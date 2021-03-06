/*
 *
 * Copyright (c) 1998-2000
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex.cpp
  *   VERSION      3.11
  *   DESCRIPTION: Declares boost::reg_expression<> and associated
  *                functions and classes. This header is the main
  *                entry point for the template regex code.
  */


/* start with C compatability API */

#ifndef BOOST_RE_REGEX_HPP
#define BOOST_RE_REGEX_HPP

#include <boost/cregex.hpp>

#ifdef __cplusplus

// what follows is all C++ don't include in C builds!!

#ifdef BOOST_RE_DEBUG
# include <iosfwd>
#endif

#include <new>
#include <boost/regex/detail/regex_config.hpp>
#if !defined(BOOST_RE_NO_TYPEINFO)
#include <typeinfo>
#endif
#include <cstring>
#include <boost/regex/detail/regex_stack.hpp>
#include <boost/regex/detail/regex_raw_buffer.hpp>
#include <boost/regex/detail/regex_kmp.hpp>
#include <boost/regex/pattern_except.hpp>
#include <boost/regex/regex_traits.hpp>
#include <boost/type_traits/cv_traits.hpp>


namespace boost{

#ifdef __BORLANDC__
   #pragma option push -a4 -b -Ve -pc
#endif

namespace re_detail{

struct re_set_long;
struct re_syntax_base;

} // namespace re_detail

namespace deprecated{
//
// class char_regex_traits_i
// provides case insensitive traits classes (deprecated):
template <class charT>
class char_regex_traits_i : public regex_traits<charT> {};

template<>
class char_regex_traits_i<char> : public regex_traits<char>
{
public:
   typedef char char_type;
   typedef unsigned char uchar_type;
   typedef unsigned int size_type;
   typedef regex_traits<char> base_type;

   char BOOST_RE_CALL translate(char c, bool)const
   {
      return static_cast<const regex_traits<char>*>(this)->translate(c, true);
   }
};

#ifndef BOOST_RE_NO_WCSTRING
template<>
class char_regex_traits_i<wchar_t> : public regex_traits<wchar_t>
{
public:
   typedef wchar_t char_type;
   typedef unsigned short uchar_type;
   typedef unsigned int size_type;
   typedef regex_traits<wchar_t> base_type;

   wchar_t BOOST_RE_CALL translate(wchar_t c, bool)const
   {
      return static_cast<const regex_traits<wchar_t>*>(this)->translate(c, true);
   }
   boost::uint_fast32_t BOOST_RE_CALL lookup_classname(const wchar_t* first, const wchar_t* last)const
   {
      boost::uint_fast32_t result = static_cast<const regex_traits<wchar_t>*>(this)->lookup_classname(first, last);
      if((result & base_type::char_class_upper) == base_type::char_class_upper)
         result |= base_type::char_class_alpha;
      return result;
   }
};
#endif
} // namespace deprecated


namespace re_detail{

enum mask_type
{
   mask_take = 1,
   mask_skip = 2,
   mask_any = mask_skip | mask_take,
   mask_all = mask_any
};

struct _narrow_type{};
struct _wide_type{};

template <class charT>
class is_byte;

template<>
class is_byte<char>
{
public:
   typedef _narrow_type width_type;
};

template<>
class is_byte<unsigned char>
{
public:
   typedef _narrow_type width_type;
};

template<>
class is_byte<signed char>
{
public:
   typedef _narrow_type width_type;
};

template <class charT>
class is_byte
{
public:
   typedef _wide_type width_type;
};


//
// compiled structures
//
// the following defs describe the format of the compiled string
//

//
// enum syntax_element_type
// describes the type of a record
enum syntax_element_type
{
   syntax_element_startmark = 0,
   syntax_element_endmark = syntax_element_startmark + 1,
   syntax_element_literal = syntax_element_endmark + 1,
   syntax_element_start_line = syntax_element_literal + 1,
   syntax_element_end_line = syntax_element_start_line + 1,
   syntax_element_wild = syntax_element_end_line + 1,
   syntax_element_match = syntax_element_wild + 1,
   syntax_element_word_boundary = syntax_element_match + 1,
   syntax_element_within_word = syntax_element_word_boundary + 1,
   syntax_element_word_start = syntax_element_within_word + 1,
   syntax_element_word_end = syntax_element_word_start + 1,
   syntax_element_buffer_start = syntax_element_word_end + 1,
   syntax_element_buffer_end = syntax_element_buffer_start + 1,
   syntax_element_backref = syntax_element_buffer_end + 1,
   syntax_element_long_set = syntax_element_backref + 1,
   syntax_element_set = syntax_element_long_set + 1,
   syntax_element_jump = syntax_element_set + 1,
   syntax_element_alt = syntax_element_jump + 1,
   syntax_element_rep = syntax_element_alt + 1,
   syntax_element_combining = syntax_element_rep + 1,
   syntax_element_soft_buffer_end = syntax_element_combining + 1,
   syntax_element_restart_continue = syntax_element_soft_buffer_end + 1
};

#ifdef BOOST_RE_DEBUG
// dwa 09/26/00 - This is needed to suppress warnings about an ambiguous conversion
std::ostream& operator<<(std::ostream&, syntax_element_type);
#endif

union offset_type
{
   re_syntax_base* p;
   unsigned i;
};

//
// struct re_syntax_base
// base class for all syntax types:
struct re_syntax_base
{
   syntax_element_type type;
   offset_type next;
   unsigned int can_be_null;
};

//
// struct re_brace
// marks start or end of (...)
struct re_brace : public re_syntax_base
{
   unsigned int index;
};

//
// struct re_literal
// marks a literal string and
// is followed by an array of charT[length]:
struct re_literal : public re_syntax_base
{
   unsigned int length;
};

//
// struct re_long_set
// provides data for sets [...] containing
// wide characters
struct re_set_long : public re_syntax_base
{
   unsigned int csingles, cranges, cequivalents;
   boost::uint_fast32_t cclasses;
   bool isnot;
};

//
// struct re_set
// provides a map of bools for sets containing
// narrow, single byte characters.
struct re_set : public re_syntax_base
{
   unsigned char _map[256];
};

//
// struct re_jump
// provides alternative next destination
struct re_jump : public re_syntax_base
{
   offset_type alt;
   unsigned char _map[256];
};

//
// struct re_repeat
// provides repeat expressions
struct re_repeat : public re_jump
{
   unsigned min, max;
   int id;
   bool leading;
   bool greedy;
};


//
// enum re_jump_size_type
// provides compiled size of re_jump
// allowing for trailing alignment
// provide this so we know how many
// bytes to insert
enum re_jump_size_type
{
   re_jump_size = (sizeof(re_jump) + padding_mask) & ~(padding_mask),
   re_repeater_size = (sizeof(re_repeat) + padding_mask) & ~(padding_mask)
};

} // namespace re_detail

//
// class basic_regex
// handles error codes and flags

class BOOST_RE_IX_DECL regbase
{
public:
   enum flag_type_
   {
      escape_in_lists = 1,                     // '\' special inside [...]
      char_classes = escape_in_lists << 1,     // [[:CLASS:]] allowed
      intervals = char_classes << 1,           // {x,y} allowed
      limited_ops = intervals << 1,            // all of + ? and | are normal characters
      newline_alt = limited_ops << 1,          // \n is the same as |
      bk_plus_qm = newline_alt << 1,           // uses \+ and \?
      bk_braces = bk_plus_qm << 1,             // uses \{ and \}
      bk_parens = bk_braces << 1,              // uses \( and \)
      bk_refs = bk_parens << 1,                // \d allowed
      bk_vbar = bk_refs << 1,                  // uses \|

