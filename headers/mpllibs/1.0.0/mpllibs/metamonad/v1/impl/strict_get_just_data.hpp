#ifndef MPLLIBS_METAMONAD_V1_IMPL_STRICT_GET_JUST_DATA_HPP
#define MPLLIBS_METAMONAD_V1_IMPL_STRICT_GET_JUST_DATA_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metamonad/v1/fwd/maybe.hpp>

namespace mpllibs
{
  namespace metamonad
  {
    namespace v1
    {
      namespace impl
      {
        template <class T>
        struct strict_get_just_data;

        template <class T>
        struct strict_get_just_data<just<T> > : T {};
      }
    }
  }
}

#endif

