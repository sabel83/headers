#ifndef BOOST_PREPROCESSOR_REPEAT_HPP
#define BOOST_PREPROCESSOR_REPEAT_HPP

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

/** <p>Repeats the macro <code>M(I,P)</code> for I = [0,N-1[.</p>

<p>In other words, expands to the sequence:</p>

<pre>
  M(0,P) M(1,P) ... M(BOOST_PP_DEC(N),P)
</pre>

<h3>2D and 3D repetition</h3>

<p>2D and 3D repetition are supported with the BOOST_PP_REPEAT_2ND() and
BOOST_PP_REPEAT_3RD() macros.</p>

<h3>Example</h3>
<ul>
  <li><a href="../../example/repeat_2d.c">repeat_2d.c</a></li>
</ul>

<h3>See</h3>
<ul>
  <li>BOOST_PP_FOR()</li>
  <li>BOOST_PP_LIMIT_MAG</li>
</ul>
*/
#define BOOST_PP_REPEAT(N,M,P) BOOST_PP_REPEAT_DELAY(N,M,P)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_REPEAT_DELAY(N,M,P) BOOST_PP_REPEAT##N(M,P)
#define BOOST_PP_REPEAT0(M,P)
#define BOOST_PP_REPEAT1(M,P) M(0,P)
#define BOOST_PP_REPEAT2(M,P) M(0,P) M(1,P)
#define BOOST_PP_REPEAT3(M,P) M(0,P) M(1,P) M(2,P)
#define BOOST_PP_REPEAT4(M,P) M(0,P) M(1,P) M(2,P) M(3,P)
#define BOOST_PP_REPEAT5(M,P) BOOST_PP_REPEAT4(M,P) M(4,P)
#define BOOST_PP_REPEAT6(M,P) BOOST_PP_REPEAT5(M,P) M(5,P)
#define BOOST_PP_REPEAT7(M,P) BOOST_PP_REPEAT6(M,P) M(6,P)
#define BOOST_PP_REPEAT8(M,P) BOOST_PP_REPEAT7(M,P) M(7,P)
#define BOOST_PP_REPEAT9(M,P) BOOST_PP_REPEAT8(M,P) M(8,P)
#define BOOST_PP_REPEAT10(M,P) BOOST_PP_REPEAT9(M,P) M(9,P)
#define BOOST_PP_REPEAT11(M,P) BOOST_PP_REPEAT10(M,P) M(10,P)
#define BOOST_PP_REPEAT12(M,P) BOOST_PP_REPEAT11(M,P) M(11,P)
#define BOOST_PP_REPEAT13(M,P) BOOST_PP_REPEAT12(M,P) M(12,P)
#define BOOST_PP_REPEAT14(M,P) BOOST_PP_REPEAT13(M,P) M(13,P)
#define BOOST_PP_REPEAT15(M,P) BOOST_PP_REPEAT14(M,P) M(14,P)
#define BOOST_PP_REPEAT16(M,P) BOOST_PP_REPEAT15(M,P) M(15,P)
#define BOOST_PP_REPEAT17(M,P) BOOST_PP_REPEAT16(M,P) M(16,P)
#define BOOST_PP_REPEAT18(M,P) BOOST_PP_REPEAT17(M,P) M(17,P)
#define BOOST_PP_REPEAT19(M,P) BOOST_PP_REPEAT18(M,P) M(18,P)
#define BOOST_PP_REPEAT20(M,P) BOOST_PP_REPEAT19(M,P) M(19,P)
#define BOOST_PP_REPEAT21(M,P) BOOST_PP_REPEAT20(M,P) M(20,P)
#define BOOST_PP_REPEAT22(M,P) BOOST_PP_REPEAT21(M,P) M(21,P)
#define BOOST_PP_REPEAT23(M,P) BOOST_PP_REPEAT22(M,P) M(22,P)
#define BOOST_PP_REPEAT24(M,P) BOOST_PP_REPEAT23(M,P) M(23,P)
#define BOOST_PP_REPEAT25(M,P) BOOST_PP_REPEAT24(M,P) M(24,P)
#define BOOST_PP_REPEAT26(M,P) BOOST_PP_REPEAT25(M,P) M(25,P)
#define BOOST_PP_REPEAT27(M,P) BOOST_PP_REPEAT26(M,P) M(26,P)
#define BOOST_PP_REPEAT28(M,P) BOOST_PP_REPEAT27(M,P) M(27,P)
#define BOOST_PP_REPEAT29(M,P) BOOST_PP_REPEAT28(M,P) M(28,P)
#define BOOST_PP_REPEAT30(M,P) BOOST_PP_REPEAT29(M,P) M(29,P)
#define BOOST_PP_REPEAT31(M,P) BOOST_PP_REPEAT30(M,P) M(30,P)
#define BOOST_PP_REPEAT32(M,P) BOOST_PP_REPEAT31(M,P) M(31,P)
#define BOOST_PP_REPEAT33(M,P) BOOST_PP_REPEAT32(M,P) M(32,P)
#define BOOST_PP_REPEAT34(M,P) BOOST_PP_REPEAT33(M,P) M(33,P)
#define BOOST_PP_REPEAT35(M,P) BOOST_PP_REPEAT34(M,P) M(34,P)
#define BOOST_PP_REPEAT36(M,P) BOOST_PP_REPEAT35(M,P) M(35,P)
#define BOOST_PP_REPEAT37(M,P) BOOST_PP_REPEAT36(M,P) M(36,P)
#define BOOST_PP_REPEAT38(M,P) BOOST_PP_REPEAT37(M,P) M(37,P)
#define BOOST_PP_REPEAT39(M,P) BOOST_PP_REPEAT38(M,P) M(38,P)
#define BOOST_PP_REPEAT40(M,P) BOOST_PP_REPEAT39(M,P) M(39,P)
#define BOOST_PP_REPEAT41(M,P) BOOST_PP_REPEAT40(M,P) M(40,P)
#define BOOST_PP_REPEAT42(M,P) BOOST_PP_REPEAT41(M,P) M(41,P)
#define BOOST_PP_REPEAT43(M,P) BOOST_PP_REPEAT42(M,P) M(42,P)
#define BOOST_PP_REPEAT44(M,P) BOOST_PP_REPEAT43(M,P) M(43,P)
#define BOOST_PP_REPEAT45(M,P) BOOST_PP_REPEAT44(M,P) M(44,P)
#define BOOST_PP_REPEAT46(M,P) BOOST_PP_REPEAT45(M,P) M(45,P)
#define BOOST_PP_REPEAT47(M,P) BOOST_PP_REPEAT46(M,P) M(46,P)
#define BOOST_PP_REPEAT48(M,P) BOOST_PP_REPEAT47(M,P) M(47,P)
#define BOOST_PP_REPEAT49(M,P) BOOST_PP_REPEAT48(M,P) M(48,P)
#define BOOST_PP_REPEAT50(M,P) BOOST_PP_REPEAT49(M,P) M(49,P)
#define BOOST_PP_REPEAT51(M,P) BOOST_PP_REPEAT50(M,P) M(50,P)
#define BOOST_PP_REPEAT52(M,P) BOOST_PP_REPEAT51(M,P) M(51,P)
#define BOOST_PP_REPEAT53(M,P) BOOST_PP_REPEAT52(M,P) M(52,P)
#define BOOST_PP_REPEAT54(M,P) BOOST_PP_REPEAT53(M,P) M(53,P)
#define BOOST_PP_REPEAT55(M,P) BOOST_PP_REPEAT54(M,P) M(54,P)
#define BOOST_PP_REPEAT56(M,P) BOOST_PP_REPEAT55(M,P) M(55,P)
#define BOOST_PP_REPEAT57(M,P) BOOST_PP_REPEAT56(M,P) M(56,P)
#define BOOST_PP_REPEAT58(M,P) BOOST_PP_REPEAT57(M,P) M(57,P)
#define BOOST_PP_REPEAT59(M,P) BOOST_PP_REPEAT58(M,P) M(58,P)
#define BOOST_PP_REPEAT60(M,P) BOOST_PP_REPEAT59(M,P) M(59,P)
#define BOOST_PP_REPEAT61(M,P) BOOST_PP_REPEAT60(M,P) M(60,P)
#define BOOST_PP_REPEAT62(M,P) BOOST_PP_REPEAT61(M,P) M(61,P)
#define BOOST_PP_REPEAT63(M,P) BOOST_PP_REPEAT62(M,P) M(62,P)
#define BOOST_PP_REPEAT64(M,P) BOOST_PP_REPEAT63(M,P) M(63,P)
#define BOOST_PP_REPEAT65(M,P) BOOST_PP_REPEAT64(M,P) M(64,P)
#define BOOST_PP_REPEAT66(M,P) BOOST_PP_REPEAT65(M,P) M(65,P)
#define BOOST_PP_REPEAT67(M,P) BOOST_PP_REPEAT66(M,P) M(66,P)
#define BOOST_PP_REPEAT68(M,P) BOOST_PP_REPEAT67(M,P) M(67,P)
#define BOOST_PP_REPEAT69(M,P) BOOST_PP_REPEAT68(M,P) M(68,P)
#define BOOST_PP_REPEAT70(M,P) BOOST_PP_REPEAT69(M,P) M(69,P)
#define BOOST_PP_REPEAT71(M,P) BOOST_PP_REPEAT70(M,P) M(70,P)
#define BOOST_PP_REPEAT72(M,P) BOOST_PP_REPEAT71(M,P) M(71,P)
#define BOOST_PP_REPEAT73(M,P) BOOST_PP_REPEAT72(M,P) M(72,P)
#define BOOST_PP_REPEAT74(M,P) BOOST_PP_REPEAT73(M,P) M(73,P)
#define BOOST_PP_REPEAT75(M,P) BOOST_PP_REPEAT74(M,P) M(74,P)
#define BOOST_PP_REPEAT76(M,P) BOOST_PP_REPEAT75(M,P) M(75,P)
#define BOOST_PP_REPEAT77(M,P) BOOST_PP_REPEAT76(M,P) M(76,P)
#define BOOST_PP_REPEAT78(M,P) BOOST_PP_REPEAT77(M,P) M(77,P)
#define BOOST_PP_REPEAT79(M,P) BOOST_PP_REPEAT78(M,P) M(78,P)
#define BOOST_PP_REPEAT80(M,P) BOOST_PP_REPEAT79(M,P) M(79,P)
#define BOOST_PP_REPEAT81(M,P) BOOST_PP_REPEAT80(M,P) M(80,P)
#define BOOST_PP_REPEAT82(M,P) BOOST_PP_REPEAT81(M,P) M(81,P)
#define BOOST_PP_REPEAT83(M,P) BOOST_PP_REPEAT82(M,P) M(82,P)
#define BOOST_PP_REPEAT84(M,P) BOOST_PP_REPEAT83(M,P) M(83,P)
#define BOOST_PP_REPEAT85(M,P) BOOST_PP_REPEAT84(M,P) M(84,P)
#define BOOST_PP_REPEAT86(M,P) BOOST_PP_REPEAT85(M,P) M(85,P)
#define BOOST_PP_REPEAT87(M,P) BOOST_PP_REPEAT86(M,P) M(86,P)
#define BOOST_PP_REPEAT88(M,P) BOOST_PP_REPEAT87(M,P) M(87,P)
#define BOOST_PP_REPEAT89(M,P) BOOST_PP_REPEAT88(M,P) M(88,P)
#define BOOST_PP_REPEAT90(M,P) BOOST_PP_REPEAT89(M,P) M(89,P)
#define BOOST_PP_REPEAT91(M,P) BOOST_PP_REPEAT90(M,P) M(90,P)
#define BOOST_PP_REPEAT92(M,P) BOOST_PP_REPEAT91(M,P) M(91,P)
#define BOOST_PP_REPEAT93(M,P) BOOST_PP_REPEAT92(M,P) M(92,P)
#define BOOST_PP_REPEAT94(M,P) BOOST_PP_REPEAT93(M,P) M(93,P)
#define BOOST_PP_REPEAT95(M,P) BOOST_PP_REPEAT94(M,P) M(94,P)
#define BOOST_PP_REPEAT96(M,P) BOOST_PP_REPEAT95(M,P) M(95,P)
#define BOOST_PP_REPEAT97(M,P) BOOST_PP_REPEAT96(M,P) M(96,P)
#define BOOST_PP_REPEAT98(M,P) BOOST_PP_REPEAT97(M,P) M(97,P)
#define BOOST_PP_REPEAT99(M,P) BOOST_PP_REPEAT98(M,P) M(98,P)
#define BOOST_PP_REPEAT100(M,P) BOOST_PP_REPEAT99(M,P) M(99,P)
#define BOOST_PP_REPEAT101(M,P) BOOST_PP_REPEAT100(M,P) M(100,P)
#define BOOST_PP_REPEAT102(M,P) BOOST_PP_REPEAT101(M,P) M(101,P)
#define BOOST_PP_REPEAT103(M,P) BOOST_PP_REPEAT102(M,P) M(102,P)
#define BOOST_PP_REPEAT104(M,P) BOOST_PP_REPEAT103(M,P) M(103,P)
#define BOOST_PP_REPEAT105(M,P) BOOST_PP_REPEAT104(M,P) M(104,P)
#define BOOST_PP_REPEAT106(M,P) BOOST_PP_REPEAT105(M,P) M(105,P)
#define BOOST_PP_REPEAT107(M,P) BOOST_PP_REPEAT106(M,P) M(106,P)
#define BOOST_PP_REPEAT108(M,P) BOOST_PP_REPEAT107(M,P) M(107,P)
#define BOOST_PP_REPEAT109(M,P) BOOST_PP_REPEAT108(M,P) M(108,P)
#define BOOST_PP_REPEAT110(M,P) BOOST_PP_REPEAT109(M,P) M(109,P)
#define BOOST_PP_REPEAT111(M,P) BOOST_PP_REPEAT110(M,P) M(110,P)
#define BOOST_PP_REPEAT112(M,P) BOOST_PP_REPEAT111(M,P) M(111,P)
#define BOOST_PP_REPEAT113(M,P) BOOST_PP_REPEAT112(M,P) M(112,P)
#define BOOST_PP_REPEAT114(M,P) BOOST_PP_REPEAT113(M,P) M(113,P)
#define BOOST_PP_REPEAT115(M,P) BOOST_PP_REPEAT114(M,P) M(114,P)
#define BOOST_PP_REPEAT116(M,P) BOOST_PP_REPEAT115(M,P) M(115,P)
#define BOOST_PP_REPEAT117(M,P) BOOST_PP_REPEAT116(M,P) M(116,P)
#define BOOST_PP_REPEAT118(M,P) BOOST_PP_REPEAT117(M,P) M(117,P)
#define BOOST_PP_REPEAT119(M,P) BOOST_PP_REPEAT118(M,P) M(118,P)
#define BOOST_PP_REPEAT120(M,P) BOOST_PP_REPEAT119(M,P) M(119,P)
#define BOOST_PP_REPEAT121(M,P) BOOST_PP_REPEAT120(M,P) M(120,P)
#define BOOST_PP_REPEAT122(M,P) BOOST_PP_REPEAT121(M,P) M(121,P)
#define BOOST_PP_REPEAT123(M,P) BOOST_PP_REPEAT122(M,P) M(122,P)
#define BOOST_PP_REPEAT124(M,P) BOOST_PP_REPEAT123(M,P) M(123,P)
#define BOOST_PP_REPEAT125(M,P) BOOST_PP_REPEAT124(M,P) M(124,P)
#define BOOST_PP_REPEAT126(M,P) BOOST_PP_REPEAT125(M,P) M(125,P)
#define BOOST_PP_REPEAT127(M,P) BOOST_PP_REPEAT126(M,P) M(126,P)
#define BOOST_PP_REPEAT128(M,P) BOOST_PP_REPEAT127(M,P) M(127,P)
#endif

/** <p>Obsolete. Use BOOST_PP_REPEAT().</p> */
#define BOOST_PREPROCESSOR_REPEAT(N,M,P) BOOST_PP_REPEAT(N,M,P)
#endif