      use_except = bk_vbar << 1,               // exception on error
      failbit = use_except << 1,               // error flag
      literal = failbit << 1,                  // all characters are literals
      icase = literal << 1,                    // characters are matched regardless of case
      nocollate = icase << 1,                  // don't use locale specific collation

      basic = char_classes | intervals | limited_ops | bk_braces | bk_parens | bk_refs,
      extended = char_classes | intervals | bk_refs,
      normal = escape_in_lists | char_classes | intervals | bk_refs | nocollate,
      emacs = bk_braces | bk_parens | bk_refs | bk_vbar,
      awk = extended | escape_in_lists,
      grep = basic | newline_alt,
      egrep = extended | newline_alt,
      sed = basic,
      perl = normal
   };
   typedef unsigned int flag_type;

   enum restart_info
   {
      restart_any = 0,
      restart_word = 1,
      restart_line = 2,
      restart_buf = 3,
      restart_continue = 4,
      restart_lit = 5,
      restart_fixed_lit = 6
   };

   flag_type BOOST_RE_CALL flags()const
   {
      return _flags;
   }

   regbase();
   regbase(const regbase& b);
protected:
   flag_type _flags;
};

//
// some forward declarations:
namespace re_detail{
template <class iterator, class Allocator>
class _priv_match_data;

#if defined(BOOST_NO_STD_ITERATOR_TRAITS) || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <class T>
struct regex_iterator_traits 
{
  typedef typename T::iterator_category iterator_category;
  typedef typename T::value_type        value_type;
#ifndef BOOST_MSVC
  typedef typename T::difference_type   difference_type;
  typedef typename T::pointer           pointer;
  typedef typename T::reference         reference;
#else
  typedef std::ptrdiff_t                difference_type;
  typedef value_type*                   pointer;
  typedef value_type&                   reference;
#endif
};

template <class T>
struct pointer_iterator_traits
{
   typedef std::ptrdiff_t difference_type;
   typedef T value_type;
   typedef T* pointer;
   typedef T& reference;
   typedef std::random_access_iterator_tag iterator_category;
};
template <class T>
struct const_pointer_iterator_traits
{
   typedef std::ptrdiff_t difference_type;
   typedef T value_type;
   typedef const T* pointer;
   typedef const T& reference;
   typedef std::random_access_iterator_tag iterator_category;
};

template<>
struct regex_iterator_traits<char*> : pointer_iterator_traits<char>{};
template<>
struct regex_iterator_traits<const char*> : const_pointer_iterator_traits<char>{};
template<>
struct regex_iterator_traits<wchar_t*> : pointer_iterator_traits<wchar_t>{};
template<>
struct regex_iterator_traits<const wchar_t*> : const_pointer_iterator_traits<wchar_t>{};

#if defined(__SGI_STL_PORT) && defined(__STL_DEBUG)
template<>
struct regex_iterator_traits<std::string::iterator> : pointer_iterator_traits<char>{};
template<>
struct regex_iterator_traits<std::string::const_iterator> : const_pointer_iterator_traits<char>{};
#ifndef BOOST_NO_WSTRING
template<>
struct regex_iterator_traits<std::wstring::iterator> : pointer_iterator_traits<wchar_t>{};
template<>
struct regex_iterator_traits<std::wstring::const_iterator> : const_pointer_iterator_traits<wchar_t>{};
#endif // BOOST_NO_WSTRING
#endif // stport

#else

template <class T>
struct regex_iterator_traits : public std::iterator_traits<T> {};

#endif

template <class I>
struct def_alloc_param_traits
{
   typedef typename regex_iterator_traits<I>::value_type const_value_type;
   typedef typename remove_cv<const_value_type>::type type;
};
template <>
struct def_alloc_param_traits<const char*>
{
   typedef char type;
};
template <>
struct def_alloc_param_traits<const wchar_t*>
{
   typedef wchar_t type;
};

}

template <class iterator, class Allocator BOOST_RE_DEF_ALLOC_PARAM(typename re_detail::def_alloc_param_traits<iterator>::type) >
class match_results;

//
// class reg_expression
// represents the compiled
// regular expression:
//

#if defined(BOOST_RE_NO_TEMPLATE_SWITCH_MERGE) && !defined(BOOST_RE_NO_NAMESPACES)
//
// Ugly ugly hack, 
// template don't merge if they contain switch statements so declare these
// templates in unnamed namespace (ie with internal linkage), each translation
// unit then gets its own local copy, it works seemlessly but bloats the app.
namespace{
#endif

template <class charT, class traits BOOST_RE_TRICKY_DEFAULT_PARAM(regex_traits<charT>), class Allocator BOOST_RE_DEF_ALLOC_PARAM(charT) >
class reg_expression : public regbase
{
   typedef typename traits::size_type traits_size_type;
   typedef typename traits::uchar_type traits_uchar_type;
   typedef typename traits::string_type traits_string_type;
public:
   // typedefs:
   typedef charT char_type;
   typedef traits traits_type;

