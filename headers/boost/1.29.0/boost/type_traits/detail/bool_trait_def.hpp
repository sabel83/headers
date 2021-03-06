//-----------------------------------------------------------------------------
// boost/type_traits/detail/bool_trait_def.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

// no include guards, the header is intended for multiple inclusion!

#include "boost/type_traits/detail/template_arity_spec.hpp"
#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/config.hpp"

#if !defined(BOOST_MSVC) || BOOST_MSVC > 1200
#   define BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) /**/
#else
#   define BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    typedef mpl::bool_c< C > base_; \
    using base_::value; \
    /**/
#endif

#define BOOST_TT_AUX_BOOL_TRAIT_DEF1(trait,T,C) \
template< typename T > struct trait \
    : mpl::bool_c< C > \
{ \
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,trait,(T)) \
}; \
\
BOOST_TT_AUX_TEMPLATE_ARITY_SPEC(1,trait) \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_DEF2(trait,T1,T2,C) \
template< typename T1, typename T2 > struct trait \
    : mpl::bool_c< C > \
{ \
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,trait,(T1,T2)) \
}; \
\
BOOST_TT_AUX_TEMPLATE_ARITY_SPEC(2,trait) \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp,C) \
template<> struct trait<sp> \
    : mpl::bool_c< C > \
{ \
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,trait,(sp)) \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_SPEC2(trait,sp1,sp2,C) \
template<> struct trait<sp1,sp2> \
    : mpl::bool_c< C > \
{ \
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,trait,(sp1,sp2)) \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_1(param,trait,sp,C) \
template< param > struct trait<sp> \
    : mpl::bool_c< C > \
{ \
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_2(param1,param2,trait,sp,C) \
template< param1, param2 > struct trait<sp> \
    : mpl::bool_c< C > \
{ \
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_1(param,trait,sp1,sp2,C) \
template< param > struct trait<sp1,sp2> \
    : mpl::bool_c< C > \
{ \
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,trait,(sp1,sp2)) \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(param1,param2,trait,sp1,sp2,C) \
template< param1, param2 > struct trait<sp1,sp2> \
    : mpl::bool_c< C > \
{ \
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(C) \
}; \
/**/

#ifndef BOOST_NO_CV_SPECIALIZATIONS
#   define BOOST_TT_AUX_BOOL_TRAIT_CV_SPEC1(trait,sp,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp const,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp volatile,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp const volatile,value) \
    /**/
#else
#   define BOOST_TT_AUX_BOOL_TRAIT_CV_SPEC1(trait,sp,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp,value) \
    /**/
#endif
