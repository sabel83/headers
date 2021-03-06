#ifndef BOOST_PREPROCESSOR_ASSERT_MSG_HPP
#define BOOST_PREPROCESSOR_ASSERT_MSG_HPP

//  Copyright (C) 2001
//  Housemarque, Inc.
//  http://www.housemarque.com
//  
//  Permission to copy, use, modify, sell and distribute this software is
//  granted provided this copyright notice appears in all copies. This
//  software is provided "as is" without express or implied warranty, and
//  with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

/*! \file

<a href="../../../../boost/preprocessor/assert_msg.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_EMPTY_HPP
#  include <boost/preprocessor/empty.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_IDENTITY_HPP
#  include <boost/preprocessor/identity.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_IF_HPP
#  include <boost/preprocessor/if.hpp>
#endif

//! Expands to nothing if C != 0 and to MSG if C == 0.
#define BOOST_PREPROCESSOR_ASSERT_MSG(C,MSG) BOOST_PREPROCESSOR_IF(C,BOOST_PREPROCESSOR_EMPTY,BOOST_PREPROCESSOR_IDENTITY(MSG))()
#endif