   // locale_type
   // placeholder for actual locale type used by the
   // traits class to localise *this.
   typedef typename traits::locale_type locale_type;
   // value_type
   typedef charT value_type;
   // reference, const_reference
   typedef charT& reference;
   typedef const charT& const_reference;
   // iterator, const_iterator
   typedef const charT* const_iterator;
   typedef const_iterator iterator;
   // difference_type
   typedef typename Allocator::difference_type difference_type;
   // size_type
   typedef typename Allocator::size_type size_type;   
   // allocator_type
   typedef Allocator allocator_type;
   typedef Allocator alloc_type;
   // flag_type
   typedef regbase::flag_type flag_type;
   
public:
   explicit reg_expression(const Allocator& a = Allocator());
   explicit reg_expression(const charT* p, flag_type f = regbase::normal, const Allocator& a = Allocator());
   reg_expression(const charT* p1, const charT* p2, flag_type f = regbase::normal, const Allocator& a = Allocator());
   reg_expression(const charT* p, size_type len, flag_type f, const Allocator& a = Allocator());
   reg_expression(const reg_expression&);
   ~reg_expression();
   reg_expression& BOOST_RE_CALL operator=(const reg_expression&);
   reg_expression& BOOST_RE_CALL operator=(const charT* ptr)
   {
      set_expression(ptr, regbase::normal | regbase::use_except);
      return *this;
   }

   //
   // assign:
   reg_expression& assign(const reg_expression& that)
   { return *this = that; }
   reg_expression& assign(const charT* ptr, flag_type f = regbase::normal)
   {
      set_expression(ptr, f | regbase::use_except);
      return *this;
   }

   reg_expression& assign(const charT* first,
                          const charT* last,
                          flag_type f = regbase::normal)
   {
      set_expression(first, last, f | regbase::use_except);
      return *this;
   }
#ifndef BOOST_NO_MEMBER_TEMPLATES

   template <class ST, class SA>
   unsigned int BOOST_RE_CALL set_expression(const std::basic_string<charT, ST, SA>& p, flag_type f = regbase::normal)
   { return set_expression(p.data(), p.data() + p.size(), f); }

   template <class ST, class SA>
   explicit reg_expression(const std::basic_string<charT, ST, SA>& p, flag_type f = regbase::normal, const Allocator& a = Allocator())
    : data(a), pkmp(0) { set_expression(p, f | regbase::use_except); }

   template <class I>
   reg_expression(I first, I last, flag_type f = regbase::normal, const Allocator& al = Allocator())
    : data(al), pkmp(0)
   {
      size_type len = last-first;
      scoped_array<charT> a(new charT[len]);
      std::copy(first, last, a.get());
      set_expression(a.get(), a.get() + len, f | regbase::use_except);
   }

   template <class ST, class SA>
   reg_expression& BOOST_RE_CALL operator=(const std::basic_string<charT, ST, SA>& p)
   {
      set_expression(p.c_str(), p.c_str() + p.size(), regbase::normal | regbase::use_except);
      return *this;
   }

   template <class string_traits, class A>
   reg_expression& BOOST_RE_CALL assign(
       const std::basic_string<charT, string_traits, A>& s,
       flag_type f = regbase::normal)
   {
      set_expression(s.c_str(), s.c_str() + s.size(), f | regbase::use_except);
      return *this;
   }

   template <class fwd_iterator>
   reg_expression& BOOST_RE_CALL assign(fwd_iterator first,
                          fwd_iterator last,
                          flag_type f = regbase::normal)
   {
      size_type len = last-first;
      scoped_array<charT> a(new charT[len]);
      std::copy(first, last, a.get());
      set_expression(a.get(), a.get() + len, f | regbase::use_except);
      return *this;
   }
#elif !defined(BOOST_RE_NO_STRING_DEF_ARGS)
   unsigned int BOOST_RE_CALL set_expression(const std::basic_string<charT>& p, flag_type f = regbase::normal)
   { return set_expression(p.data(), p.data() + p.size(), f | regbase::use_except); }

   reg_expression(const std::basic_string<charT>& p, flag_type f = regbase::normal, const Allocator& a = Allocator())
    : data(a), pkmp(0) { set_expression(p, f | regbase::use_except); }

   reg_expression& BOOST_RE_CALL operator=(const std::basic_string<charT>& p)
   {
      set_expression(p.c_str(), p.c_str() + p.size(), regbase::normal | regbase::use_except);
      return *this;
   }

   reg_expression& BOOST_RE_CALL assign(
       const std::basic_string<charT>& s,
       flag_type f = regbase::normal)
   {
      set_expression(s.c_str(), s.c_str() + s.size(), f | regbase::use_except);
      return *this;
   }

#endif


   //
   // allocator access:
   Allocator BOOST_RE_CALL get_allocator()const;
   //
   // locale:
   locale_type BOOST_RE_CALL imbue(locale_type l){ return traits_inst.imbue(l); }
   locale_type BOOST_RE_CALL getloc()const{ return traits_inst.getloc(); }
   //
   // flags:
   flag_type BOOST_RE_CALL getflags()const
   { return flags(); }
   //
   // str:
   std::basic_string<charT> BOOST_RE_CALL str()const
   {
      std::basic_string<charT> result;
      if(this->error_code() == 0)
         result = std::basic_string<charT>(_expression, _expression_len);
      return result;
   }
   //
   // begin, end:
   const_iterator BOOST_RE_CALL begin()const
   { return (this->error_code() ? 0 : _expression); }
   const_iterator BOOST_RE_CALL end()const
   { return (this->error_code() ? 0 : _expression + _expression_len); }
   //
   // swap:
   void BOOST_RE_CALL swap(reg_expression&)throw();
   //
   // size:
   size_type BOOST_RE_CALL size()const
   { return (this->error_code() ? 0 : _expression_len); }
   //
   // max_size:
   size_type BOOST_RE_CALL max_size()const
   { return UINT_MAX; }
   //
   // empty:
   bool BOOST_RE_CALL empty()const
   { return this->error_code(); }

