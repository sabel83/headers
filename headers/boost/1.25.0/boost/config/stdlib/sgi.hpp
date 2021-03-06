//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

//  generic SGI STL:

#if !defined(__STL_CONFIG_H)
#  include <utility>
#  if !defined(__STL_CONFIG_H)
#      error "This is not the SGI STL!"
#  endif
#endif

//
// No std::iterator traits without partial specialisation:
//
#if !defined(__STL_CLASS_PARTIAL_SPECIALIZATION)
#  define BOOST_NO_STD_ITERATOR_TRAITS
#endif

//
// No std::stringstream with gcc < 3
//
#if defined(__GNUC__) && (__GNUC__ < 3) && (__GNUC_MINOR__ < 95) && !defined(__STL_USE_NEW_IOSTREAMS) || defined(__APPLE_CC__)
   // Note that we only set this for gnu C++ prior to 2.95 since the
   // latest patches for that release do contain a minimal <sstream>
   // If you are running a 2.95 release prior to 2.95.3 then this will need
   // setting, but there is no way to detect that automatically (other
   // than by running the configure script).
#  define BOOST_NO_STRINGSTREAM
#endif

//
// Assume no std::locale without own iostreams (this may be an
// incorrect assumption in some cases):
//
#if !defined(__SGI_STL_OWN_IOSTREAMS) && !defined(__STL_USE_NEW_IOSTREAMS)
#  define BOOST_NO_STD_LOCALE
#endif

//
// No template iterator constructors, or std::allocator
// without member templates:
//
#if !defined(__STL_MEMBER_TEMPLATES)
#  define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  define BOOST_NO_STD_ALLOCATOR
#endif

//
// We always have SGI style hash_set, hash_map, and slist:
//
#define BOOST_HAS_HASH
#define BOOST_HAS_SLIST

//
// If this is GNU libstdc++2, then no <limits> and no std::wstring:
//
#if (defined(__GNUC__) && (__GNUC__ < 3))
#  include <string>
#  if defined(__BASTRING__)
#     define BOOST_NO_LIMITS
#     define BOOST_NO_STD_WSTRING
#  endif
#endif

//
// There is no standard iterator unless we have namespace support:
//
#if !defined(__STL_USE_NAMESPACES)
#  define BOOST_NO_STD_ITERATOR
#endif

#define BOOST_STDLIB "SGI standard library"
