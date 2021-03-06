#ifndef BOOST_DETAIL_SP_COUNTED_BASE_CW_PPC_HPP_INCLUDED
#define BOOST_DETAIL_SP_COUNTED_BASE_CW_PPC_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_cw_ppc.hpp - CodeWarrior on PowerPC
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
//  Lock-free algorithm by Alexander Terekhov
//
//  Thanks to Ben Hitchings for the #weak + (#shared != 0)
//  formulation
//

#include <typeinfo>

namespace boost
{

namespace detail
{

inline void atomic_increment( register long * pw )
{
    asm
    {
loop:

    lwarx   r4, 0, r3
    addi    r4, r4, 1
    stwcx.  r4, 0, r3
    bne-    loop
    }
}

inline long atomic_decrement( register long * pw )
{
    asm
    {
    sync

loop:

    lwarx   r4, 0, r3
    addi    r4, r4, -1
    stwcx.  r4, 0, r3
    bne-    loop

    mr      r3, r4

    isync
    }
}

inline long atomic_conditional_increment( register long * pw )
{
    asm
    {
loop:

    lwarx   r4, 0, r3
    cmpwi   r4, 0
    beq     store

    addi    r4, r4, 1

store:

    stwcx.  r4, 0, r3
    bne-    loop

    mr      r3, r4
    }
}

class sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    long use_count_;        // #shared
    long weak_count_;       // #weak + (#shared != 0)

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }

    virtual ~sp_counted_base() // nothrow
    {
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.

    virtual void destroy() // nothrow
    {
        delete this;
    }

    virtual void * get_deleter( std::type_info const & ti ) = 0;

    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }

    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }

    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }

    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        return static_cast<long const volatile &>( use_count_ );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_DETAIL_SP_COUNTED_BASE_CW_PPC_HPP_INCLUDED