   unsigned BOOST_RE_CALL mark_count()const { return (this->error_code() ? 0 : marks); }
   bool BOOST_RE_CALL operator==(const reg_expression&)const;
   bool BOOST_RE_CALL operator<(const reg_expression&)const;
   //
   // The following are deprecated as public interfaces
   // but are available for compatability with earlier versions.
   allocator_type BOOST_RE_CALL allocator()const;
   const charT* BOOST_RE_CALL expression()const { return (this->error_code() ? 0 : _expression); }
   unsigned int BOOST_RE_CALL set_expression(const charT* p, const charT* end, flag_type f = regbase::normal);
   unsigned int BOOST_RE_CALL set_expression(const charT* p, flag_type f = regbase::normal) { return set_expression(p, p + traits_type::length(p), f); }
   //
   // this should be private but template friends don't work:
   const traits_type& get_traits()const { return traits_inst; }
   unsigned int BOOST_RE_CALL error_code()const
   {
      return error_code_;
   }

private:
   re_detail::raw_storage<Allocator> data;
   unsigned _restart_type;
   unsigned marks;
   int repeats;
   unsigned char* startmap;
   charT* _expression;
   unsigned _expression_len;
   unsigned int _leading_len;
   const charT* _leading_string;
   unsigned int _leading_string_len;
   re_detail::kmp_info<charT>* pkmp;
   traits_type traits_inst;
   unsigned error_code_;

   void BOOST_RE_CALL compile_maps();
   void BOOST_RE_CALL compile_map(re_detail::re_syntax_base* node, unsigned char* _map, unsigned int* pnull, unsigned char mask, re_detail::re_syntax_base* terminal = 0)const;
   bool BOOST_RE_CALL probe_start(re_detail::re_syntax_base* node, charT c, re_detail::re_syntax_base* terminal)const;
   bool BOOST_RE_CALL probe_start_null(re_detail::re_syntax_base* node, re_detail::re_syntax_base* terminal)const;
   void BOOST_RE_CALL fixup_apply(re_detail::re_syntax_base* b, unsigned cbraces);
   void BOOST_RE_CALL move_offsets(re_detail::re_syntax_base* j, unsigned size);
   re_detail::re_syntax_base* BOOST_RE_CALL compile_set(const charT*& first, const charT* last);
   re_detail::re_syntax_base* BOOST_RE_CALL compile_set_aux(re_detail::jstack<traits_string_type, Allocator>& singles, re_detail::jstack<traits_string_type, Allocator>& ranges, re_detail::jstack<boost::uint_fast32_t, Allocator>& classes, re_detail::jstack<traits_string_type, Allocator>& equivalents, bool isnot, const re_detail::_narrow_type&);
   re_detail::re_syntax_base* BOOST_RE_CALL compile_set_aux(re_detail::jstack<traits_string_type, Allocator>& singles, re_detail::jstack<traits_string_type, Allocator>& ranges, re_detail::jstack<boost::uint_fast32_t, Allocator>& classes, re_detail::jstack<traits_string_type, Allocator>& equivalents, bool isnot, const re_detail::_wide_type&);
   re_detail::re_syntax_base* BOOST_RE_CALL compile_set_simple(re_detail::re_syntax_base* dat, unsigned long cls, bool isnot = false);
   unsigned int BOOST_RE_CALL parse_inner_set(const charT*& first, const charT* last);

   re_detail::re_syntax_base* BOOST_RE_CALL add_simple(re_detail::re_syntax_base* dat, re_detail::syntax_element_type type, unsigned int size = sizeof(re_detail::re_syntax_base));
   re_detail::re_syntax_base* BOOST_RE_CALL add_literal(re_detail::re_syntax_base* dat, charT c);
   charT BOOST_RE_CALL parse_escape(const charT*& first, const charT* last);
   void BOOST_RE_CALL parse_range(const charT*& first, const charT* last, unsigned& min, unsigned& max);
   bool BOOST_RE_CALL skip_space(const charT*& first, const charT* last);
   unsigned int BOOST_RE_CALL probe_restart(re_detail::re_syntax_base* dat);
   unsigned int BOOST_RE_CALL fixup_leading_rep(re_detail::re_syntax_base* dat, re_detail::re_syntax_base* end);
   void BOOST_RE_CALL fail(unsigned int err);

protected:
   static int BOOST_RE_CALL repeat_count(const reg_expression& e)
   { return e.repeats; }
   static unsigned int BOOST_RE_CALL restart_type(const reg_expression& e)
   { return e._restart_type; }
   static const re_detail::re_syntax_base* BOOST_RE_CALL first(const reg_expression& e)
   { return (const re_detail::re_syntax_base*)e.data.data(); }
   static const unsigned char* BOOST_RE_CALL get_map(const reg_expression& e)
   { return e.startmap; }
   static unsigned int BOOST_RE_CALL leading_length(const reg_expression& e)
   { return e._leading_len; }
   static const re_detail::kmp_info<charT>* get_kmp(const reg_expression& e)
   { return e.pkmp; }
   static bool BOOST_RE_CALL can_start(charT c, const unsigned char* _map, unsigned char mask, const re_detail::_wide_type&);
   static bool BOOST_RE_CALL can_start(charT c, const unsigned char* _map, unsigned char mask, const re_detail::_narrow_type&);
};

template <class charT, class traits, class Allocator>
void BOOST_RE_CALL reg_expression<charT, traits, Allocator>::swap(reg_expression& that)throw()
{
   // this is not as efficient as it should be,
   // however swapping traits classes is problematic
   // so just use 'brute force' method for now:
   reg_expression<charT, traits, Allocator> e(that);
   that = *this;
   *this = e;
}


#if defined(BOOST_RE_NO_TEMPLATE_SWITCH_MERGE) && !defined(BOOST_RE_NO_NAMESPACES)
} // namespace
#endif

//
// class match_results and match_results_base
// handles what matched where

template <class iterator>
struct sub_match
{
   typedef typename re_detail::regex_iterator_traits<iterator>::value_type       value_type;
#if defined(BOOST_NO_STD_ITERATOR_TRAITS) || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
   typedef std::ptrdiff_t  difference_type;
#else
   typedef typename re_detail::regex_iterator_traits<iterator>::difference_type       difference_type;
#endif
   typedef iterator                                                  iterator_type;
   
