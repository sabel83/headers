#ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP

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

<a href="../../../../boost/preprocessor/arithmetic/sub.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_DEC_HPP
#  include <boost/preprocessor/dec.hpp>
#endif

//! Expands to the difference of X and Y.
#define BOOST_PREPROCESSOR_SUB(X,Y) BOOST_PREPROCESSOR_SUB_DELAY(X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_SUB_DELAY(X,Y) BOOST_PREPROCESSOR_SUB##Y(X)
#define BOOST_PREPROCESSOR_SUB0(Y) Y
#define BOOST_PREPROCESSOR_SUB1(Y) BOOST_PREPROCESSOR_DEC(Y)
#define BOOST_PREPROCESSOR_SUB2(Y) BOOST_PREPROCESSOR_DEC(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB3(Y) BOOST_PREPROCESSOR_SUB2(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB4(Y) BOOST_PREPROCESSOR_SUB3(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB5(Y) BOOST_PREPROCESSOR_SUB4(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB6(Y) BOOST_PREPROCESSOR_SUB5(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB7(Y) BOOST_PREPROCESSOR_SUB6(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB8(Y) BOOST_PREPROCESSOR_SUB7(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB9(Y) BOOST_PREPROCESSOR_SUB8(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB10(Y) BOOST_PREPROCESSOR_SUB9(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB11(Y) BOOST_PREPROCESSOR_SUB10(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB12(Y) BOOST_PREPROCESSOR_SUB11(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB13(Y) BOOST_PREPROCESSOR_SUB12(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB14(Y) BOOST_PREPROCESSOR_SUB13(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB15(Y) BOOST_PREPROCESSOR_SUB14(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB16(Y) BOOST_PREPROCESSOR_SUB15(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB17(Y) BOOST_PREPROCESSOR_SUB16(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB18(Y) BOOST_PREPROCESSOR_SUB17(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB19(Y) BOOST_PREPROCESSOR_SUB18(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB20(Y) BOOST_PREPROCESSOR_SUB19(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB21(Y) BOOST_PREPROCESSOR_SUB20(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB22(Y) BOOST_PREPROCESSOR_SUB21(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB23(Y) BOOST_PREPROCESSOR_SUB22(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB24(Y) BOOST_PREPROCESSOR_SUB23(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB25(Y) BOOST_PREPROCESSOR_SUB24(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB26(Y) BOOST_PREPROCESSOR_SUB25(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB27(Y) BOOST_PREPROCESSOR_SUB26(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB28(Y) BOOST_PREPROCESSOR_SUB27(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB29(Y) BOOST_PREPROCESSOR_SUB28(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB30(Y) BOOST_PREPROCESSOR_SUB29(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB31(Y) BOOST_PREPROCESSOR_SUB30(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB32(Y) BOOST_PREPROCESSOR_SUB31(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB33(Y) BOOST_PREPROCESSOR_SUB32(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB34(Y) BOOST_PREPROCESSOR_SUB33(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB35(Y) BOOST_PREPROCESSOR_SUB34(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB36(Y) BOOST_PREPROCESSOR_SUB35(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB37(Y) BOOST_PREPROCESSOR_SUB36(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB38(Y) BOOST_PREPROCESSOR_SUB37(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB39(Y) BOOST_PREPROCESSOR_SUB38(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB40(Y) BOOST_PREPROCESSOR_SUB39(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB41(Y) BOOST_PREPROCESSOR_SUB40(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB42(Y) BOOST_PREPROCESSOR_SUB41(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB43(Y) BOOST_PREPROCESSOR_SUB42(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB44(Y) BOOST_PREPROCESSOR_SUB43(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB45(Y) BOOST_PREPROCESSOR_SUB44(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB46(Y) BOOST_PREPROCESSOR_SUB45(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB47(Y) BOOST_PREPROCESSOR_SUB46(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB48(Y) BOOST_PREPROCESSOR_SUB47(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB49(Y) BOOST_PREPROCESSOR_SUB48(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB50(Y) BOOST_PREPROCESSOR_SUB49(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB51(Y) BOOST_PREPROCESSOR_SUB50(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB52(Y) BOOST_PREPROCESSOR_SUB51(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB53(Y) BOOST_PREPROCESSOR_SUB52(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB54(Y) BOOST_PREPROCESSOR_SUB53(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB55(Y) BOOST_PREPROCESSOR_SUB54(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB56(Y) BOOST_PREPROCESSOR_SUB55(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB57(Y) BOOST_PREPROCESSOR_SUB56(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB58(Y) BOOST_PREPROCESSOR_SUB57(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB59(Y) BOOST_PREPROCESSOR_SUB58(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB60(Y) BOOST_PREPROCESSOR_SUB59(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB61(Y) BOOST_PREPROCESSOR_SUB60(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB62(Y) BOOST_PREPROCESSOR_SUB61(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB63(Y) BOOST_PREPROCESSOR_SUB62(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB64(Y) BOOST_PREPROCESSOR_SUB63(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB65(Y) BOOST_PREPROCESSOR_SUB64(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB66(Y) BOOST_PREPROCESSOR_SUB65(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB67(Y) BOOST_PREPROCESSOR_SUB66(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB68(Y) BOOST_PREPROCESSOR_SUB67(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB69(Y) BOOST_PREPROCESSOR_SUB68(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB70(Y) BOOST_PREPROCESSOR_SUB69(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB71(Y) BOOST_PREPROCESSOR_SUB70(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB72(Y) BOOST_PREPROCESSOR_SUB71(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB73(Y) BOOST_PREPROCESSOR_SUB72(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB74(Y) BOOST_PREPROCESSOR_SUB73(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB75(Y) BOOST_PREPROCESSOR_SUB74(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB76(Y) BOOST_PREPROCESSOR_SUB75(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB77(Y) BOOST_PREPROCESSOR_SUB76(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB78(Y) BOOST_PREPROCESSOR_SUB77(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB79(Y) BOOST_PREPROCESSOR_SUB78(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB80(Y) BOOST_PREPROCESSOR_SUB79(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB81(Y) BOOST_PREPROCESSOR_SUB80(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB82(Y) BOOST_PREPROCESSOR_SUB81(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB83(Y) BOOST_PREPROCESSOR_SUB82(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB84(Y) BOOST_PREPROCESSOR_SUB83(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB85(Y) BOOST_PREPROCESSOR_SUB84(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB86(Y) BOOST_PREPROCESSOR_SUB85(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB87(Y) BOOST_PREPROCESSOR_SUB86(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB88(Y) BOOST_PREPROCESSOR_SUB87(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB89(Y) BOOST_PREPROCESSOR_SUB88(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB90(Y) BOOST_PREPROCESSOR_SUB89(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB91(Y) BOOST_PREPROCESSOR_SUB90(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB92(Y) BOOST_PREPROCESSOR_SUB91(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB93(Y) BOOST_PREPROCESSOR_SUB92(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB94(Y) BOOST_PREPROCESSOR_SUB93(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB95(Y) BOOST_PREPROCESSOR_SUB94(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB96(Y) BOOST_PREPROCESSOR_SUB95(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB97(Y) BOOST_PREPROCESSOR_SUB96(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB98(Y) BOOST_PREPROCESSOR_SUB97(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB99(Y) BOOST_PREPROCESSOR_SUB98(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB100(Y) BOOST_PREPROCESSOR_SUB99(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB101(Y) BOOST_PREPROCESSOR_SUB100(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB102(Y) BOOST_PREPROCESSOR_SUB101(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB103(Y) BOOST_PREPROCESSOR_SUB102(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB104(Y) BOOST_PREPROCESSOR_SUB103(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB105(Y) BOOST_PREPROCESSOR_SUB104(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB106(Y) BOOST_PREPROCESSOR_SUB105(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB107(Y) BOOST_PREPROCESSOR_SUB106(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB108(Y) BOOST_PREPROCESSOR_SUB107(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB109(Y) BOOST_PREPROCESSOR_SUB108(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB110(Y) BOOST_PREPROCESSOR_SUB109(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB111(Y) BOOST_PREPROCESSOR_SUB110(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB112(Y) BOOST_PREPROCESSOR_SUB111(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB113(Y) BOOST_PREPROCESSOR_SUB112(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB114(Y) BOOST_PREPROCESSOR_SUB113(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB115(Y) BOOST_PREPROCESSOR_SUB114(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB116(Y) BOOST_PREPROCESSOR_SUB115(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB117(Y) BOOST_PREPROCESSOR_SUB116(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB118(Y) BOOST_PREPROCESSOR_SUB117(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB119(Y) BOOST_PREPROCESSOR_SUB118(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB120(Y) BOOST_PREPROCESSOR_SUB119(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB121(Y) BOOST_PREPROCESSOR_SUB120(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB122(Y) BOOST_PREPROCESSOR_SUB121(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB123(Y) BOOST_PREPROCESSOR_SUB122(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB124(Y) BOOST_PREPROCESSOR_SUB123(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB125(Y) BOOST_PREPROCESSOR_SUB124(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB126(Y) BOOST_PREPROCESSOR_SUB125(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB127(Y) BOOST_PREPROCESSOR_SUB126(BOOST_PREPROCESSOR_DEC(Y))
#define BOOST_PREPROCESSOR_SUB128(Y) BOOST_PREPROCESSOR_SUB127(BOOST_PREPROCESSOR_DEC(Y))
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
