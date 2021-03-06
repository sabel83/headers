#ifndef BOOST_PREPROCESSOR_REPEAT_2ND_HPP
#define BOOST_PREPROCESSOR_REPEAT_2ND_HPP

/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

/** <p>Same as BOOST_PP_REPEAT(), but implemented independently.</p>

<h3>Test</h3>
<ul>
  <li><a href="../../test/repeat_2nd_test.cpp">repeat_2nd_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_REPEAT_2ND(COUNT,MACRO,DATA) BOOST_PP_REPEAT_2ND_DELAY(COUNT)(MACRO,DATA)

#define BOOST_PP_REPEAT_2ND_DELAY(C) BOOST_PP_REPEAT_2ND##C
#define BOOST_PP_REPEAT_2ND0(M,D)
#define BOOST_PP_REPEAT_2ND1(M,D) M(0,D)
#define BOOST_PP_REPEAT_2ND2(M,D) M(0,D) M(1,D)
#define BOOST_PP_REPEAT_2ND3(M,D) M(0,D) M(1,D) M(2,D)
#define BOOST_PP_REPEAT_2ND4(M,D) M(0,D) M(1,D) M(2,D) M(3,D)
#define BOOST_PP_REPEAT_2ND5(M,D) BOOST_PP_REPEAT_2ND4(M,D) M(4,D)
#define BOOST_PP_REPEAT_2ND6(M,D) BOOST_PP_REPEAT_2ND5(M,D) M(5,D)
#define BOOST_PP_REPEAT_2ND7(M,D) BOOST_PP_REPEAT_2ND6(M,D) M(6,D)
#define BOOST_PP_REPEAT_2ND8(M,D) BOOST_PP_REPEAT_2ND7(M,D) M(7,D)
#define BOOST_PP_REPEAT_2ND9(M,D) BOOST_PP_REPEAT_2ND8(M,D) M(8,D)
#define BOOST_PP_REPEAT_2ND10(M,D) BOOST_PP_REPEAT_2ND9(M,D) M(9,D)
#define BOOST_PP_REPEAT_2ND11(M,D) BOOST_PP_REPEAT_2ND10(M,D) M(10,D)
#define BOOST_PP_REPEAT_2ND12(M,D) BOOST_PP_REPEAT_2ND11(M,D) M(11,D)
#define BOOST_PP_REPEAT_2ND13(M,D) BOOST_PP_REPEAT_2ND12(M,D) M(12,D)
#define BOOST_PP_REPEAT_2ND14(M,D) BOOST_PP_REPEAT_2ND13(M,D) M(13,D)
#define BOOST_PP_REPEAT_2ND15(M,D) BOOST_PP_REPEAT_2ND14(M,D) M(14,D)
#define BOOST_PP_REPEAT_2ND16(M,D) BOOST_PP_REPEAT_2ND15(M,D) M(15,D)
#define BOOST_PP_REPEAT_2ND17(M,D) BOOST_PP_REPEAT_2ND16(M,D) M(16,D)
#define BOOST_PP_REPEAT_2ND18(M,D) BOOST_PP_REPEAT_2ND17(M,D) M(17,D)
#define BOOST_PP_REPEAT_2ND19(M,D) BOOST_PP_REPEAT_2ND18(M,D) M(18,D)
#define BOOST_PP_REPEAT_2ND20(M,D) BOOST_PP_REPEAT_2ND19(M,D) M(19,D)
#define BOOST_PP_REPEAT_2ND21(M,D) BOOST_PP_REPEAT_2ND20(M,D) M(20,D)
#define BOOST_PP_REPEAT_2ND22(M,D) BOOST_PP_REPEAT_2ND21(M,D) M(21,D)
#define BOOST_PP_REPEAT_2ND23(M,D) BOOST_PP_REPEAT_2ND22(M,D) M(22,D)
#define BOOST_PP_REPEAT_2ND24(M,D) BOOST_PP_REPEAT_2ND23(M,D) M(23,D)
#define BOOST_PP_REPEAT_2ND25(M,D) BOOST_PP_REPEAT_2ND24(M,D) M(24,D)
#define BOOST_PP_REPEAT_2ND26(M,D) BOOST_PP_REPEAT_2ND25(M,D) M(25,D)
#define BOOST_PP_REPEAT_2ND27(M,D) BOOST_PP_REPEAT_2ND26(M,D) M(26,D)
#define BOOST_PP_REPEAT_2ND28(M,D) BOOST_PP_REPEAT_2ND27(M,D) M(27,D)
#define BOOST_PP_REPEAT_2ND29(M,D) BOOST_PP_REPEAT_2ND28(M,D) M(28,D)
#define BOOST_PP_REPEAT_2ND30(M,D) BOOST_PP_REPEAT_2ND29(M,D) M(29,D)
#define BOOST_PP_REPEAT_2ND31(M,D) BOOST_PP_REPEAT_2ND30(M,D) M(30,D)
#define BOOST_PP_REPEAT_2ND32(M,D) BOOST_PP_REPEAT_2ND31(M,D) M(31,D)
#define BOOST_PP_REPEAT_2ND33(M,D) BOOST_PP_REPEAT_2ND32(M,D) M(32,D)
#define BOOST_PP_REPEAT_2ND34(M,D) BOOST_PP_REPEAT_2ND33(M,D) M(33,D)
#define BOOST_PP_REPEAT_2ND35(M,D) BOOST_PP_REPEAT_2ND34(M,D) M(34,D)
#define BOOST_PP_REPEAT_2ND36(M,D) BOOST_PP_REPEAT_2ND35(M,D) M(35,D)
#define BOOST_PP_REPEAT_2ND37(M,D) BOOST_PP_REPEAT_2ND36(M,D) M(36,D)
#define BOOST_PP_REPEAT_2ND38(M,D) BOOST_PP_REPEAT_2ND37(M,D) M(37,D)
#define BOOST_PP_REPEAT_2ND39(M,D) BOOST_PP_REPEAT_2ND38(M,D) M(38,D)
#define BOOST_PP_REPEAT_2ND40(M,D) BOOST_PP_REPEAT_2ND39(M,D) M(39,D)
#define BOOST_PP_REPEAT_2ND41(M,D) BOOST_PP_REPEAT_2ND40(M,D) M(40,D)
#define BOOST_PP_REPEAT_2ND42(M,D) BOOST_PP_REPEAT_2ND41(M,D) M(41,D)
#define BOOST_PP_REPEAT_2ND43(M,D) BOOST_PP_REPEAT_2ND42(M,D) M(42,D)
#define BOOST_PP_REPEAT_2ND44(M,D) BOOST_PP_REPEAT_2ND43(M,D) M(43,D)
#define BOOST_PP_REPEAT_2ND45(M,D) BOOST_PP_REPEAT_2ND44(M,D) M(44,D)
#define BOOST_PP_REPEAT_2ND46(M,D) BOOST_PP_REPEAT_2ND45(M,D) M(45,D)
#define BOOST_PP_REPEAT_2ND47(M,D) BOOST_PP_REPEAT_2ND46(M,D) M(46,D)
#define BOOST_PP_REPEAT_2ND48(M,D) BOOST_PP_REPEAT_2ND47(M,D) M(47,D)
#define BOOST_PP_REPEAT_2ND49(M,D) BOOST_PP_REPEAT_2ND48(M,D) M(48,D)
#define BOOST_PP_REPEAT_2ND50(M,D) BOOST_PP_REPEAT_2ND49(M,D) M(49,D)
#define BOOST_PP_REPEAT_2ND51(M,D) BOOST_PP_REPEAT_2ND50(M,D) M(50,D)
#define BOOST_PP_REPEAT_2ND52(M,D) BOOST_PP_REPEAT_2ND51(M,D) M(51,D)
#define BOOST_PP_REPEAT_2ND53(M,D) BOOST_PP_REPEAT_2ND52(M,D) M(52,D)
#define BOOST_PP_REPEAT_2ND54(M,D) BOOST_PP_REPEAT_2ND53(M,D) M(53,D)
#define BOOST_PP_REPEAT_2ND55(M,D) BOOST_PP_REPEAT_2ND54(M,D) M(54,D)
#define BOOST_PP_REPEAT_2ND56(M,D) BOOST_PP_REPEAT_2ND55(M,D) M(55,D)
#define BOOST_PP_REPEAT_2ND57(M,D) BOOST_PP_REPEAT_2ND56(M,D) M(56,D)
#define BOOST_PP_REPEAT_2ND58(M,D) BOOST_PP_REPEAT_2ND57(M,D) M(57,D)
#define BOOST_PP_REPEAT_2ND59(M,D) BOOST_PP_REPEAT_2ND58(M,D) M(58,D)
#define BOOST_PP_REPEAT_2ND60(M,D) BOOST_PP_REPEAT_2ND59(M,D) M(59,D)
#define BOOST_PP_REPEAT_2ND61(M,D) BOOST_PP_REPEAT_2ND60(M,D) M(60,D)
#define BOOST_PP_REPEAT_2ND62(M,D) BOOST_PP_REPEAT_2ND61(M,D) M(61,D)
#define BOOST_PP_REPEAT_2ND63(M,D) BOOST_PP_REPEAT_2ND62(M,D) M(62,D)
#define BOOST_PP_REPEAT_2ND64(M,D) BOOST_PP_REPEAT_2ND63(M,D) M(63,D)
#define BOOST_PP_REPEAT_2ND65(M,D) BOOST_PP_REPEAT_2ND64(M,D) M(64,D)
#define BOOST_PP_REPEAT_2ND66(M,D) BOOST_PP_REPEAT_2ND65(M,D) M(65,D)
#define BOOST_PP_REPEAT_2ND67(M,D) BOOST_PP_REPEAT_2ND66(M,D) M(66,D)
#define BOOST_PP_REPEAT_2ND68(M,D) BOOST_PP_REPEAT_2ND67(M,D) M(67,D)
#define BOOST_PP_REPEAT_2ND69(M,D) BOOST_PP_REPEAT_2ND68(M,D) M(68,D)
#define BOOST_PP_REPEAT_2ND70(M,D) BOOST_PP_REPEAT_2ND69(M,D) M(69,D)
#define BOOST_PP_REPEAT_2ND71(M,D) BOOST_PP_REPEAT_2ND70(M,D) M(70,D)
#define BOOST_PP_REPEAT_2ND72(M,D) BOOST_PP_REPEAT_2ND71(M,D) M(71,D)
#define BOOST_PP_REPEAT_2ND73(M,D) BOOST_PP_REPEAT_2ND72(M,D) M(72,D)
#define BOOST_PP_REPEAT_2ND74(M,D) BOOST_PP_REPEAT_2ND73(M,D) M(73,D)
#define BOOST_PP_REPEAT_2ND75(M,D) BOOST_PP_REPEAT_2ND74(M,D) M(74,D)
#define BOOST_PP_REPEAT_2ND76(M,D) BOOST_PP_REPEAT_2ND75(M,D) M(75,D)
#define BOOST_PP_REPEAT_2ND77(M,D) BOOST_PP_REPEAT_2ND76(M,D) M(76,D)
#define BOOST_PP_REPEAT_2ND78(M,D) BOOST_PP_REPEAT_2ND77(M,D) M(77,D)
#define BOOST_PP_REPEAT_2ND79(M,D) BOOST_PP_REPEAT_2ND78(M,D) M(78,D)
#define BOOST_PP_REPEAT_2ND80(M,D) BOOST_PP_REPEAT_2ND79(M,D) M(79,D)
#define BOOST_PP_REPEAT_2ND81(M,D) BOOST_PP_REPEAT_2ND80(M,D) M(80,D)
#define BOOST_PP_REPEAT_2ND82(M,D) BOOST_PP_REPEAT_2ND81(M,D) M(81,D)
#define BOOST_PP_REPEAT_2ND83(M,D) BOOST_PP_REPEAT_2ND82(M,D) M(82,D)
#define BOOST_PP_REPEAT_2ND84(M,D) BOOST_PP_REPEAT_2ND83(M,D) M(83,D)
#define BOOST_PP_REPEAT_2ND85(M,D) BOOST_PP_REPEAT_2ND84(M,D) M(84,D)
#define BOOST_PP_REPEAT_2ND86(M,D) BOOST_PP_REPEAT_2ND85(M,D) M(85,D)
#define BOOST_PP_REPEAT_2ND87(M,D) BOOST_PP_REPEAT_2ND86(M,D) M(86,D)
#define BOOST_PP_REPEAT_2ND88(M,D) BOOST_PP_REPEAT_2ND87(M,D) M(87,D)
#define BOOST_PP_REPEAT_2ND89(M,D) BOOST_PP_REPEAT_2ND88(M,D) M(88,D)
#define BOOST_PP_REPEAT_2ND90(M,D) BOOST_PP_REPEAT_2ND89(M,D) M(89,D)
#define BOOST_PP_REPEAT_2ND91(M,D) BOOST_PP_REPEAT_2ND90(M,D) M(90,D)
#define BOOST_PP_REPEAT_2ND92(M,D) BOOST_PP_REPEAT_2ND91(M,D) M(91,D)
#define BOOST_PP_REPEAT_2ND93(M,D) BOOST_PP_REPEAT_2ND92(M,D) M(92,D)
#define BOOST_PP_REPEAT_2ND94(M,D) BOOST_PP_REPEAT_2ND93(M,D) M(93,D)
#define BOOST_PP_REPEAT_2ND95(M,D) BOOST_PP_REPEAT_2ND94(M,D) M(94,D)
#define BOOST_PP_REPEAT_2ND96(M,D) BOOST_PP_REPEAT_2ND95(M,D) M(95,D)
#define BOOST_PP_REPEAT_2ND97(M,D) BOOST_PP_REPEAT_2ND96(M,D) M(96,D)
#define BOOST_PP_REPEAT_2ND98(M,D) BOOST_PP_REPEAT_2ND97(M,D) M(97,D)
#define BOOST_PP_REPEAT_2ND99(M,D) BOOST_PP_REPEAT_2ND98(M,D) M(98,D)
#define BOOST_PP_REPEAT_2ND100(M,D) BOOST_PP_REPEAT_2ND99(M,D) M(99,D)
#define BOOST_PP_REPEAT_2ND101(M,D) BOOST_PP_REPEAT_2ND100(M,D) M(100,D)
#define BOOST_PP_REPEAT_2ND102(M,D) BOOST_PP_REPEAT_2ND101(M,D) M(101,D)
#define BOOST_PP_REPEAT_2ND103(M,D) BOOST_PP_REPEAT_2ND102(M,D) M(102,D)
#define BOOST_PP_REPEAT_2ND104(M,D) BOOST_PP_REPEAT_2ND103(M,D) M(103,D)
#define BOOST_PP_REPEAT_2ND105(M,D) BOOST_PP_REPEAT_2ND104(M,D) M(104,D)
#define BOOST_PP_REPEAT_2ND106(M,D) BOOST_PP_REPEAT_2ND105(M,D) M(105,D)
#define BOOST_PP_REPEAT_2ND107(M,D) BOOST_PP_REPEAT_2ND106(M,D) M(106,D)
#define BOOST_PP_REPEAT_2ND108(M,D) BOOST_PP_REPEAT_2ND107(M,D) M(107,D)
#define BOOST_PP_REPEAT_2ND109(M,D) BOOST_PP_REPEAT_2ND108(M,D) M(108,D)
#define BOOST_PP_REPEAT_2ND110(M,D) BOOST_PP_REPEAT_2ND109(M,D) M(109,D)
#define BOOST_PP_REPEAT_2ND111(M,D) BOOST_PP_REPEAT_2ND110(M,D) M(110,D)
#define BOOST_PP_REPEAT_2ND112(M,D) BOOST_PP_REPEAT_2ND111(M,D) M(111,D)
#define BOOST_PP_REPEAT_2ND113(M,D) BOOST_PP_REPEAT_2ND112(M,D) M(112,D)
#define BOOST_PP_REPEAT_2ND114(M,D) BOOST_PP_REPEAT_2ND113(M,D) M(113,D)
#define BOOST_PP_REPEAT_2ND115(M,D) BOOST_PP_REPEAT_2ND114(M,D) M(114,D)
#define BOOST_PP_REPEAT_2ND116(M,D) BOOST_PP_REPEAT_2ND115(M,D) M(115,D)
#define BOOST_PP_REPEAT_2ND117(M,D) BOOST_PP_REPEAT_2ND116(M,D) M(116,D)
#define BOOST_PP_REPEAT_2ND118(M,D) BOOST_PP_REPEAT_2ND117(M,D) M(117,D)
#define BOOST_PP_REPEAT_2ND119(M,D) BOOST_PP_REPEAT_2ND118(M,D) M(118,D)
#define BOOST_PP_REPEAT_2ND120(M,D) BOOST_PP_REPEAT_2ND119(M,D) M(119,D)
#define BOOST_PP_REPEAT_2ND121(M,D) BOOST_PP_REPEAT_2ND120(M,D) M(120,D)
#define BOOST_PP_REPEAT_2ND122(M,D) BOOST_PP_REPEAT_2ND121(M,D) M(121,D)
#define BOOST_PP_REPEAT_2ND123(M,D) BOOST_PP_REPEAT_2ND122(M,D) M(122,D)
#define BOOST_PP_REPEAT_2ND124(M,D) BOOST_PP_REPEAT_2ND123(M,D) M(123,D)
#define BOOST_PP_REPEAT_2ND125(M,D) BOOST_PP_REPEAT_2ND124(M,D) M(124,D)
#define BOOST_PP_REPEAT_2ND126(M,D) BOOST_PP_REPEAT_2ND125(M,D) M(125,D)
#define BOOST_PP_REPEAT_2ND127(M,D) BOOST_PP_REPEAT_2ND126(M,D) M(126,D)
#define BOOST_PP_REPEAT_2ND128(M,D) BOOST_PP_REPEAT_2ND127(M,D) M(127,D)

/* <p>Obsolete. Use BOOST_PP_REPEAT_2ND().</p> */
#define BOOST_PREPROCESSOR_REPEAT_2ND(C,M,D) BOOST_PP_REPEAT_2ND(C,M,D)
#endif