   iterator first;
   iterator second;
   bool matched;

   operator std::basic_string<value_type> ()const
   {
      std::basic_string<value_type> result;
      unsigned len = boost::re_detail::distance((iterator)first, (iterator)second);
      result.reserve(len);
      iterator i = first;
      while(i != second)
      {
         result.append(1, *i);
         ++i;
      }
      return result;
   }
   #ifdef BOOST_OLD_REGEX_H
   //
   // the following are deprecated, do not use!!
   //
   operator int()const;
   operator unsigned int()const;
   operator short()const
   {
      return (short)(int)(*this);
   }
   operator unsigned short()const
   {
      return (unsigned short)(unsigned int)(*this);
   }
   #endif
   sub_match() { matched = false; }
   sub_match(iterator i) : first(i), second(i), matched(false) {}

   bool operator==(const sub_match& that)const
   {
      return (first == that.first) && (second == that.second) && (matched == that.matched);
   }
   bool BOOST_RE_CALL operator !=(const sub_match& that)const
   { return !(*this == that); }

   difference_type BOOST_RE_CALL length()const
   {
      difference_type n = boost::re_detail::distance((iterator)first, (iterator)second);
      return n;
   }
};

#ifdef BOOST_OLD_REGEX_H
namespace re_detail{
template <class iterator, class charT>
int do_toi(iterator i, iterator j, char c, int radix)
{
   std::string s(i, j);
   char* p;
   int result = std::strtol(s.c_str(), &p, radix);
   if(*p)throw bad_pattern("Bad sub-expression");
   return result;
}

//
// helper:
template <class I, class charT>
int do_toi(I& i, I j, charT c)
{
   int result = 0;
   while((i != j) && (isdigit(*i)))
   {
      result = result*10 + (*i - '0');
      ++i;
   }
   return result;
}
}


template <class iterator>
sub_match<iterator>::operator int()const
{
   iterator i = first;
   iterator j = second;
   if(i == j)throw bad_pattern("Bad sub-expression");
   int neg = 1;
   if((i != j) && (*i == '-'))
   {
      neg = -1;
      ++i;
   }
   neg *= re_detail::do_toi(i, j, *i);
   if(i != j)throw bad_pattern("Bad sub-expression");
   return neg;
}
template <class iterator>
sub_match<iterator>::operator unsigned int()const
{
   iterator i = first;
   iterator j = second;
   if(i == j)
      throw bad_pattern("Bad sub-expression");
   return re_detail::do_toi(i, j, *first);
}
#endif

namespace re_detail{

template <class iterator, class Allocator BOOST_RE_DEF_ALLOC_PARAM(typename def_alloc_param_traits<iterator>::type) >
class match_results_base
{
public:
   typedef Allocator                                                 alloc_type;
   typedef typename boost::re_detail::rebind_allocator<iterator, Allocator>::type  iterator_alloc;
   typedef typename iterator_alloc::size_type                        size_type;
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_NO_STD_ITERATOR_TRAITS)
   typedef typename std::iterator_traits<iterator>::difference_type  difference_type;
   typedef typename std::iterator_traits<iterator>::value_type       char_type;
#else
   typedef std::ptrdiff_t                                            difference_type;
   typedef typename re_detail::regex_iterator_traits<iterator>::value_type char_type;
#endif
   typedef sub_match<iterator>                                       value_type;
   typedef iterator                                                  iterator_type;

protected:
   typedef typename boost::re_detail::rebind_allocator<char, Allocator>::type c_alloc;
   
   struct c_reference : public c_alloc
   {
      unsigned int cmatches;
      unsigned count;
      sub_match<iterator> head, tail, null;
      unsigned int lines;
      iterator line_pos, base;
      c_reference(const Allocator& a) : c_alloc(a) {  }

      bool operator==(const c_reference& that)const
      {
         return (cmatches == that.cmatches) &&
                  (count == that.count) &&
                  (head == that.head) &&
                  (tail == that.tail) &&
                  (lines == that.lines) &&
                  (base == that.base);
      }
      bool operator!=(const c_reference& that)const
      { return !(*this == that); }
   };

   c_reference* ref;

   void BOOST_RE_CALL cow();

   // protected contructor for derived class...
   match_results_base(bool){}
   void BOOST_RE_CALL free();

public:

   match_results_base(const Allocator& a = Allocator());

   match_results_base(const match_results_base& m)
   {
      ref = m.ref;
      ++(ref->count);
   }

   match_results_base& BOOST_RE_CALL operator=(const match_results_base& m);

   ~match_results_base()
   {
      free();
   }

   size_type BOOST_RE_CALL size()const
   {
      //return (*this)[0].matched ? ref->cmatches : 0;
      return ref->cmatches;
   }

   const sub_match<iterator>& BOOST_RE_CALL operator[](int n) const
   {
      if((n >= 0) && ((unsigned int)n < ref->cmatches))
         return *(sub_match<iterator>*)((char*)ref + sizeof(c_reference) + sizeof(sub_match<iterator>)*n);
      return (n == -1) ? ref->head : (n == -2) ? ref->tail : ref->null;
   }

   Allocator BOOST_RE_CALL allocator()const;

   difference_type BOOST_RE_CALL length(unsigned int sub = 0)const
   {
      jm_assert(ref->cmatches);
      const sub_match<iterator>& m = (*this)[sub];
      if(m.matched == false)
         return 0;
      difference_type n = boost::re_detail::distance((iterator)m.first, (iterator)m.second);
      return n;
   }

   std::basic_string<char_type> str(int i)const
   {
      return static_cast<std::basic_string<char_type> >((*this)[i]);
   }

   unsigned int BOOST_RE_CALL line()const
   {
      return ref->lines;
   }

   difference_type BOOST_RE_CALL position(unsigned int sub = 0)const
   {
      jm_assert(ref->cmatches);
      const sub_match<iterator>& s = (*this)[sub];
      if(s.matched == false)
         return -1;
      difference_type n = boost::re_detail::distance((iterator)(ref->base), (iterator)(s.first));
      return n;
   }

   iterator BOOST_RE_CALL line_start()const
   {
      return ref->line_pos;
   }

   void swap(match_results_base& that)
   {
      c_reference* t = that.ref;
      that.ref = ref;
      ref = t;
   }

   bool operator==(const match_results_base& that)const;
   bool operator<(const match_results_base& that)const
   { return position() < that.position(); }

   friend class match_results<iterator, Allocator>;

   void BOOST_RE_CALL set_size(size_type n);
   void BOOST_RE_CALL set_size(size_type n, iterator i, iterator j);
   void BOOST_RE_CALL maybe_assign(const match_results_base& m);
   void BOOST_RE_CALL init_fail(iterator i, iterator j);

   void BOOST_RE_CALL set_first(iterator i);
   void BOOST_RE_CALL set_first(iterator i, size_t pos);

   void BOOST_RE_CALL set_second(iterator i)
   {
      cow();
      ((sub_match<iterator>*)(ref+1))->second = i;
      ((sub_match<iterator>*)(ref+1))->matched = true;
      ref->tail.first = i;
      ref->tail.matched = (ref->tail.first == ref->tail.second) ? false : true;
   }

   void BOOST_RE_CALL set_second(iterator i, size_t pos, bool m = true)
   {
      cow();
      ((sub_match<iterator>*)((char*)ref + sizeof(c_reference) + sizeof(sub_match<iterator>) * pos))->second = i;
      ((sub_match<iterator>*)((char*)ref + sizeof(c_reference) + sizeof(sub_match<iterator>) * pos))->matched = m;
      if(pos == 0)
      {
         ref->tail.first = i;
         ref->tail.matched = (ref->tail.first == ref->tail.second) ? false : true;
      }
   }

   void BOOST_RE_CALL set_line(unsigned int i, iterator pos)
   {
      ref->lines = i;
      ref->line_pos = pos;
   }

   void BOOST_RE_CALL set_base(iterator pos)
   {
      ref->base = pos;
   }
};

template <class iterator, class Allocator>
void BOOST_RE_CALL match_results_base<iterator, Allocator>::set_first(iterator i)
{
   cow();
   ref->head.second = i;
   ref->head.matched = (ref->head.first == ref->head.second) ? false : true;
   sub_match<iterator>* p1 = (sub_match<iterator>*)(ref+1);
   sub_match<iterator>* p2 = p1 + ref->cmatches;
   p1->first = i;
   p1->matched = false;
   ++p1;
   while(p1 != p2)
   {
      p1->matched = false;
      p1->first = ref->tail.second;
      p1->second = ref->tail.second;
      ++p1;
   }
}

template <class iterator, class Allocator>
void BOOST_RE_CALL match_results_base<iterator, Allocator>::set_first(iterator i, size_t pos)
{
   cow();
   ((sub_match<iterator>*)((char*)ref + sizeof(c_reference) + sizeof(sub_match<iterator>) * pos))->first = i;
   if(pos == 0)
   {
      ref->head.second = i;
      ref->head.matched = (ref->head.first == ref->head.second) ? false : true;
      sub_match<iterator>* p1 = (sub_match<iterator>*)(ref+1);
      sub_match<iterator>* p2 = p1 + ref->cmatches;
      p1->first = i;
      p1->matched = false;
      ++p1;
      while(p1 != p2)
      {
         p1->matched = false;
         p1->first = ref->tail.second;
         p1->second = ref->tail.second;
         ++p1;
      }
   }
}


template <class iterator, class Allocator>
match_results_base<iterator, Allocator>::match_results_base(const Allocator& a)
{
   ref = (c_reference*)c_alloc(a).allocate(sizeof(sub_match<iterator>) + sizeof(c_reference));
   try
   {
      new (ref) c_reference(a);
      ref->cmatches = 1;
      ref->count = 1;
      // construct the sub_match<iterator>:
      try
      {
         new ((sub_match<iterator>*)(ref+1)) sub_match<iterator>();
      }
      catch(...)
      { 
         jm_destroy(ref); 
         throw; 
      }
   }
   catch(...)
   { 
      c_alloc(a).deallocate((char*)(void*)ref, sizeof(sub_match<iterator>) + sizeof(c_reference)); 
      throw; 
   }
}

template <class iterator, class Allocator>
Allocator BOOST_RE_CALL match_results_base<iterator, Allocator>::allocator()const
{
  return *((c_alloc*)ref);
}

template <class iterator, class Allocator>
inline match_results_base<iterator, Allocator>& BOOST_RE_CALL match_results_base<iterator, Allocator>::operator=(const match_results_base<iterator, Allocator>& m)
{
   if(ref != m.ref)
   {
      free();
      ref = m.ref;
      ++(ref->count);
   }
   return *this;
}


template <class iterator, class Allocator>
void BOOST_RE_CALL match_results_base<iterator, Allocator>::free()
{
   if(--(ref->count) == 0)
   {
      c_alloc a(*ref);
      sub_match<iterator>* p1, *p2;
      p1 = (sub_match<iterator>*)(ref+1);
      p2 = p1 + ref->cmatches;
      while(p1 != p2)
      {
         jm_destroy(p1);
         ++p1;
      }
      jm_destroy(ref);
      a.deallocate((char*)(void*)ref, sizeof(sub_match<iterator>) * ref->cmatches + sizeof(c_reference));
   }
}

template <class iterator, class Allocator>
bool match_results_base<iterator, Allocator>::operator==(const match_results_base<iterator, Allocator>& that)const
{
   if(*ref != *(that.ref))
      return false;
   const sub_match<iterator>* p1 = (sub_match<iterator>*)(ref+1);
   const sub_match<iterator>* p2 = p1 + ref->cmatches;
   const sub_match<iterator>* p3 = (sub_match<iterator>*)(that.ref+1);
   while(p1 != p2)
   {
      if(*p1 != *p3)
         return false;
      ++p1;
      ++p3;
   }
   return true;
}

template <class iterator, class Allocator>
void BOOST_RE_CALL match_results_base<iterator, Allocator>::set_size(size_type n)
{
   if(ref->cmatches != n)
   {
      c_reference* newref = (c_reference*)ref->allocate(sizeof(sub_match<iterator>) * n + sizeof(c_reference));
      try
      {
         new (newref) c_reference(*ref);
         newref->count = 1;
         newref->cmatches = n;
         sub_match<iterator>* p1, *p2;
         p1 = (sub_match<iterator>*)(newref+1);
         p2 = p1 + newref->cmatches;
         try
         {
            while(p1 != p2)
            {
               new (p1) sub_match<iterator>();
               ++p1;
            }
            free();
         }
         catch(...)
         { 
            p2 = (sub_match<iterator>*)(newref+1);
            while(p2 != p1)
            {
               jm_destroy(p2);
               ++p2;
            }
            jm_destroy(ref);
            throw; 
         }
         ref = newref;
      }
      catch(...)
      { 
         ref->deallocate((char*)(void*)newref, sizeof(sub_match<iterator>) * n + sizeof(c_reference)); 
         throw; 
      }
   }
}

template <class iterator, class Allocator>
void BOOST_RE_CALL match_results_base<iterator, Allocator>::set_size(size_type n, iterator i, iterator j)
{
   if(ref->cmatches != n)
   {
      c_reference* newref = (c_reference*)ref->allocate(sizeof(sub_match<iterator>) * n + sizeof(c_reference));;
      try{
         new (newref) c_reference(*ref);
         newref->count = 1;
         newref->cmatches = n;
         sub_match<iterator>* p1 = (sub_match<iterator>*)(newref+1);
         sub_match<iterator>* p2 = p1 + newref->cmatches;
         try
         {
            while(p1 != p2)
            {
               new (p1) sub_match<iterator>(j);
               ++p1;
            }
            free();
         }
         catch(...)
         { 
            p2 = (sub_match<iterator>*)(newref+1);
            while(p2 != p1)
            {
               jm_destroy(p2);
               ++p2;
            }
            jm_destroy(ref);
            throw; 
         }
         ref = newref;
      }
      catch(...)
      { 
         ref->deallocate((char*)(void*)newref, sizeof(sub_match<iterator>) * n + sizeof(c_reference)); 
         throw; 
      }
   }
   else
   {
      cow();
      // set iterators to be i, matched to false:
      sub_match<iterator>* p1, *p2;
      p1 = (sub_match<iterator>*)(ref+1);
      p2 = p1 + ref->cmatches;
      while(p1 != p2)
      {
         p1->first = j;
         p1->second = j;
         p1->matched = false;
         ++p1;
      }                                 
   }
   ref->head.first = i;
   ref->tail.second = j;
   ref->head.matched = ref->tail.matched = true;
   ref->null.first = ref->null.second = j;
   ref->null.matched = false;
}

template <class iterator, class Allocator>
inline void BOOST_RE_CALL match_results_base<iterator, Allocator>::init_fail(iterator i, iterator j)
{
   set_size(ref->cmatches, i, j);
}

template <class iterator, class Allocator>
void BOOST_RE_CALL match_results_base<iterator, Allocator>::maybe_assign(const match_results_base<iterator, Allocator>& m)
{
   sub_match<iterator>* p1, *p2;
   p1 = (sub_match<iterator>*)(ref+1);
   p2 = (sub_match<iterator>*)(m.ref+1);
   iterator base = (*this)[-1].first;
   unsigned int len1 = 0;
   unsigned int len2 = 0;
   unsigned int base1 = 0;
   unsigned int base2 = 0;
   unsigned int i;
   for(i = 0; i < ref->cmatches; ++i)
   {
      //
      // leftmost takes priority over longest:
      base1 = boost::re_detail::distance(base, p1->first);
      base2 = boost::re_detail::distance(base, p2->first);
      if(base1 < base2) return;
      if(base2 < base1) break;

      len1 = boost::re_detail::distance(p1->first, p1->second);
      len2 = boost::re_detail::distance(p2->first, p2->second);
      if((len1 != len2) || ((p1->matched == false) && (p2->matched == true)))
         break;
      if((p1->matched == true) && (p2->matched == false))
         return;
      ++p1;
      ++p2;
   }
   if(i == ref->cmatches)
      return;
   if(base2 < base1)
      *this = m;
   else if((len2 > len1) || ((p1->matched == false) && (p2->matched == true)) )
      *this = m;
}

template <class iterator, class Allocator>
void BOOST_RE_CALL match_results_base<iterator, Allocator>::cow()
{
   if(ref->count > 1)
   {
      c_reference* newref = (c_reference*)ref->allocate(sizeof(sub_match<iterator>) * ref->cmatches + sizeof(c_reference));
      try{
         new (newref) c_reference(*ref);
         newref->count = 1;
         sub_match<iterator>* p1 = (sub_match<iterator>*)(newref+1);
         sub_match<iterator>* p2 = p1 + newref->cmatches;
         sub_match<iterator>* p3 = (sub_match<iterator>*)(ref+1);
         try{
            while(p1 != p2)
            {
               new (p1) sub_match<iterator>(*p3);
               ++p1;
               ++p3;
            }
         }
         catch(...)
         { 
            p2 = (sub_match<iterator>*)(newref+1);
            while(p2 != p1)
            {
               jm_destroy(p2);
               ++p2;
            }
            jm_destroy(ref);
            throw; 
         }
      --(ref->count);
      ref = newref;
      }
      catch(...)
      { 
         ref->deallocate((char*)(void*)newref, sizeof(sub_match<iterator>) * ref->cmatches + sizeof(c_reference)); 
         throw; 
      }
   }
}

} // namespace re_detail

//
// class match_results
// encapsulates match_results_base, does a deep copy rather than
// reference counting to ensure thread safety when copying
// other match_results instances

template <class iterator, class Allocator>
class match_results : public re_detail::match_results_base<iterator, Allocator>
{
   typedef re_detail::match_results_base<iterator, Allocator> base_type;
public:

   typedef typename base_type::alloc_type          alloc_type;
   typedef typename base_type::size_type           size_type;
   typedef typename base_type::char_type           char_type;
   typedef typename base_type::value_type          value_type;
   typedef typename base_type::difference_type     difference_type;
   typedef typename base_type::iterator_type       iterator_type;

   explicit match_results(const Allocator& a = Allocator())
      : re_detail::match_results_base<iterator, Allocator>(a){}

   match_results(const re_detail::match_results_base<iterator, Allocator>& m)
      : re_detail::match_results_base<iterator, Allocator>(m){}

   match_results& operator=(const re_detail::match_results_base<iterator, Allocator>& m)
   {
      // shallow copy
      base_type::operator=(m);
      return *this;
   }

   match_results(const match_results& m);
   match_results& operator=(const match_results& m);
   //
   // the following function definitions should *not* be required, except
   // when this class is used as a template inside another template definition,
   // in which members of the base class are not visible to the calling code.
   // As a workaround we define simple forwarding functions:
   //
   size_type size()const
   { return static_cast<const base_type*>(this)->size(); }

   const sub_match<iterator>& operator[](int n) const
   { return (*static_cast<const base_type*>(this))[n]; }

   Allocator allocator()const
   { return static_cast<const base_type*>(this)->allocator(); }

   difference_type length(int sub = 0)const
   { return static_cast<const base_type*>(this)->length(sub); }

   difference_type position(unsigned int sub = 0)const
   { return static_cast<const base_type*>(this)->position(sub); }

   unsigned int line()const
   { return static_cast<const base_type*>(this)->line(); }

   iterator line_start()const
   { return static_cast<const base_type*>(this)->line_start(); }

   std::basic_string<char_type> str(int sub = 0)const
   { return static_cast<const base_type*>(this)->str(sub); }

   void swap(match_results& that)
   { static_cast<base_type*>(this)->swap(that); }

   bool operator==(const match_results& that)const
   { return static_cast<const base_type&>(*this) == static_cast<const base_type&>(that); }

   bool operator<(const match_results& that) const
   { return position() < that.position(); }
};

template <class iterator, class Allocator>
match_results<iterator, Allocator>::match_results(const match_results<iterator, Allocator>& m)
   : re_detail::match_results_base<iterator, Allocator>(false)
{
   this->ref =
      reinterpret_cast<typename re_detail::match_results_base<iterator, Allocator>::c_reference *>
         (m.ref->allocate(sizeof(sub_match<iterator>) * m.ref->cmatches +
                          sizeof(typename re_detail::match_results_base<iterator, Allocator>::c_reference)));
   try{
      new (this->ref) typename re_detail::match_results_base<iterator, Allocator>::c_reference(*m.ref);
      this->ref->count = 1;
      sub_match<iterator>* p1 = (sub_match<iterator>*)(this->ref+1);
      sub_match<iterator>* p2 = p1 + this->ref->cmatches;
      sub_match<iterator>* p3 = (sub_match<iterator>*)(m.ref+1);
      try{
         while(p1 != p2)
         {
            new (p1) sub_match<iterator>(*p3);
            ++p1;
            ++p3;
         }
      }
      catch(...)
      { 
         p2 = (sub_match<iterator>*)(this->ref+1);
         while(p2 != p1)
         {
            re_detail::jm_destroy(p2);
            ++p2;
         }
         re_detail::jm_destroy(this->ref);
         throw; 
      }
   }
   catch(...)
   { 
      m.ref->deallocate((char*)(void*)this->ref, sizeof(sub_match<iterator>) * m.ref->cmatches + sizeof(typename re_detail::match_results_base<iterator, Allocator>::c_reference));
      throw; 
   }
}

template <class iterator, class Allocator>
match_results<iterator, Allocator>& match_results<iterator, Allocator>::operator=(const match_results<iterator, Allocator>& m)
{
   match_results<iterator, Allocator> t(m);
   this->swap(t);
   return *this;
}

namespace re_detail{
template <class iterator, class charT, class traits_type, class Allocator>
iterator BOOST_RE_CALL re_is_set_member(iterator next, 
                          iterator last, 
                          re_set_long* set_, 
                          const reg_expression<charT, traits_type, Allocator>& e);
} // namepsace re_detail

#ifdef __BORLANDC__
  #pragma option pop
#endif

} // namespace boost

#include <boost/regex/detail/regex_compile.hpp>

namespace boost{

typedef reg_expression<char, regex_traits<char>, BOOST_RE_DEF_ALLOC(char)> regex;
#ifndef BOOST_RE_NO_WCSTRING
typedef reg_expression<wchar_t, regex_traits<wchar_t>, BOOST_RE_DEF_ALLOC(wchar_t)> wregex;
#endif

typedef match_results<const char*> cmatch;
#ifndef BOOST_RE_NO_WCSTRING
typedef match_results<const wchar_t*> wcmatch;
#endif

} // namespace boost

#include <boost/regex/detail/regex_match.hpp>
#include <boost/regex/detail/regex_format.hpp>
#include <boost/regex/detail/regex_split.hpp>


#endif  // __cplusplus

#endif  // include


























