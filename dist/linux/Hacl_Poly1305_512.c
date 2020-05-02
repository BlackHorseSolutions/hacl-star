/* MIT License
 *
 * Copyright (c) 2016-2020 INRIA, CMU and Microsoft Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "Hacl_Poly1305_512.h"

static void load_acc8(Lib_IntVector_Intrinsics_vec512 *acc, u8 *b)
{
  KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec512), (u32)5U);
  {
    Lib_IntVector_Intrinsics_vec512 e[5U];
    {
      u32 _i;
      for (_i = 0U; _i < (u32)5U; ++_i)
        e[_i] = Lib_IntVector_Intrinsics_vec512_zero;
    }
    {
      Lib_IntVector_Intrinsics_vec512 b10 = Lib_IntVector_Intrinsics_vec512_load_le(b);
      Lib_IntVector_Intrinsics_vec512 b2 = Lib_IntVector_Intrinsics_vec512_load_le(b + (u32)64U);
      Lib_IntVector_Intrinsics_vec512
      lo0 = Lib_IntVector_Intrinsics_vec512_interleave_low256(b10, b2);
      Lib_IntVector_Intrinsics_vec512
      hi0 = Lib_IntVector_Intrinsics_vec512_interleave_high256(b10, b2);
      Lib_IntVector_Intrinsics_vec512
      lo1 = Lib_IntVector_Intrinsics_vec512_interleave_low128(lo0, hi0);
      Lib_IntVector_Intrinsics_vec512
      hi1 = Lib_IntVector_Intrinsics_vec512_interleave_high128(lo0, hi0);
      Lib_IntVector_Intrinsics_vec512
      lo = Lib_IntVector_Intrinsics_vec512_interleave_low64(lo1, hi1);
      Lib_IntVector_Intrinsics_vec512
      hi = Lib_IntVector_Intrinsics_vec512_interleave_high64(lo1, hi1);
      Lib_IntVector_Intrinsics_vec512
      f00 =
        Lib_IntVector_Intrinsics_vec512_and(lo,
          Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec512
      f10 =
        Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(lo,
            (u32)26U),
          Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec512
      f20 =
        Lib_IntVector_Intrinsics_vec512_or(Lib_IntVector_Intrinsics_vec512_shift_right64(lo,
            (u32)52U),
          Lib_IntVector_Intrinsics_vec512_shift_left64(Lib_IntVector_Intrinsics_vec512_and(hi,
              Lib_IntVector_Intrinsics_vec512_load64((u64)0x3fffU)),
            (u32)12U));
      Lib_IntVector_Intrinsics_vec512
      f30 =
        Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(hi,
            (u32)14U),
          Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec512
      f40 = Lib_IntVector_Intrinsics_vec512_shift_right64(hi, (u32)40U);
      Lib_IntVector_Intrinsics_vec512 f01 = f00;
      Lib_IntVector_Intrinsics_vec512 f11 = f10;
      Lib_IntVector_Intrinsics_vec512 f21 = f20;
      Lib_IntVector_Intrinsics_vec512 f31 = f30;
      Lib_IntVector_Intrinsics_vec512 f41 = f40;
      u64 b1;
      Lib_IntVector_Intrinsics_vec512 mask;
      Lib_IntVector_Intrinsics_vec512 f42;
      Lib_IntVector_Intrinsics_vec512 acc0;
      Lib_IntVector_Intrinsics_vec512 acc1;
      Lib_IntVector_Intrinsics_vec512 acc2;
      Lib_IntVector_Intrinsics_vec512 acc3;
      Lib_IntVector_Intrinsics_vec512 acc4;
      Lib_IntVector_Intrinsics_vec512 e0;
      Lib_IntVector_Intrinsics_vec512 e1;
      Lib_IntVector_Intrinsics_vec512 e2;
      Lib_IntVector_Intrinsics_vec512 e3;
      Lib_IntVector_Intrinsics_vec512 e4;
      Lib_IntVector_Intrinsics_vec512 r0;
      Lib_IntVector_Intrinsics_vec512 r1;
      Lib_IntVector_Intrinsics_vec512 r2;
      Lib_IntVector_Intrinsics_vec512 r3;
      Lib_IntVector_Intrinsics_vec512 r4;
      Lib_IntVector_Intrinsics_vec512 r01;
      Lib_IntVector_Intrinsics_vec512 r11;
      Lib_IntVector_Intrinsics_vec512 r21;
      Lib_IntVector_Intrinsics_vec512 r31;
      Lib_IntVector_Intrinsics_vec512 r41;
      Lib_IntVector_Intrinsics_vec512 f0;
      Lib_IntVector_Intrinsics_vec512 f1;
      Lib_IntVector_Intrinsics_vec512 f2;
      Lib_IntVector_Intrinsics_vec512 f3;
      Lib_IntVector_Intrinsics_vec512 f4;
      Lib_IntVector_Intrinsics_vec512 acc01;
      Lib_IntVector_Intrinsics_vec512 acc11;
      Lib_IntVector_Intrinsics_vec512 acc21;
      Lib_IntVector_Intrinsics_vec512 acc31;
      Lib_IntVector_Intrinsics_vec512 acc41;
      e[0U] = f01;
      e[1U] = f11;
      e[2U] = f21;
      e[3U] = f31;
      e[4U] = f41;
      b1 = (u64)0x1000000U;
      mask = Lib_IntVector_Intrinsics_vec512_load64(b1);
      f42 = e[4U];
      e[4U] = Lib_IntVector_Intrinsics_vec512_or(f42, mask);
      acc0 = acc[0U];
      acc1 = acc[1U];
      acc2 = acc[2U];
      acc3 = acc[3U];
      acc4 = acc[4U];
      e0 = e[0U];
      e1 = e[1U];
      e2 = e[2U];
      e3 = e[3U];
      e4 = e[4U];
      r0 = Lib_IntVector_Intrinsics_vec512_zero;
      r1 = Lib_IntVector_Intrinsics_vec512_zero;
      r2 = Lib_IntVector_Intrinsics_vec512_zero;
      r3 = Lib_IntVector_Intrinsics_vec512_zero;
      r4 = Lib_IntVector_Intrinsics_vec512_zero;
      r01 =
        Lib_IntVector_Intrinsics_vec512_insert64(r0,
          Lib_IntVector_Intrinsics_vec512_extract64(acc0, (u32)0U),
          (u32)0U);
      r11 =
        Lib_IntVector_Intrinsics_vec512_insert64(r1,
          Lib_IntVector_Intrinsics_vec512_extract64(acc1, (u32)0U),
          (u32)0U);
      r21 =
        Lib_IntVector_Intrinsics_vec512_insert64(r2,
          Lib_IntVector_Intrinsics_vec512_extract64(acc2, (u32)0U),
          (u32)0U);
      r31 =
        Lib_IntVector_Intrinsics_vec512_insert64(r3,
          Lib_IntVector_Intrinsics_vec512_extract64(acc3, (u32)0U),
          (u32)0U);
      r41 =
        Lib_IntVector_Intrinsics_vec512_insert64(r4,
          Lib_IntVector_Intrinsics_vec512_extract64(acc4, (u32)0U),
          (u32)0U);
      f0 = Lib_IntVector_Intrinsics_vec512_add64(r01, e0);
      f1 = Lib_IntVector_Intrinsics_vec512_add64(r11, e1);
      f2 = Lib_IntVector_Intrinsics_vec512_add64(r21, e2);
      f3 = Lib_IntVector_Intrinsics_vec512_add64(r31, e3);
      f4 = Lib_IntVector_Intrinsics_vec512_add64(r41, e4);
      acc01 = f0;
      acc11 = f1;
      acc21 = f2;
      acc31 = f3;
      acc41 = f4;
      acc[0U] = acc01;
      acc[1U] = acc11;
      acc[2U] = acc21;
      acc[3U] = acc31;
      acc[4U] = acc41;
    }
  }
}

static void
fmul_r8_normalize(Lib_IntVector_Intrinsics_vec512 *out, Lib_IntVector_Intrinsics_vec512 *p)
{
  Lib_IntVector_Intrinsics_vec512 *r = p;
  Lib_IntVector_Intrinsics_vec512 *r_5 = p + (u32)5U;
  Lib_IntVector_Intrinsics_vec512 *r8 = p + (u32)10U;
  Lib_IntVector_Intrinsics_vec512 a0 = out[0U];
  Lib_IntVector_Intrinsics_vec512 a1 = out[1U];
  Lib_IntVector_Intrinsics_vec512 a2 = out[2U];
  Lib_IntVector_Intrinsics_vec512 a3 = out[3U];
  Lib_IntVector_Intrinsics_vec512 a4 = out[4U];
  Lib_IntVector_Intrinsics_vec512 r10 = r[0U];
  Lib_IntVector_Intrinsics_vec512 r11 = r[1U];
  Lib_IntVector_Intrinsics_vec512 r12 = r[2U];
  Lib_IntVector_Intrinsics_vec512 r13 = r[3U];
  Lib_IntVector_Intrinsics_vec512 r14 = r[4U];
  Lib_IntVector_Intrinsics_vec512 r151 = r_5[1U];
  Lib_IntVector_Intrinsics_vec512 r152 = r_5[2U];
  Lib_IntVector_Intrinsics_vec512 r153 = r_5[3U];
  Lib_IntVector_Intrinsics_vec512 r154 = r_5[4U];
  Lib_IntVector_Intrinsics_vec512 r80 = r8[0U];
  Lib_IntVector_Intrinsics_vec512 r81 = r8[1U];
  Lib_IntVector_Intrinsics_vec512 r82 = r8[2U];
  Lib_IntVector_Intrinsics_vec512 r83 = r8[3U];
  Lib_IntVector_Intrinsics_vec512 r84 = r8[4U];
  Lib_IntVector_Intrinsics_vec512 a010 = Lib_IntVector_Intrinsics_vec512_mul64(r10, r10);
  Lib_IntVector_Intrinsics_vec512 a110 = Lib_IntVector_Intrinsics_vec512_mul64(r11, r10);
  Lib_IntVector_Intrinsics_vec512 a210 = Lib_IntVector_Intrinsics_vec512_mul64(r12, r10);
  Lib_IntVector_Intrinsics_vec512 a310 = Lib_IntVector_Intrinsics_vec512_mul64(r13, r10);
  Lib_IntVector_Intrinsics_vec512 a410 = Lib_IntVector_Intrinsics_vec512_mul64(r14, r10);
  Lib_IntVector_Intrinsics_vec512
  a020 =
    Lib_IntVector_Intrinsics_vec512_add64(a010,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r11));
  Lib_IntVector_Intrinsics_vec512
  a120 =
    Lib_IntVector_Intrinsics_vec512_add64(a110,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r11));
  Lib_IntVector_Intrinsics_vec512
  a220 =
    Lib_IntVector_Intrinsics_vec512_add64(a210,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r11));
  Lib_IntVector_Intrinsics_vec512
  a320 =
    Lib_IntVector_Intrinsics_vec512_add64(a310,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r11));
  Lib_IntVector_Intrinsics_vec512
  a420 =
    Lib_IntVector_Intrinsics_vec512_add64(a410,
      Lib_IntVector_Intrinsics_vec512_mul64(r13, r11));
  Lib_IntVector_Intrinsics_vec512
  a030 =
    Lib_IntVector_Intrinsics_vec512_add64(a020,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r12));
  Lib_IntVector_Intrinsics_vec512
  a130 =
    Lib_IntVector_Intrinsics_vec512_add64(a120,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r12));
  Lib_IntVector_Intrinsics_vec512
  a230 =
    Lib_IntVector_Intrinsics_vec512_add64(a220,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r12));
  Lib_IntVector_Intrinsics_vec512
  a330 =
    Lib_IntVector_Intrinsics_vec512_add64(a320,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r12));
  Lib_IntVector_Intrinsics_vec512
  a430 =
    Lib_IntVector_Intrinsics_vec512_add64(a420,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r12));
  Lib_IntVector_Intrinsics_vec512
  a040 =
    Lib_IntVector_Intrinsics_vec512_add64(a030,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r13));
  Lib_IntVector_Intrinsics_vec512
  a140 =
    Lib_IntVector_Intrinsics_vec512_add64(a130,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r13));
  Lib_IntVector_Intrinsics_vec512
  a240 =
    Lib_IntVector_Intrinsics_vec512_add64(a230,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r13));
  Lib_IntVector_Intrinsics_vec512
  a340 =
    Lib_IntVector_Intrinsics_vec512_add64(a330,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r13));
  Lib_IntVector_Intrinsics_vec512
  a440 =
    Lib_IntVector_Intrinsics_vec512_add64(a430,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r13));
  Lib_IntVector_Intrinsics_vec512
  a050 =
    Lib_IntVector_Intrinsics_vec512_add64(a040,
      Lib_IntVector_Intrinsics_vec512_mul64(r151, r14));
  Lib_IntVector_Intrinsics_vec512
  a150 =
    Lib_IntVector_Intrinsics_vec512_add64(a140,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r14));
  Lib_IntVector_Intrinsics_vec512
  a250 =
    Lib_IntVector_Intrinsics_vec512_add64(a240,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r14));
  Lib_IntVector_Intrinsics_vec512
  a350 =
    Lib_IntVector_Intrinsics_vec512_add64(a340,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r14));
  Lib_IntVector_Intrinsics_vec512
  a450 =
    Lib_IntVector_Intrinsics_vec512_add64(a440,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r14));
  Lib_IntVector_Intrinsics_vec512 t00 = a050;
  Lib_IntVector_Intrinsics_vec512 t10 = a150;
  Lib_IntVector_Intrinsics_vec512 t20 = a250;
  Lib_IntVector_Intrinsics_vec512 t30 = a350;
  Lib_IntVector_Intrinsics_vec512 t40 = a450;
  Lib_IntVector_Intrinsics_vec512
  mask260 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  Lib_IntVector_Intrinsics_vec512
  z00 = Lib_IntVector_Intrinsics_vec512_shift_right64(t00, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z10 = Lib_IntVector_Intrinsics_vec512_shift_right64(t30, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x00 = Lib_IntVector_Intrinsics_vec512_and(t00, mask260);
  Lib_IntVector_Intrinsics_vec512 x30 = Lib_IntVector_Intrinsics_vec512_and(t30, mask260);
  Lib_IntVector_Intrinsics_vec512 x10 = Lib_IntVector_Intrinsics_vec512_add64(t10, z00);
  Lib_IntVector_Intrinsics_vec512 x40 = Lib_IntVector_Intrinsics_vec512_add64(t40, z10);
  Lib_IntVector_Intrinsics_vec512
  z010 = Lib_IntVector_Intrinsics_vec512_shift_right64(x10, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z110 = Lib_IntVector_Intrinsics_vec512_shift_right64(x40, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  t5 = Lib_IntVector_Intrinsics_vec512_shift_left64(z110, (u32)2U);
  Lib_IntVector_Intrinsics_vec512 z12 = Lib_IntVector_Intrinsics_vec512_add64(z110, t5);
  Lib_IntVector_Intrinsics_vec512 x110 = Lib_IntVector_Intrinsics_vec512_and(x10, mask260);
  Lib_IntVector_Intrinsics_vec512 x410 = Lib_IntVector_Intrinsics_vec512_and(x40, mask260);
  Lib_IntVector_Intrinsics_vec512 x20 = Lib_IntVector_Intrinsics_vec512_add64(t20, z010);
  Lib_IntVector_Intrinsics_vec512 x010 = Lib_IntVector_Intrinsics_vec512_add64(x00, z12);
  Lib_IntVector_Intrinsics_vec512
  z020 = Lib_IntVector_Intrinsics_vec512_shift_right64(x20, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z130 = Lib_IntVector_Intrinsics_vec512_shift_right64(x010, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x210 = Lib_IntVector_Intrinsics_vec512_and(x20, mask260);
  Lib_IntVector_Intrinsics_vec512 x020 = Lib_IntVector_Intrinsics_vec512_and(x010, mask260);
  Lib_IntVector_Intrinsics_vec512 x310 = Lib_IntVector_Intrinsics_vec512_add64(x30, z020);
  Lib_IntVector_Intrinsics_vec512 x120 = Lib_IntVector_Intrinsics_vec512_add64(x110, z130);
  Lib_IntVector_Intrinsics_vec512
  z030 = Lib_IntVector_Intrinsics_vec512_shift_right64(x310, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x320 = Lib_IntVector_Intrinsics_vec512_and(x310, mask260);
  Lib_IntVector_Intrinsics_vec512 x420 = Lib_IntVector_Intrinsics_vec512_add64(x410, z030);
  Lib_IntVector_Intrinsics_vec512 r20 = x020;
  Lib_IntVector_Intrinsics_vec512 r21 = x120;
  Lib_IntVector_Intrinsics_vec512 r22 = x210;
  Lib_IntVector_Intrinsics_vec512 r23 = x320;
  Lib_IntVector_Intrinsics_vec512 r24 = x420;
  Lib_IntVector_Intrinsics_vec512 a011 = Lib_IntVector_Intrinsics_vec512_mul64(r10, r20);
  Lib_IntVector_Intrinsics_vec512 a111 = Lib_IntVector_Intrinsics_vec512_mul64(r11, r20);
  Lib_IntVector_Intrinsics_vec512 a211 = Lib_IntVector_Intrinsics_vec512_mul64(r12, r20);
  Lib_IntVector_Intrinsics_vec512 a311 = Lib_IntVector_Intrinsics_vec512_mul64(r13, r20);
  Lib_IntVector_Intrinsics_vec512 a411 = Lib_IntVector_Intrinsics_vec512_mul64(r14, r20);
  Lib_IntVector_Intrinsics_vec512
  a021 =
    Lib_IntVector_Intrinsics_vec512_add64(a011,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r21));
  Lib_IntVector_Intrinsics_vec512
  a121 =
    Lib_IntVector_Intrinsics_vec512_add64(a111,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r21));
  Lib_IntVector_Intrinsics_vec512
  a221 =
    Lib_IntVector_Intrinsics_vec512_add64(a211,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r21));
  Lib_IntVector_Intrinsics_vec512
  a321 =
    Lib_IntVector_Intrinsics_vec512_add64(a311,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r21));
  Lib_IntVector_Intrinsics_vec512
  a421 =
    Lib_IntVector_Intrinsics_vec512_add64(a411,
      Lib_IntVector_Intrinsics_vec512_mul64(r13, r21));
  Lib_IntVector_Intrinsics_vec512
  a031 =
    Lib_IntVector_Intrinsics_vec512_add64(a021,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r22));
  Lib_IntVector_Intrinsics_vec512
  a131 =
    Lib_IntVector_Intrinsics_vec512_add64(a121,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r22));
  Lib_IntVector_Intrinsics_vec512
  a231 =
    Lib_IntVector_Intrinsics_vec512_add64(a221,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r22));
  Lib_IntVector_Intrinsics_vec512
  a331 =
    Lib_IntVector_Intrinsics_vec512_add64(a321,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r22));
  Lib_IntVector_Intrinsics_vec512
  a431 =
    Lib_IntVector_Intrinsics_vec512_add64(a421,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r22));
  Lib_IntVector_Intrinsics_vec512
  a041 =
    Lib_IntVector_Intrinsics_vec512_add64(a031,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r23));
  Lib_IntVector_Intrinsics_vec512
  a141 =
    Lib_IntVector_Intrinsics_vec512_add64(a131,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r23));
  Lib_IntVector_Intrinsics_vec512
  a241 =
    Lib_IntVector_Intrinsics_vec512_add64(a231,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r23));
  Lib_IntVector_Intrinsics_vec512
  a341 =
    Lib_IntVector_Intrinsics_vec512_add64(a331,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r23));
  Lib_IntVector_Intrinsics_vec512
  a441 =
    Lib_IntVector_Intrinsics_vec512_add64(a431,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r23));
  Lib_IntVector_Intrinsics_vec512
  a051 =
    Lib_IntVector_Intrinsics_vec512_add64(a041,
      Lib_IntVector_Intrinsics_vec512_mul64(r151, r24));
  Lib_IntVector_Intrinsics_vec512
  a151 =
    Lib_IntVector_Intrinsics_vec512_add64(a141,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r24));
  Lib_IntVector_Intrinsics_vec512
  a251 =
    Lib_IntVector_Intrinsics_vec512_add64(a241,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r24));
  Lib_IntVector_Intrinsics_vec512
  a351 =
    Lib_IntVector_Intrinsics_vec512_add64(a341,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r24));
  Lib_IntVector_Intrinsics_vec512
  a451 =
    Lib_IntVector_Intrinsics_vec512_add64(a441,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r24));
  Lib_IntVector_Intrinsics_vec512 t01 = a051;
  Lib_IntVector_Intrinsics_vec512 t11 = a151;
  Lib_IntVector_Intrinsics_vec512 t21 = a251;
  Lib_IntVector_Intrinsics_vec512 t31 = a351;
  Lib_IntVector_Intrinsics_vec512 t41 = a451;
  Lib_IntVector_Intrinsics_vec512
  mask261 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  Lib_IntVector_Intrinsics_vec512
  z04 = Lib_IntVector_Intrinsics_vec512_shift_right64(t01, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z14 = Lib_IntVector_Intrinsics_vec512_shift_right64(t31, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x03 = Lib_IntVector_Intrinsics_vec512_and(t01, mask261);
  Lib_IntVector_Intrinsics_vec512 x33 = Lib_IntVector_Intrinsics_vec512_and(t31, mask261);
  Lib_IntVector_Intrinsics_vec512 x13 = Lib_IntVector_Intrinsics_vec512_add64(t11, z04);
  Lib_IntVector_Intrinsics_vec512 x43 = Lib_IntVector_Intrinsics_vec512_add64(t41, z14);
  Lib_IntVector_Intrinsics_vec512
  z011 = Lib_IntVector_Intrinsics_vec512_shift_right64(x13, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z111 = Lib_IntVector_Intrinsics_vec512_shift_right64(x43, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  t6 = Lib_IntVector_Intrinsics_vec512_shift_left64(z111, (u32)2U);
  Lib_IntVector_Intrinsics_vec512 z120 = Lib_IntVector_Intrinsics_vec512_add64(z111, t6);
  Lib_IntVector_Intrinsics_vec512 x111 = Lib_IntVector_Intrinsics_vec512_and(x13, mask261);
  Lib_IntVector_Intrinsics_vec512 x411 = Lib_IntVector_Intrinsics_vec512_and(x43, mask261);
  Lib_IntVector_Intrinsics_vec512 x22 = Lib_IntVector_Intrinsics_vec512_add64(t21, z011);
  Lib_IntVector_Intrinsics_vec512 x011 = Lib_IntVector_Intrinsics_vec512_add64(x03, z120);
  Lib_IntVector_Intrinsics_vec512
  z021 = Lib_IntVector_Intrinsics_vec512_shift_right64(x22, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z131 = Lib_IntVector_Intrinsics_vec512_shift_right64(x011, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x211 = Lib_IntVector_Intrinsics_vec512_and(x22, mask261);
  Lib_IntVector_Intrinsics_vec512 x021 = Lib_IntVector_Intrinsics_vec512_and(x011, mask261);
  Lib_IntVector_Intrinsics_vec512 x311 = Lib_IntVector_Intrinsics_vec512_add64(x33, z021);
  Lib_IntVector_Intrinsics_vec512 x121 = Lib_IntVector_Intrinsics_vec512_add64(x111, z131);
  Lib_IntVector_Intrinsics_vec512
  z031 = Lib_IntVector_Intrinsics_vec512_shift_right64(x311, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x321 = Lib_IntVector_Intrinsics_vec512_and(x311, mask261);
  Lib_IntVector_Intrinsics_vec512 x421 = Lib_IntVector_Intrinsics_vec512_add64(x411, z031);
  Lib_IntVector_Intrinsics_vec512 r30 = x021;
  Lib_IntVector_Intrinsics_vec512 r31 = x121;
  Lib_IntVector_Intrinsics_vec512 r32 = x211;
  Lib_IntVector_Intrinsics_vec512 r33 = x321;
  Lib_IntVector_Intrinsics_vec512 r34 = x421;
  Lib_IntVector_Intrinsics_vec512 a012 = Lib_IntVector_Intrinsics_vec512_mul64(r10, r30);
  Lib_IntVector_Intrinsics_vec512 a112 = Lib_IntVector_Intrinsics_vec512_mul64(r11, r30);
  Lib_IntVector_Intrinsics_vec512 a212 = Lib_IntVector_Intrinsics_vec512_mul64(r12, r30);
  Lib_IntVector_Intrinsics_vec512 a312 = Lib_IntVector_Intrinsics_vec512_mul64(r13, r30);
  Lib_IntVector_Intrinsics_vec512 a412 = Lib_IntVector_Intrinsics_vec512_mul64(r14, r30);
  Lib_IntVector_Intrinsics_vec512
  a022 =
    Lib_IntVector_Intrinsics_vec512_add64(a012,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r31));
  Lib_IntVector_Intrinsics_vec512
  a122 =
    Lib_IntVector_Intrinsics_vec512_add64(a112,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r31));
  Lib_IntVector_Intrinsics_vec512
  a222 =
    Lib_IntVector_Intrinsics_vec512_add64(a212,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r31));
  Lib_IntVector_Intrinsics_vec512
  a322 =
    Lib_IntVector_Intrinsics_vec512_add64(a312,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r31));
  Lib_IntVector_Intrinsics_vec512
  a422 =
    Lib_IntVector_Intrinsics_vec512_add64(a412,
      Lib_IntVector_Intrinsics_vec512_mul64(r13, r31));
  Lib_IntVector_Intrinsics_vec512
  a032 =
    Lib_IntVector_Intrinsics_vec512_add64(a022,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r32));
  Lib_IntVector_Intrinsics_vec512
  a132 =
    Lib_IntVector_Intrinsics_vec512_add64(a122,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r32));
  Lib_IntVector_Intrinsics_vec512
  a232 =
    Lib_IntVector_Intrinsics_vec512_add64(a222,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r32));
  Lib_IntVector_Intrinsics_vec512
  a332 =
    Lib_IntVector_Intrinsics_vec512_add64(a322,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r32));
  Lib_IntVector_Intrinsics_vec512
  a432 =
    Lib_IntVector_Intrinsics_vec512_add64(a422,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r32));
  Lib_IntVector_Intrinsics_vec512
  a042 =
    Lib_IntVector_Intrinsics_vec512_add64(a032,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r33));
  Lib_IntVector_Intrinsics_vec512
  a142 =
    Lib_IntVector_Intrinsics_vec512_add64(a132,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r33));
  Lib_IntVector_Intrinsics_vec512
  a242 =
    Lib_IntVector_Intrinsics_vec512_add64(a232,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r33));
  Lib_IntVector_Intrinsics_vec512
  a342 =
    Lib_IntVector_Intrinsics_vec512_add64(a332,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r33));
  Lib_IntVector_Intrinsics_vec512
  a442 =
    Lib_IntVector_Intrinsics_vec512_add64(a432,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r33));
  Lib_IntVector_Intrinsics_vec512
  a052 =
    Lib_IntVector_Intrinsics_vec512_add64(a042,
      Lib_IntVector_Intrinsics_vec512_mul64(r151, r34));
  Lib_IntVector_Intrinsics_vec512
  a152 =
    Lib_IntVector_Intrinsics_vec512_add64(a142,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r34));
  Lib_IntVector_Intrinsics_vec512
  a252 =
    Lib_IntVector_Intrinsics_vec512_add64(a242,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r34));
  Lib_IntVector_Intrinsics_vec512
  a352 =
    Lib_IntVector_Intrinsics_vec512_add64(a342,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r34));
  Lib_IntVector_Intrinsics_vec512
  a452 =
    Lib_IntVector_Intrinsics_vec512_add64(a442,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r34));
  Lib_IntVector_Intrinsics_vec512 t02 = a052;
  Lib_IntVector_Intrinsics_vec512 t12 = a152;
  Lib_IntVector_Intrinsics_vec512 t22 = a252;
  Lib_IntVector_Intrinsics_vec512 t32 = a352;
  Lib_IntVector_Intrinsics_vec512 t42 = a452;
  Lib_IntVector_Intrinsics_vec512
  mask262 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  Lib_IntVector_Intrinsics_vec512
  z05 = Lib_IntVector_Intrinsics_vec512_shift_right64(t02, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z15 = Lib_IntVector_Intrinsics_vec512_shift_right64(t32, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x04 = Lib_IntVector_Intrinsics_vec512_and(t02, mask262);
  Lib_IntVector_Intrinsics_vec512 x34 = Lib_IntVector_Intrinsics_vec512_and(t32, mask262);
  Lib_IntVector_Intrinsics_vec512 x14 = Lib_IntVector_Intrinsics_vec512_add64(t12, z05);
  Lib_IntVector_Intrinsics_vec512 x44 = Lib_IntVector_Intrinsics_vec512_add64(t42, z15);
  Lib_IntVector_Intrinsics_vec512
  z012 = Lib_IntVector_Intrinsics_vec512_shift_right64(x14, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z112 = Lib_IntVector_Intrinsics_vec512_shift_right64(x44, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  t7 = Lib_IntVector_Intrinsics_vec512_shift_left64(z112, (u32)2U);
  Lib_IntVector_Intrinsics_vec512 z121 = Lib_IntVector_Intrinsics_vec512_add64(z112, t7);
  Lib_IntVector_Intrinsics_vec512 x112 = Lib_IntVector_Intrinsics_vec512_and(x14, mask262);
  Lib_IntVector_Intrinsics_vec512 x412 = Lib_IntVector_Intrinsics_vec512_and(x44, mask262);
  Lib_IntVector_Intrinsics_vec512 x23 = Lib_IntVector_Intrinsics_vec512_add64(t22, z012);
  Lib_IntVector_Intrinsics_vec512 x012 = Lib_IntVector_Intrinsics_vec512_add64(x04, z121);
  Lib_IntVector_Intrinsics_vec512
  z022 = Lib_IntVector_Intrinsics_vec512_shift_right64(x23, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z132 = Lib_IntVector_Intrinsics_vec512_shift_right64(x012, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x212 = Lib_IntVector_Intrinsics_vec512_and(x23, mask262);
  Lib_IntVector_Intrinsics_vec512 x022 = Lib_IntVector_Intrinsics_vec512_and(x012, mask262);
  Lib_IntVector_Intrinsics_vec512 x312 = Lib_IntVector_Intrinsics_vec512_add64(x34, z022);
  Lib_IntVector_Intrinsics_vec512 x122 = Lib_IntVector_Intrinsics_vec512_add64(x112, z132);
  Lib_IntVector_Intrinsics_vec512
  z032 = Lib_IntVector_Intrinsics_vec512_shift_right64(x312, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x322 = Lib_IntVector_Intrinsics_vec512_and(x312, mask262);
  Lib_IntVector_Intrinsics_vec512 x422 = Lib_IntVector_Intrinsics_vec512_add64(x412, z032);
  Lib_IntVector_Intrinsics_vec512 r40 = x022;
  Lib_IntVector_Intrinsics_vec512 r41 = x122;
  Lib_IntVector_Intrinsics_vec512 r42 = x212;
  Lib_IntVector_Intrinsics_vec512 r43 = x322;
  Lib_IntVector_Intrinsics_vec512 r44 = x422;
  Lib_IntVector_Intrinsics_vec512 a013 = Lib_IntVector_Intrinsics_vec512_mul64(r10, r40);
  Lib_IntVector_Intrinsics_vec512 a113 = Lib_IntVector_Intrinsics_vec512_mul64(r11, r40);
  Lib_IntVector_Intrinsics_vec512 a213 = Lib_IntVector_Intrinsics_vec512_mul64(r12, r40);
  Lib_IntVector_Intrinsics_vec512 a313 = Lib_IntVector_Intrinsics_vec512_mul64(r13, r40);
  Lib_IntVector_Intrinsics_vec512 a413 = Lib_IntVector_Intrinsics_vec512_mul64(r14, r40);
  Lib_IntVector_Intrinsics_vec512
  a023 =
    Lib_IntVector_Intrinsics_vec512_add64(a013,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r41));
  Lib_IntVector_Intrinsics_vec512
  a123 =
    Lib_IntVector_Intrinsics_vec512_add64(a113,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r41));
  Lib_IntVector_Intrinsics_vec512
  a223 =
    Lib_IntVector_Intrinsics_vec512_add64(a213,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r41));
  Lib_IntVector_Intrinsics_vec512
  a323 =
    Lib_IntVector_Intrinsics_vec512_add64(a313,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r41));
  Lib_IntVector_Intrinsics_vec512
  a423 =
    Lib_IntVector_Intrinsics_vec512_add64(a413,
      Lib_IntVector_Intrinsics_vec512_mul64(r13, r41));
  Lib_IntVector_Intrinsics_vec512
  a033 =
    Lib_IntVector_Intrinsics_vec512_add64(a023,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r42));
  Lib_IntVector_Intrinsics_vec512
  a133 =
    Lib_IntVector_Intrinsics_vec512_add64(a123,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r42));
  Lib_IntVector_Intrinsics_vec512
  a233 =
    Lib_IntVector_Intrinsics_vec512_add64(a223,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r42));
  Lib_IntVector_Intrinsics_vec512
  a333 =
    Lib_IntVector_Intrinsics_vec512_add64(a323,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r42));
  Lib_IntVector_Intrinsics_vec512
  a433 =
    Lib_IntVector_Intrinsics_vec512_add64(a423,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r42));
  Lib_IntVector_Intrinsics_vec512
  a043 =
    Lib_IntVector_Intrinsics_vec512_add64(a033,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r43));
  Lib_IntVector_Intrinsics_vec512
  a143 =
    Lib_IntVector_Intrinsics_vec512_add64(a133,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r43));
  Lib_IntVector_Intrinsics_vec512
  a243 =
    Lib_IntVector_Intrinsics_vec512_add64(a233,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r43));
  Lib_IntVector_Intrinsics_vec512
  a343 =
    Lib_IntVector_Intrinsics_vec512_add64(a333,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r43));
  Lib_IntVector_Intrinsics_vec512
  a443 =
    Lib_IntVector_Intrinsics_vec512_add64(a433,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r43));
  Lib_IntVector_Intrinsics_vec512
  a053 =
    Lib_IntVector_Intrinsics_vec512_add64(a043,
      Lib_IntVector_Intrinsics_vec512_mul64(r151, r44));
  Lib_IntVector_Intrinsics_vec512
  a153 =
    Lib_IntVector_Intrinsics_vec512_add64(a143,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r44));
  Lib_IntVector_Intrinsics_vec512
  a253 =
    Lib_IntVector_Intrinsics_vec512_add64(a243,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r44));
  Lib_IntVector_Intrinsics_vec512
  a353 =
    Lib_IntVector_Intrinsics_vec512_add64(a343,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r44));
  Lib_IntVector_Intrinsics_vec512
  a453 =
    Lib_IntVector_Intrinsics_vec512_add64(a443,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r44));
  Lib_IntVector_Intrinsics_vec512 t03 = a053;
  Lib_IntVector_Intrinsics_vec512 t13 = a153;
  Lib_IntVector_Intrinsics_vec512 t23 = a253;
  Lib_IntVector_Intrinsics_vec512 t33 = a353;
  Lib_IntVector_Intrinsics_vec512 t43 = a453;
  Lib_IntVector_Intrinsics_vec512
  mask263 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  Lib_IntVector_Intrinsics_vec512
  z06 = Lib_IntVector_Intrinsics_vec512_shift_right64(t03, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z16 = Lib_IntVector_Intrinsics_vec512_shift_right64(t33, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x05 = Lib_IntVector_Intrinsics_vec512_and(t03, mask263);
  Lib_IntVector_Intrinsics_vec512 x35 = Lib_IntVector_Intrinsics_vec512_and(t33, mask263);
  Lib_IntVector_Intrinsics_vec512 x15 = Lib_IntVector_Intrinsics_vec512_add64(t13, z06);
  Lib_IntVector_Intrinsics_vec512 x45 = Lib_IntVector_Intrinsics_vec512_add64(t43, z16);
  Lib_IntVector_Intrinsics_vec512
  z013 = Lib_IntVector_Intrinsics_vec512_shift_right64(x15, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z113 = Lib_IntVector_Intrinsics_vec512_shift_right64(x45, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  t8 = Lib_IntVector_Intrinsics_vec512_shift_left64(z113, (u32)2U);
  Lib_IntVector_Intrinsics_vec512 z122 = Lib_IntVector_Intrinsics_vec512_add64(z113, t8);
  Lib_IntVector_Intrinsics_vec512 x113 = Lib_IntVector_Intrinsics_vec512_and(x15, mask263);
  Lib_IntVector_Intrinsics_vec512 x413 = Lib_IntVector_Intrinsics_vec512_and(x45, mask263);
  Lib_IntVector_Intrinsics_vec512 x24 = Lib_IntVector_Intrinsics_vec512_add64(t23, z013);
  Lib_IntVector_Intrinsics_vec512 x013 = Lib_IntVector_Intrinsics_vec512_add64(x05, z122);
  Lib_IntVector_Intrinsics_vec512
  z023 = Lib_IntVector_Intrinsics_vec512_shift_right64(x24, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z133 = Lib_IntVector_Intrinsics_vec512_shift_right64(x013, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x213 = Lib_IntVector_Intrinsics_vec512_and(x24, mask263);
  Lib_IntVector_Intrinsics_vec512 x023 = Lib_IntVector_Intrinsics_vec512_and(x013, mask263);
  Lib_IntVector_Intrinsics_vec512 x313 = Lib_IntVector_Intrinsics_vec512_add64(x35, z023);
  Lib_IntVector_Intrinsics_vec512 x123 = Lib_IntVector_Intrinsics_vec512_add64(x113, z133);
  Lib_IntVector_Intrinsics_vec512
  z033 = Lib_IntVector_Intrinsics_vec512_shift_right64(x313, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x323 = Lib_IntVector_Intrinsics_vec512_and(x313, mask263);
  Lib_IntVector_Intrinsics_vec512 x423 = Lib_IntVector_Intrinsics_vec512_add64(x413, z033);
  Lib_IntVector_Intrinsics_vec512 r50 = x023;
  Lib_IntVector_Intrinsics_vec512 r51 = x123;
  Lib_IntVector_Intrinsics_vec512 r52 = x213;
  Lib_IntVector_Intrinsics_vec512 r53 = x323;
  Lib_IntVector_Intrinsics_vec512 r54 = x423;
  Lib_IntVector_Intrinsics_vec512 a014 = Lib_IntVector_Intrinsics_vec512_mul64(r10, r50);
  Lib_IntVector_Intrinsics_vec512 a114 = Lib_IntVector_Intrinsics_vec512_mul64(r11, r50);
  Lib_IntVector_Intrinsics_vec512 a214 = Lib_IntVector_Intrinsics_vec512_mul64(r12, r50);
  Lib_IntVector_Intrinsics_vec512 a314 = Lib_IntVector_Intrinsics_vec512_mul64(r13, r50);
  Lib_IntVector_Intrinsics_vec512 a414 = Lib_IntVector_Intrinsics_vec512_mul64(r14, r50);
  Lib_IntVector_Intrinsics_vec512
  a024 =
    Lib_IntVector_Intrinsics_vec512_add64(a014,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r51));
  Lib_IntVector_Intrinsics_vec512
  a124 =
    Lib_IntVector_Intrinsics_vec512_add64(a114,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r51));
  Lib_IntVector_Intrinsics_vec512
  a224 =
    Lib_IntVector_Intrinsics_vec512_add64(a214,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r51));
  Lib_IntVector_Intrinsics_vec512
  a324 =
    Lib_IntVector_Intrinsics_vec512_add64(a314,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r51));
  Lib_IntVector_Intrinsics_vec512
  a424 =
    Lib_IntVector_Intrinsics_vec512_add64(a414,
      Lib_IntVector_Intrinsics_vec512_mul64(r13, r51));
  Lib_IntVector_Intrinsics_vec512
  a034 =
    Lib_IntVector_Intrinsics_vec512_add64(a024,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r52));
  Lib_IntVector_Intrinsics_vec512
  a134 =
    Lib_IntVector_Intrinsics_vec512_add64(a124,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r52));
  Lib_IntVector_Intrinsics_vec512
  a234 =
    Lib_IntVector_Intrinsics_vec512_add64(a224,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r52));
  Lib_IntVector_Intrinsics_vec512
  a334 =
    Lib_IntVector_Intrinsics_vec512_add64(a324,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r52));
  Lib_IntVector_Intrinsics_vec512
  a434 =
    Lib_IntVector_Intrinsics_vec512_add64(a424,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r52));
  Lib_IntVector_Intrinsics_vec512
  a044 =
    Lib_IntVector_Intrinsics_vec512_add64(a034,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r53));
  Lib_IntVector_Intrinsics_vec512
  a144 =
    Lib_IntVector_Intrinsics_vec512_add64(a134,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r53));
  Lib_IntVector_Intrinsics_vec512
  a244 =
    Lib_IntVector_Intrinsics_vec512_add64(a234,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r53));
  Lib_IntVector_Intrinsics_vec512
  a344 =
    Lib_IntVector_Intrinsics_vec512_add64(a334,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r53));
  Lib_IntVector_Intrinsics_vec512
  a444 =
    Lib_IntVector_Intrinsics_vec512_add64(a434,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r53));
  Lib_IntVector_Intrinsics_vec512
  a054 =
    Lib_IntVector_Intrinsics_vec512_add64(a044,
      Lib_IntVector_Intrinsics_vec512_mul64(r151, r54));
  Lib_IntVector_Intrinsics_vec512
  a154 =
    Lib_IntVector_Intrinsics_vec512_add64(a144,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r54));
  Lib_IntVector_Intrinsics_vec512
  a254 =
    Lib_IntVector_Intrinsics_vec512_add64(a244,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r54));
  Lib_IntVector_Intrinsics_vec512
  a354 =
    Lib_IntVector_Intrinsics_vec512_add64(a344,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r54));
  Lib_IntVector_Intrinsics_vec512
  a454 =
    Lib_IntVector_Intrinsics_vec512_add64(a444,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r54));
  Lib_IntVector_Intrinsics_vec512 t04 = a054;
  Lib_IntVector_Intrinsics_vec512 t14 = a154;
  Lib_IntVector_Intrinsics_vec512 t24 = a254;
  Lib_IntVector_Intrinsics_vec512 t34 = a354;
  Lib_IntVector_Intrinsics_vec512 t44 = a454;
  Lib_IntVector_Intrinsics_vec512
  mask264 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  Lib_IntVector_Intrinsics_vec512
  z07 = Lib_IntVector_Intrinsics_vec512_shift_right64(t04, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z17 = Lib_IntVector_Intrinsics_vec512_shift_right64(t34, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x06 = Lib_IntVector_Intrinsics_vec512_and(t04, mask264);
  Lib_IntVector_Intrinsics_vec512 x36 = Lib_IntVector_Intrinsics_vec512_and(t34, mask264);
  Lib_IntVector_Intrinsics_vec512 x16 = Lib_IntVector_Intrinsics_vec512_add64(t14, z07);
  Lib_IntVector_Intrinsics_vec512 x46 = Lib_IntVector_Intrinsics_vec512_add64(t44, z17);
  Lib_IntVector_Intrinsics_vec512
  z014 = Lib_IntVector_Intrinsics_vec512_shift_right64(x16, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z114 = Lib_IntVector_Intrinsics_vec512_shift_right64(x46, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  t9 = Lib_IntVector_Intrinsics_vec512_shift_left64(z114, (u32)2U);
  Lib_IntVector_Intrinsics_vec512 z123 = Lib_IntVector_Intrinsics_vec512_add64(z114, t9);
  Lib_IntVector_Intrinsics_vec512 x114 = Lib_IntVector_Intrinsics_vec512_and(x16, mask264);
  Lib_IntVector_Intrinsics_vec512 x414 = Lib_IntVector_Intrinsics_vec512_and(x46, mask264);
  Lib_IntVector_Intrinsics_vec512 x25 = Lib_IntVector_Intrinsics_vec512_add64(t24, z014);
  Lib_IntVector_Intrinsics_vec512 x014 = Lib_IntVector_Intrinsics_vec512_add64(x06, z123);
  Lib_IntVector_Intrinsics_vec512
  z024 = Lib_IntVector_Intrinsics_vec512_shift_right64(x25, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z134 = Lib_IntVector_Intrinsics_vec512_shift_right64(x014, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x214 = Lib_IntVector_Intrinsics_vec512_and(x25, mask264);
  Lib_IntVector_Intrinsics_vec512 x024 = Lib_IntVector_Intrinsics_vec512_and(x014, mask264);
  Lib_IntVector_Intrinsics_vec512 x314 = Lib_IntVector_Intrinsics_vec512_add64(x36, z024);
  Lib_IntVector_Intrinsics_vec512 x124 = Lib_IntVector_Intrinsics_vec512_add64(x114, z134);
  Lib_IntVector_Intrinsics_vec512
  z034 = Lib_IntVector_Intrinsics_vec512_shift_right64(x314, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x324 = Lib_IntVector_Intrinsics_vec512_and(x314, mask264);
  Lib_IntVector_Intrinsics_vec512 x424 = Lib_IntVector_Intrinsics_vec512_add64(x414, z034);
  Lib_IntVector_Intrinsics_vec512 r60 = x024;
  Lib_IntVector_Intrinsics_vec512 r61 = x124;
  Lib_IntVector_Intrinsics_vec512 r62 = x214;
  Lib_IntVector_Intrinsics_vec512 r63 = x324;
  Lib_IntVector_Intrinsics_vec512 r64 = x424;
  Lib_IntVector_Intrinsics_vec512 a015 = Lib_IntVector_Intrinsics_vec512_mul64(r10, r60);
  Lib_IntVector_Intrinsics_vec512 a115 = Lib_IntVector_Intrinsics_vec512_mul64(r11, r60);
  Lib_IntVector_Intrinsics_vec512 a215 = Lib_IntVector_Intrinsics_vec512_mul64(r12, r60);
  Lib_IntVector_Intrinsics_vec512 a315 = Lib_IntVector_Intrinsics_vec512_mul64(r13, r60);
  Lib_IntVector_Intrinsics_vec512 a415 = Lib_IntVector_Intrinsics_vec512_mul64(r14, r60);
  Lib_IntVector_Intrinsics_vec512
  a025 =
    Lib_IntVector_Intrinsics_vec512_add64(a015,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r61));
  Lib_IntVector_Intrinsics_vec512
  a125 =
    Lib_IntVector_Intrinsics_vec512_add64(a115,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r61));
  Lib_IntVector_Intrinsics_vec512
  a225 =
    Lib_IntVector_Intrinsics_vec512_add64(a215,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r61));
  Lib_IntVector_Intrinsics_vec512
  a325 =
    Lib_IntVector_Intrinsics_vec512_add64(a315,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r61));
  Lib_IntVector_Intrinsics_vec512
  a425 =
    Lib_IntVector_Intrinsics_vec512_add64(a415,
      Lib_IntVector_Intrinsics_vec512_mul64(r13, r61));
  Lib_IntVector_Intrinsics_vec512
  a035 =
    Lib_IntVector_Intrinsics_vec512_add64(a025,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r62));
  Lib_IntVector_Intrinsics_vec512
  a135 =
    Lib_IntVector_Intrinsics_vec512_add64(a125,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r62));
  Lib_IntVector_Intrinsics_vec512
  a235 =
    Lib_IntVector_Intrinsics_vec512_add64(a225,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r62));
  Lib_IntVector_Intrinsics_vec512
  a335 =
    Lib_IntVector_Intrinsics_vec512_add64(a325,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r62));
  Lib_IntVector_Intrinsics_vec512
  a435 =
    Lib_IntVector_Intrinsics_vec512_add64(a425,
      Lib_IntVector_Intrinsics_vec512_mul64(r12, r62));
  Lib_IntVector_Intrinsics_vec512
  a045 =
    Lib_IntVector_Intrinsics_vec512_add64(a035,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r63));
  Lib_IntVector_Intrinsics_vec512
  a145 =
    Lib_IntVector_Intrinsics_vec512_add64(a135,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r63));
  Lib_IntVector_Intrinsics_vec512
  a245 =
    Lib_IntVector_Intrinsics_vec512_add64(a235,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r63));
  Lib_IntVector_Intrinsics_vec512
  a345 =
    Lib_IntVector_Intrinsics_vec512_add64(a335,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r63));
  Lib_IntVector_Intrinsics_vec512
  a445 =
    Lib_IntVector_Intrinsics_vec512_add64(a435,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, r63));
  Lib_IntVector_Intrinsics_vec512
  a055 =
    Lib_IntVector_Intrinsics_vec512_add64(a045,
      Lib_IntVector_Intrinsics_vec512_mul64(r151, r64));
  Lib_IntVector_Intrinsics_vec512
  a155 =
    Lib_IntVector_Intrinsics_vec512_add64(a145,
      Lib_IntVector_Intrinsics_vec512_mul64(r152, r64));
  Lib_IntVector_Intrinsics_vec512
  a255 =
    Lib_IntVector_Intrinsics_vec512_add64(a245,
      Lib_IntVector_Intrinsics_vec512_mul64(r153, r64));
  Lib_IntVector_Intrinsics_vec512
  a355 =
    Lib_IntVector_Intrinsics_vec512_add64(a345,
      Lib_IntVector_Intrinsics_vec512_mul64(r154, r64));
  Lib_IntVector_Intrinsics_vec512
  a455 =
    Lib_IntVector_Intrinsics_vec512_add64(a445,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, r64));
  Lib_IntVector_Intrinsics_vec512 t05 = a055;
  Lib_IntVector_Intrinsics_vec512 t15 = a155;
  Lib_IntVector_Intrinsics_vec512 t25 = a255;
  Lib_IntVector_Intrinsics_vec512 t35 = a355;
  Lib_IntVector_Intrinsics_vec512 t45 = a455;
  Lib_IntVector_Intrinsics_vec512
  mask265 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  Lib_IntVector_Intrinsics_vec512
  z08 = Lib_IntVector_Intrinsics_vec512_shift_right64(t05, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z18 = Lib_IntVector_Intrinsics_vec512_shift_right64(t35, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x07 = Lib_IntVector_Intrinsics_vec512_and(t05, mask265);
  Lib_IntVector_Intrinsics_vec512 x37 = Lib_IntVector_Intrinsics_vec512_and(t35, mask265);
  Lib_IntVector_Intrinsics_vec512 x17 = Lib_IntVector_Intrinsics_vec512_add64(t15, z08);
  Lib_IntVector_Intrinsics_vec512 x47 = Lib_IntVector_Intrinsics_vec512_add64(t45, z18);
  Lib_IntVector_Intrinsics_vec512
  z015 = Lib_IntVector_Intrinsics_vec512_shift_right64(x17, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z115 = Lib_IntVector_Intrinsics_vec512_shift_right64(x47, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  t16 = Lib_IntVector_Intrinsics_vec512_shift_left64(z115, (u32)2U);
  Lib_IntVector_Intrinsics_vec512 z124 = Lib_IntVector_Intrinsics_vec512_add64(z115, t16);
  Lib_IntVector_Intrinsics_vec512 x115 = Lib_IntVector_Intrinsics_vec512_and(x17, mask265);
  Lib_IntVector_Intrinsics_vec512 x415 = Lib_IntVector_Intrinsics_vec512_and(x47, mask265);
  Lib_IntVector_Intrinsics_vec512 x26 = Lib_IntVector_Intrinsics_vec512_add64(t25, z015);
  Lib_IntVector_Intrinsics_vec512 x015 = Lib_IntVector_Intrinsics_vec512_add64(x07, z124);
  Lib_IntVector_Intrinsics_vec512
  z025 = Lib_IntVector_Intrinsics_vec512_shift_right64(x26, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z135 = Lib_IntVector_Intrinsics_vec512_shift_right64(x015, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x215 = Lib_IntVector_Intrinsics_vec512_and(x26, mask265);
  Lib_IntVector_Intrinsics_vec512 x025 = Lib_IntVector_Intrinsics_vec512_and(x015, mask265);
  Lib_IntVector_Intrinsics_vec512 x315 = Lib_IntVector_Intrinsics_vec512_add64(x37, z025);
  Lib_IntVector_Intrinsics_vec512 x125 = Lib_IntVector_Intrinsics_vec512_add64(x115, z135);
  Lib_IntVector_Intrinsics_vec512
  z035 = Lib_IntVector_Intrinsics_vec512_shift_right64(x315, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x325 = Lib_IntVector_Intrinsics_vec512_and(x315, mask265);
  Lib_IntVector_Intrinsics_vec512 x425 = Lib_IntVector_Intrinsics_vec512_add64(x415, z035);
  Lib_IntVector_Intrinsics_vec512 r70 = x025;
  Lib_IntVector_Intrinsics_vec512 r71 = x125;
  Lib_IntVector_Intrinsics_vec512 r72 = x215;
  Lib_IntVector_Intrinsics_vec512 r73 = x325;
  Lib_IntVector_Intrinsics_vec512 r74 = x425;
  Lib_IntVector_Intrinsics_vec512
  v210 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r20, r10);
  Lib_IntVector_Intrinsics_vec512
  v430 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r40, r30);
  Lib_IntVector_Intrinsics_vec512
  v650 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r60, r50);
  Lib_IntVector_Intrinsics_vec512
  v870 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r80, r70);
  Lib_IntVector_Intrinsics_vec512
  v43210 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v430, v210);
  Lib_IntVector_Intrinsics_vec512
  v87650 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v870, v650);
  Lib_IntVector_Intrinsics_vec512
  r810 = Lib_IntVector_Intrinsics_vec512_interleave_low256(v87650, v43210);
  Lib_IntVector_Intrinsics_vec512
  v211 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r21, r11);
  Lib_IntVector_Intrinsics_vec512
  v431 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r41, r31);
  Lib_IntVector_Intrinsics_vec512
  v651 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r61, r51);
  Lib_IntVector_Intrinsics_vec512
  v871 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r81, r71);
  Lib_IntVector_Intrinsics_vec512
  v43211 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v431, v211);
  Lib_IntVector_Intrinsics_vec512
  v87651 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v871, v651);
  Lib_IntVector_Intrinsics_vec512
  r811 = Lib_IntVector_Intrinsics_vec512_interleave_low256(v87651, v43211);
  Lib_IntVector_Intrinsics_vec512
  v212 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r22, r12);
  Lib_IntVector_Intrinsics_vec512
  v432 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r42, r32);
  Lib_IntVector_Intrinsics_vec512
  v652 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r62, r52);
  Lib_IntVector_Intrinsics_vec512
  v872 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r82, r72);
  Lib_IntVector_Intrinsics_vec512
  v43212 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v432, v212);
  Lib_IntVector_Intrinsics_vec512
  v87652 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v872, v652);
  Lib_IntVector_Intrinsics_vec512
  r812 = Lib_IntVector_Intrinsics_vec512_interleave_low256(v87652, v43212);
  Lib_IntVector_Intrinsics_vec512
  v213 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r23, r13);
  Lib_IntVector_Intrinsics_vec512
  v433 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r43, r33);
  Lib_IntVector_Intrinsics_vec512
  v653 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r63, r53);
  Lib_IntVector_Intrinsics_vec512
  v873 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r83, r73);
  Lib_IntVector_Intrinsics_vec512
  v43213 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v433, v213);
  Lib_IntVector_Intrinsics_vec512
  v87653 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v873, v653);
  Lib_IntVector_Intrinsics_vec512
  r813 = Lib_IntVector_Intrinsics_vec512_interleave_low256(v87653, v43213);
  Lib_IntVector_Intrinsics_vec512
  v214 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r24, r14);
  Lib_IntVector_Intrinsics_vec512
  v434 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r44, r34);
  Lib_IntVector_Intrinsics_vec512
  v654 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r64, r54);
  Lib_IntVector_Intrinsics_vec512
  v874 = Lib_IntVector_Intrinsics_vec512_interleave_low64(r84, r74);
  Lib_IntVector_Intrinsics_vec512
  v43214 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v434, v214);
  Lib_IntVector_Intrinsics_vec512
  v87654 = Lib_IntVector_Intrinsics_vec512_interleave_low128(v874, v654);
  Lib_IntVector_Intrinsics_vec512
  r814 = Lib_IntVector_Intrinsics_vec512_interleave_low256(v87654, v43214);
  Lib_IntVector_Intrinsics_vec512
  r8150 = Lib_IntVector_Intrinsics_vec512_smul64(r810, (u32)(u64)5U);
  Lib_IntVector_Intrinsics_vec512
  r8151 = Lib_IntVector_Intrinsics_vec512_smul64(r811, (u32)(u64)5U);
  Lib_IntVector_Intrinsics_vec512
  r8152 = Lib_IntVector_Intrinsics_vec512_smul64(r812, (u32)(u64)5U);
  Lib_IntVector_Intrinsics_vec512
  r8153 = Lib_IntVector_Intrinsics_vec512_smul64(r813, (u32)(u64)5U);
  Lib_IntVector_Intrinsics_vec512
  r8154 = Lib_IntVector_Intrinsics_vec512_smul64(r814, (u32)(u64)5U);
  Lib_IntVector_Intrinsics_vec512 a01 = Lib_IntVector_Intrinsics_vec512_mul64(r810, a0);
  Lib_IntVector_Intrinsics_vec512 a11 = Lib_IntVector_Intrinsics_vec512_mul64(r811, a0);
  Lib_IntVector_Intrinsics_vec512 a21 = Lib_IntVector_Intrinsics_vec512_mul64(r812, a0);
  Lib_IntVector_Intrinsics_vec512 a31 = Lib_IntVector_Intrinsics_vec512_mul64(r813, a0);
  Lib_IntVector_Intrinsics_vec512 a41 = Lib_IntVector_Intrinsics_vec512_mul64(r814, a0);
  Lib_IntVector_Intrinsics_vec512
  a02 =
    Lib_IntVector_Intrinsics_vec512_add64(a01,
      Lib_IntVector_Intrinsics_vec512_mul64(r8154, a1));
  Lib_IntVector_Intrinsics_vec512
  a12 =
    Lib_IntVector_Intrinsics_vec512_add64(a11,
      Lib_IntVector_Intrinsics_vec512_mul64(r810, a1));
  Lib_IntVector_Intrinsics_vec512
  a22 =
    Lib_IntVector_Intrinsics_vec512_add64(a21,
      Lib_IntVector_Intrinsics_vec512_mul64(r811, a1));
  Lib_IntVector_Intrinsics_vec512
  a32 =
    Lib_IntVector_Intrinsics_vec512_add64(a31,
      Lib_IntVector_Intrinsics_vec512_mul64(r812, a1));
  Lib_IntVector_Intrinsics_vec512
  a42 =
    Lib_IntVector_Intrinsics_vec512_add64(a41,
      Lib_IntVector_Intrinsics_vec512_mul64(r813, a1));
  Lib_IntVector_Intrinsics_vec512
  a03 =
    Lib_IntVector_Intrinsics_vec512_add64(a02,
      Lib_IntVector_Intrinsics_vec512_mul64(r8153, a2));
  Lib_IntVector_Intrinsics_vec512
  a13 =
    Lib_IntVector_Intrinsics_vec512_add64(a12,
      Lib_IntVector_Intrinsics_vec512_mul64(r8154, a2));
  Lib_IntVector_Intrinsics_vec512
  a23 =
    Lib_IntVector_Intrinsics_vec512_add64(a22,
      Lib_IntVector_Intrinsics_vec512_mul64(r810, a2));
  Lib_IntVector_Intrinsics_vec512
  a33 =
    Lib_IntVector_Intrinsics_vec512_add64(a32,
      Lib_IntVector_Intrinsics_vec512_mul64(r811, a2));
  Lib_IntVector_Intrinsics_vec512
  a43 =
    Lib_IntVector_Intrinsics_vec512_add64(a42,
      Lib_IntVector_Intrinsics_vec512_mul64(r812, a2));
  Lib_IntVector_Intrinsics_vec512
  a04 =
    Lib_IntVector_Intrinsics_vec512_add64(a03,
      Lib_IntVector_Intrinsics_vec512_mul64(r8152, a3));
  Lib_IntVector_Intrinsics_vec512
  a14 =
    Lib_IntVector_Intrinsics_vec512_add64(a13,
      Lib_IntVector_Intrinsics_vec512_mul64(r8153, a3));
  Lib_IntVector_Intrinsics_vec512
  a24 =
    Lib_IntVector_Intrinsics_vec512_add64(a23,
      Lib_IntVector_Intrinsics_vec512_mul64(r8154, a3));
  Lib_IntVector_Intrinsics_vec512
  a34 =
    Lib_IntVector_Intrinsics_vec512_add64(a33,
      Lib_IntVector_Intrinsics_vec512_mul64(r810, a3));
  Lib_IntVector_Intrinsics_vec512
  a44 =
    Lib_IntVector_Intrinsics_vec512_add64(a43,
      Lib_IntVector_Intrinsics_vec512_mul64(r811, a3));
  Lib_IntVector_Intrinsics_vec512
  a05 =
    Lib_IntVector_Intrinsics_vec512_add64(a04,
      Lib_IntVector_Intrinsics_vec512_mul64(r8151, a4));
  Lib_IntVector_Intrinsics_vec512
  a15 =
    Lib_IntVector_Intrinsics_vec512_add64(a14,
      Lib_IntVector_Intrinsics_vec512_mul64(r8152, a4));
  Lib_IntVector_Intrinsics_vec512
  a25 =
    Lib_IntVector_Intrinsics_vec512_add64(a24,
      Lib_IntVector_Intrinsics_vec512_mul64(r8153, a4));
  Lib_IntVector_Intrinsics_vec512
  a35 =
    Lib_IntVector_Intrinsics_vec512_add64(a34,
      Lib_IntVector_Intrinsics_vec512_mul64(r8154, a4));
  Lib_IntVector_Intrinsics_vec512
  a45 =
    Lib_IntVector_Intrinsics_vec512_add64(a44,
      Lib_IntVector_Intrinsics_vec512_mul64(r810, a4));
  Lib_IntVector_Intrinsics_vec512 t0 = a05;
  Lib_IntVector_Intrinsics_vec512 t1 = a15;
  Lib_IntVector_Intrinsics_vec512 t2 = a25;
  Lib_IntVector_Intrinsics_vec512 t3 = a35;
  Lib_IntVector_Intrinsics_vec512 t4 = a45;
  Lib_IntVector_Intrinsics_vec512
  mask26 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  Lib_IntVector_Intrinsics_vec512
  z0 = Lib_IntVector_Intrinsics_vec512_shift_right64(t0, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z1 = Lib_IntVector_Intrinsics_vec512_shift_right64(t3, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x0 = Lib_IntVector_Intrinsics_vec512_and(t0, mask26);
  Lib_IntVector_Intrinsics_vec512 x3 = Lib_IntVector_Intrinsics_vec512_and(t3, mask26);
  Lib_IntVector_Intrinsics_vec512 x1 = Lib_IntVector_Intrinsics_vec512_add64(t1, z0);
  Lib_IntVector_Intrinsics_vec512 x4 = Lib_IntVector_Intrinsics_vec512_add64(t4, z1);
  Lib_IntVector_Intrinsics_vec512
  z01 = Lib_IntVector_Intrinsics_vec512_shift_right64(x1, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z11 = Lib_IntVector_Intrinsics_vec512_shift_right64(x4, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 t = Lib_IntVector_Intrinsics_vec512_shift_left64(z11, (u32)2U);
  Lib_IntVector_Intrinsics_vec512 z125 = Lib_IntVector_Intrinsics_vec512_add64(z11, t);
  Lib_IntVector_Intrinsics_vec512 x11 = Lib_IntVector_Intrinsics_vec512_and(x1, mask26);
  Lib_IntVector_Intrinsics_vec512 x41 = Lib_IntVector_Intrinsics_vec512_and(x4, mask26);
  Lib_IntVector_Intrinsics_vec512 x2 = Lib_IntVector_Intrinsics_vec512_add64(t2, z01);
  Lib_IntVector_Intrinsics_vec512 x01 = Lib_IntVector_Intrinsics_vec512_add64(x0, z125);
  Lib_IntVector_Intrinsics_vec512
  z02 = Lib_IntVector_Intrinsics_vec512_shift_right64(x2, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  z13 = Lib_IntVector_Intrinsics_vec512_shift_right64(x01, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x21 = Lib_IntVector_Intrinsics_vec512_and(x2, mask26);
  Lib_IntVector_Intrinsics_vec512 x02 = Lib_IntVector_Intrinsics_vec512_and(x01, mask26);
  Lib_IntVector_Intrinsics_vec512 x31 = Lib_IntVector_Intrinsics_vec512_add64(x3, z02);
  Lib_IntVector_Intrinsics_vec512 x12 = Lib_IntVector_Intrinsics_vec512_add64(x11, z13);
  Lib_IntVector_Intrinsics_vec512
  z03 = Lib_IntVector_Intrinsics_vec512_shift_right64(x31, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 x32 = Lib_IntVector_Intrinsics_vec512_and(x31, mask26);
  Lib_IntVector_Intrinsics_vec512 x42 = Lib_IntVector_Intrinsics_vec512_add64(x41, z03);
  Lib_IntVector_Intrinsics_vec512 o0 = x02;
  Lib_IntVector_Intrinsics_vec512 o10 = x12;
  Lib_IntVector_Intrinsics_vec512 o20 = x21;
  Lib_IntVector_Intrinsics_vec512 o30 = x32;
  Lib_IntVector_Intrinsics_vec512 o40 = x42;
  Lib_IntVector_Intrinsics_vec512
  v00 = Lib_IntVector_Intrinsics_vec512_interleave_high256(o0, o0);
  Lib_IntVector_Intrinsics_vec512 v10 = Lib_IntVector_Intrinsics_vec512_add64(o0, v00);
  Lib_IntVector_Intrinsics_vec512
  v20 = Lib_IntVector_Intrinsics_vec512_interleave_high128(v10, v10);
  Lib_IntVector_Intrinsics_vec512 v30 = Lib_IntVector_Intrinsics_vec512_add64(v10, v20);
  Lib_IntVector_Intrinsics_vec512
  v301 =
    Lib_IntVector_Intrinsics_vec512_add64(v30,
      Lib_IntVector_Intrinsics_vec512_interleave_high64(v30, v30));
  Lib_IntVector_Intrinsics_vec512
  v01 = Lib_IntVector_Intrinsics_vec512_interleave_high256(o10, o10);
  Lib_IntVector_Intrinsics_vec512 v11 = Lib_IntVector_Intrinsics_vec512_add64(o10, v01);
  Lib_IntVector_Intrinsics_vec512
  v21 = Lib_IntVector_Intrinsics_vec512_interleave_high128(v11, v11);
  Lib_IntVector_Intrinsics_vec512 v31 = Lib_IntVector_Intrinsics_vec512_add64(v11, v21);
  Lib_IntVector_Intrinsics_vec512
  v311 =
    Lib_IntVector_Intrinsics_vec512_add64(v31,
      Lib_IntVector_Intrinsics_vec512_interleave_high64(v31, v31));
  Lib_IntVector_Intrinsics_vec512
  v02 = Lib_IntVector_Intrinsics_vec512_interleave_high256(o20, o20);
  Lib_IntVector_Intrinsics_vec512 v12 = Lib_IntVector_Intrinsics_vec512_add64(o20, v02);
  Lib_IntVector_Intrinsics_vec512
  v22 = Lib_IntVector_Intrinsics_vec512_interleave_high128(v12, v12);
  Lib_IntVector_Intrinsics_vec512 v32 = Lib_IntVector_Intrinsics_vec512_add64(v12, v22);
  Lib_IntVector_Intrinsics_vec512
  v321 =
    Lib_IntVector_Intrinsics_vec512_add64(v32,
      Lib_IntVector_Intrinsics_vec512_interleave_high64(v32, v32));
  Lib_IntVector_Intrinsics_vec512
  v03 = Lib_IntVector_Intrinsics_vec512_interleave_high256(o30, o30);
  Lib_IntVector_Intrinsics_vec512 v13 = Lib_IntVector_Intrinsics_vec512_add64(o30, v03);
  Lib_IntVector_Intrinsics_vec512
  v23 = Lib_IntVector_Intrinsics_vec512_interleave_high128(v13, v13);
  Lib_IntVector_Intrinsics_vec512 v33 = Lib_IntVector_Intrinsics_vec512_add64(v13, v23);
  Lib_IntVector_Intrinsics_vec512
  v331 =
    Lib_IntVector_Intrinsics_vec512_add64(v33,
      Lib_IntVector_Intrinsics_vec512_interleave_high64(v33, v33));
  Lib_IntVector_Intrinsics_vec512
  v04 = Lib_IntVector_Intrinsics_vec512_interleave_high256(o40, o40);
  Lib_IntVector_Intrinsics_vec512 v14 = Lib_IntVector_Intrinsics_vec512_add64(o40, v04);
  Lib_IntVector_Intrinsics_vec512
  v24 = Lib_IntVector_Intrinsics_vec512_interleave_high128(v14, v14);
  Lib_IntVector_Intrinsics_vec512 v34 = Lib_IntVector_Intrinsics_vec512_add64(v14, v24);
  Lib_IntVector_Intrinsics_vec512
  v341 =
    Lib_IntVector_Intrinsics_vec512_add64(v34,
      Lib_IntVector_Intrinsics_vec512_interleave_high64(v34, v34));
  Lib_IntVector_Intrinsics_vec512
  l = Lib_IntVector_Intrinsics_vec512_add64(v301, Lib_IntVector_Intrinsics_vec512_zero);
  Lib_IntVector_Intrinsics_vec512
  tmp0 =
    Lib_IntVector_Intrinsics_vec512_and(l,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c0 = Lib_IntVector_Intrinsics_vec512_shift_right64(l, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l0 = Lib_IntVector_Intrinsics_vec512_add64(v311, c0);
  Lib_IntVector_Intrinsics_vec512
  tmp1 =
    Lib_IntVector_Intrinsics_vec512_and(l0,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c1 = Lib_IntVector_Intrinsics_vec512_shift_right64(l0, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l1 = Lib_IntVector_Intrinsics_vec512_add64(v321, c1);
  Lib_IntVector_Intrinsics_vec512
  tmp2 =
    Lib_IntVector_Intrinsics_vec512_and(l1,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c2 = Lib_IntVector_Intrinsics_vec512_shift_right64(l1, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l2 = Lib_IntVector_Intrinsics_vec512_add64(v331, c2);
  Lib_IntVector_Intrinsics_vec512
  tmp3 =
    Lib_IntVector_Intrinsics_vec512_and(l2,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c3 = Lib_IntVector_Intrinsics_vec512_shift_right64(l2, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l3 = Lib_IntVector_Intrinsics_vec512_add64(v341, c3);
  Lib_IntVector_Intrinsics_vec512
  tmp4 =
    Lib_IntVector_Intrinsics_vec512_and(l3,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c4 = Lib_IntVector_Intrinsics_vec512_shift_right64(l3, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  o00 =
    Lib_IntVector_Intrinsics_vec512_add64(tmp0,
      Lib_IntVector_Intrinsics_vec512_smul64(c4, (u32)(u64)5U));
  Lib_IntVector_Intrinsics_vec512 o1 = tmp1;
  Lib_IntVector_Intrinsics_vec512 o2 = tmp2;
  Lib_IntVector_Intrinsics_vec512 o3 = tmp3;
  Lib_IntVector_Intrinsics_vec512 o4 = tmp4;
  out[0U] = o00;
  out[1U] = o1;
  out[2U] = o2;
  out[3U] = o3;
  out[4U] = o4;
}

u32 Hacl_Poly1305_512_blocklen = (u32)16U;

void Hacl_Poly1305_512_poly1305_init(Lib_IntVector_Intrinsics_vec512 *ctx, u8 *key)
{
  Lib_IntVector_Intrinsics_vec512 *acc = ctx;
  Lib_IntVector_Intrinsics_vec512 *pre = ctx + (u32)5U;
  u8 *kr = key;
  u64 u0;
  u64 lo;
  u64 u;
  u64 hi;
  u64 mask0;
  u64 mask1;
  u64 lo1;
  u64 hi1;
  Lib_IntVector_Intrinsics_vec512 *r;
  Lib_IntVector_Intrinsics_vec512 *r5;
  Lib_IntVector_Intrinsics_vec512 *rn;
  Lib_IntVector_Intrinsics_vec512 *rn_5;
  Lib_IntVector_Intrinsics_vec512 r_vec0;
  Lib_IntVector_Intrinsics_vec512 r_vec1;
  Lib_IntVector_Intrinsics_vec512 f00;
  Lib_IntVector_Intrinsics_vec512 f15;
  Lib_IntVector_Intrinsics_vec512 f25;
  Lib_IntVector_Intrinsics_vec512 f30;
  Lib_IntVector_Intrinsics_vec512 f40;
  Lib_IntVector_Intrinsics_vec512 f0;
  Lib_IntVector_Intrinsics_vec512 f1;
  Lib_IntVector_Intrinsics_vec512 f2;
  Lib_IntVector_Intrinsics_vec512 f3;
  Lib_IntVector_Intrinsics_vec512 f4;
  Lib_IntVector_Intrinsics_vec512 f200;
  Lib_IntVector_Intrinsics_vec512 f210;
  Lib_IntVector_Intrinsics_vec512 f220;
  Lib_IntVector_Intrinsics_vec512 f230;
  Lib_IntVector_Intrinsics_vec512 f240;
  Lib_IntVector_Intrinsics_vec512 r00;
  Lib_IntVector_Intrinsics_vec512 r10;
  Lib_IntVector_Intrinsics_vec512 r20;
  Lib_IntVector_Intrinsics_vec512 r30;
  Lib_IntVector_Intrinsics_vec512 r40;
  Lib_IntVector_Intrinsics_vec512 r510;
  Lib_IntVector_Intrinsics_vec512 r520;
  Lib_IntVector_Intrinsics_vec512 r530;
  Lib_IntVector_Intrinsics_vec512 r540;
  Lib_IntVector_Intrinsics_vec512 f100;
  Lib_IntVector_Intrinsics_vec512 f110;
  Lib_IntVector_Intrinsics_vec512 f120;
  Lib_IntVector_Intrinsics_vec512 f130;
  Lib_IntVector_Intrinsics_vec512 f140;
  Lib_IntVector_Intrinsics_vec512 a00;
  Lib_IntVector_Intrinsics_vec512 a10;
  Lib_IntVector_Intrinsics_vec512 a20;
  Lib_IntVector_Intrinsics_vec512 a30;
  Lib_IntVector_Intrinsics_vec512 a40;
  Lib_IntVector_Intrinsics_vec512 a010;
  Lib_IntVector_Intrinsics_vec512 a110;
  Lib_IntVector_Intrinsics_vec512 a210;
  Lib_IntVector_Intrinsics_vec512 a310;
  Lib_IntVector_Intrinsics_vec512 a410;
  Lib_IntVector_Intrinsics_vec512 a020;
  Lib_IntVector_Intrinsics_vec512 a120;
  Lib_IntVector_Intrinsics_vec512 a220;
  Lib_IntVector_Intrinsics_vec512 a320;
  Lib_IntVector_Intrinsics_vec512 a420;
  Lib_IntVector_Intrinsics_vec512 a030;
  Lib_IntVector_Intrinsics_vec512 a130;
  Lib_IntVector_Intrinsics_vec512 a230;
  Lib_IntVector_Intrinsics_vec512 a330;
  Lib_IntVector_Intrinsics_vec512 a430;
  Lib_IntVector_Intrinsics_vec512 a040;
  Lib_IntVector_Intrinsics_vec512 a140;
  Lib_IntVector_Intrinsics_vec512 a240;
  Lib_IntVector_Intrinsics_vec512 a340;
  Lib_IntVector_Intrinsics_vec512 a440;
  Lib_IntVector_Intrinsics_vec512 t00;
  Lib_IntVector_Intrinsics_vec512 t10;
  Lib_IntVector_Intrinsics_vec512 t20;
  Lib_IntVector_Intrinsics_vec512 t30;
  Lib_IntVector_Intrinsics_vec512 t40;
  Lib_IntVector_Intrinsics_vec512 mask260;
  Lib_IntVector_Intrinsics_vec512 z00;
  Lib_IntVector_Intrinsics_vec512 z10;
  Lib_IntVector_Intrinsics_vec512 x00;
  Lib_IntVector_Intrinsics_vec512 x30;
  Lib_IntVector_Intrinsics_vec512 x10;
  Lib_IntVector_Intrinsics_vec512 x40;
  Lib_IntVector_Intrinsics_vec512 z010;
  Lib_IntVector_Intrinsics_vec512 z110;
  Lib_IntVector_Intrinsics_vec512 t5;
  Lib_IntVector_Intrinsics_vec512 z120;
  Lib_IntVector_Intrinsics_vec512 x110;
  Lib_IntVector_Intrinsics_vec512 x410;
  Lib_IntVector_Intrinsics_vec512 x20;
  Lib_IntVector_Intrinsics_vec512 x010;
  Lib_IntVector_Intrinsics_vec512 z020;
  Lib_IntVector_Intrinsics_vec512 z130;
  Lib_IntVector_Intrinsics_vec512 x210;
  Lib_IntVector_Intrinsics_vec512 x020;
  Lib_IntVector_Intrinsics_vec512 x310;
  Lib_IntVector_Intrinsics_vec512 x120;
  Lib_IntVector_Intrinsics_vec512 z030;
  Lib_IntVector_Intrinsics_vec512 x320;
  Lib_IntVector_Intrinsics_vec512 x420;
  Lib_IntVector_Intrinsics_vec512 o00;
  Lib_IntVector_Intrinsics_vec512 o10;
  Lib_IntVector_Intrinsics_vec512 o20;
  Lib_IntVector_Intrinsics_vec512 o30;
  Lib_IntVector_Intrinsics_vec512 o40;
  Lib_IntVector_Intrinsics_vec512 f201;
  Lib_IntVector_Intrinsics_vec512 f211;
  Lib_IntVector_Intrinsics_vec512 f221;
  Lib_IntVector_Intrinsics_vec512 f231;
  Lib_IntVector_Intrinsics_vec512 f241;
  Lib_IntVector_Intrinsics_vec512 r01;
  Lib_IntVector_Intrinsics_vec512 r11;
  Lib_IntVector_Intrinsics_vec512 r21;
  Lib_IntVector_Intrinsics_vec512 r31;
  Lib_IntVector_Intrinsics_vec512 r41;
  Lib_IntVector_Intrinsics_vec512 r511;
  Lib_IntVector_Intrinsics_vec512 r521;
  Lib_IntVector_Intrinsics_vec512 r531;
  Lib_IntVector_Intrinsics_vec512 r541;
  Lib_IntVector_Intrinsics_vec512 f101;
  Lib_IntVector_Intrinsics_vec512 f111;
  Lib_IntVector_Intrinsics_vec512 f121;
  Lib_IntVector_Intrinsics_vec512 f131;
  Lib_IntVector_Intrinsics_vec512 f141;
  Lib_IntVector_Intrinsics_vec512 a05;
  Lib_IntVector_Intrinsics_vec512 a15;
  Lib_IntVector_Intrinsics_vec512 a25;
  Lib_IntVector_Intrinsics_vec512 a35;
  Lib_IntVector_Intrinsics_vec512 a45;
  Lib_IntVector_Intrinsics_vec512 a011;
  Lib_IntVector_Intrinsics_vec512 a111;
  Lib_IntVector_Intrinsics_vec512 a211;
  Lib_IntVector_Intrinsics_vec512 a311;
  Lib_IntVector_Intrinsics_vec512 a411;
  Lib_IntVector_Intrinsics_vec512 a021;
  Lib_IntVector_Intrinsics_vec512 a121;
  Lib_IntVector_Intrinsics_vec512 a221;
  Lib_IntVector_Intrinsics_vec512 a321;
  Lib_IntVector_Intrinsics_vec512 a421;
  Lib_IntVector_Intrinsics_vec512 a031;
  Lib_IntVector_Intrinsics_vec512 a131;
  Lib_IntVector_Intrinsics_vec512 a231;
  Lib_IntVector_Intrinsics_vec512 a331;
  Lib_IntVector_Intrinsics_vec512 a431;
  Lib_IntVector_Intrinsics_vec512 a041;
  Lib_IntVector_Intrinsics_vec512 a141;
  Lib_IntVector_Intrinsics_vec512 a241;
  Lib_IntVector_Intrinsics_vec512 a341;
  Lib_IntVector_Intrinsics_vec512 a441;
  Lib_IntVector_Intrinsics_vec512 t01;
  Lib_IntVector_Intrinsics_vec512 t11;
  Lib_IntVector_Intrinsics_vec512 t21;
  Lib_IntVector_Intrinsics_vec512 t31;
  Lib_IntVector_Intrinsics_vec512 t41;
  Lib_IntVector_Intrinsics_vec512 mask261;
  Lib_IntVector_Intrinsics_vec512 z04;
  Lib_IntVector_Intrinsics_vec512 z14;
  Lib_IntVector_Intrinsics_vec512 x03;
  Lib_IntVector_Intrinsics_vec512 x33;
  Lib_IntVector_Intrinsics_vec512 x13;
  Lib_IntVector_Intrinsics_vec512 x43;
  Lib_IntVector_Intrinsics_vec512 z011;
  Lib_IntVector_Intrinsics_vec512 z111;
  Lib_IntVector_Intrinsics_vec512 t6;
  Lib_IntVector_Intrinsics_vec512 z121;
  Lib_IntVector_Intrinsics_vec512 x111;
  Lib_IntVector_Intrinsics_vec512 x411;
  Lib_IntVector_Intrinsics_vec512 x22;
  Lib_IntVector_Intrinsics_vec512 x011;
  Lib_IntVector_Intrinsics_vec512 z021;
  Lib_IntVector_Intrinsics_vec512 z131;
  Lib_IntVector_Intrinsics_vec512 x211;
  Lib_IntVector_Intrinsics_vec512 x021;
  Lib_IntVector_Intrinsics_vec512 x311;
  Lib_IntVector_Intrinsics_vec512 x121;
  Lib_IntVector_Intrinsics_vec512 z031;
  Lib_IntVector_Intrinsics_vec512 x321;
  Lib_IntVector_Intrinsics_vec512 x421;
  Lib_IntVector_Intrinsics_vec512 o01;
  Lib_IntVector_Intrinsics_vec512 o11;
  Lib_IntVector_Intrinsics_vec512 o21;
  Lib_IntVector_Intrinsics_vec512 o31;
  Lib_IntVector_Intrinsics_vec512 o41;
  Lib_IntVector_Intrinsics_vec512 f202;
  Lib_IntVector_Intrinsics_vec512 f212;
  Lib_IntVector_Intrinsics_vec512 f222;
  Lib_IntVector_Intrinsics_vec512 f232;
  Lib_IntVector_Intrinsics_vec512 f242;
  Lib_IntVector_Intrinsics_vec512 r0;
  Lib_IntVector_Intrinsics_vec512 r1;
  Lib_IntVector_Intrinsics_vec512 r2;
  Lib_IntVector_Intrinsics_vec512 r3;
  Lib_IntVector_Intrinsics_vec512 r4;
  Lib_IntVector_Intrinsics_vec512 r51;
  Lib_IntVector_Intrinsics_vec512 r52;
  Lib_IntVector_Intrinsics_vec512 r53;
  Lib_IntVector_Intrinsics_vec512 r54;
  Lib_IntVector_Intrinsics_vec512 f10;
  Lib_IntVector_Intrinsics_vec512 f11;
  Lib_IntVector_Intrinsics_vec512 f12;
  Lib_IntVector_Intrinsics_vec512 f13;
  Lib_IntVector_Intrinsics_vec512 f14;
  Lib_IntVector_Intrinsics_vec512 a0;
  Lib_IntVector_Intrinsics_vec512 a1;
  Lib_IntVector_Intrinsics_vec512 a2;
  Lib_IntVector_Intrinsics_vec512 a3;
  Lib_IntVector_Intrinsics_vec512 a4;
  Lib_IntVector_Intrinsics_vec512 a01;
  Lib_IntVector_Intrinsics_vec512 a11;
  Lib_IntVector_Intrinsics_vec512 a21;
  Lib_IntVector_Intrinsics_vec512 a31;
  Lib_IntVector_Intrinsics_vec512 a41;
  Lib_IntVector_Intrinsics_vec512 a02;
  Lib_IntVector_Intrinsics_vec512 a12;
  Lib_IntVector_Intrinsics_vec512 a22;
  Lib_IntVector_Intrinsics_vec512 a32;
  Lib_IntVector_Intrinsics_vec512 a42;
  Lib_IntVector_Intrinsics_vec512 a03;
  Lib_IntVector_Intrinsics_vec512 a13;
  Lib_IntVector_Intrinsics_vec512 a23;
  Lib_IntVector_Intrinsics_vec512 a33;
  Lib_IntVector_Intrinsics_vec512 a43;
  Lib_IntVector_Intrinsics_vec512 a04;
  Lib_IntVector_Intrinsics_vec512 a14;
  Lib_IntVector_Intrinsics_vec512 a24;
  Lib_IntVector_Intrinsics_vec512 a34;
  Lib_IntVector_Intrinsics_vec512 a44;
  Lib_IntVector_Intrinsics_vec512 t0;
  Lib_IntVector_Intrinsics_vec512 t1;
  Lib_IntVector_Intrinsics_vec512 t2;
  Lib_IntVector_Intrinsics_vec512 t3;
  Lib_IntVector_Intrinsics_vec512 t4;
  Lib_IntVector_Intrinsics_vec512 mask26;
  Lib_IntVector_Intrinsics_vec512 z0;
  Lib_IntVector_Intrinsics_vec512 z1;
  Lib_IntVector_Intrinsics_vec512 x0;
  Lib_IntVector_Intrinsics_vec512 x3;
  Lib_IntVector_Intrinsics_vec512 x1;
  Lib_IntVector_Intrinsics_vec512 x4;
  Lib_IntVector_Intrinsics_vec512 z01;
  Lib_IntVector_Intrinsics_vec512 z11;
  Lib_IntVector_Intrinsics_vec512 t;
  Lib_IntVector_Intrinsics_vec512 z12;
  Lib_IntVector_Intrinsics_vec512 x11;
  Lib_IntVector_Intrinsics_vec512 x41;
  Lib_IntVector_Intrinsics_vec512 x2;
  Lib_IntVector_Intrinsics_vec512 x01;
  Lib_IntVector_Intrinsics_vec512 z02;
  Lib_IntVector_Intrinsics_vec512 z13;
  Lib_IntVector_Intrinsics_vec512 x21;
  Lib_IntVector_Intrinsics_vec512 x02;
  Lib_IntVector_Intrinsics_vec512 x31;
  Lib_IntVector_Intrinsics_vec512 x12;
  Lib_IntVector_Intrinsics_vec512 z03;
  Lib_IntVector_Intrinsics_vec512 x32;
  Lib_IntVector_Intrinsics_vec512 x42;
  Lib_IntVector_Intrinsics_vec512 o0;
  Lib_IntVector_Intrinsics_vec512 o1;
  Lib_IntVector_Intrinsics_vec512 o2;
  Lib_IntVector_Intrinsics_vec512 o3;
  Lib_IntVector_Intrinsics_vec512 o4;
  Lib_IntVector_Intrinsics_vec512 f20;
  Lib_IntVector_Intrinsics_vec512 f21;
  Lib_IntVector_Intrinsics_vec512 f22;
  Lib_IntVector_Intrinsics_vec512 f23;
  Lib_IntVector_Intrinsics_vec512 f24;
  acc[0U] = Lib_IntVector_Intrinsics_vec512_zero;
  acc[1U] = Lib_IntVector_Intrinsics_vec512_zero;
  acc[2U] = Lib_IntVector_Intrinsics_vec512_zero;
  acc[3U] = Lib_IntVector_Intrinsics_vec512_zero;
  acc[4U] = Lib_IntVector_Intrinsics_vec512_zero;
  u0 = load64_le(kr);
  lo = u0;
  u = load64_le(kr + (u32)8U);
  hi = u;
  mask0 = (u64)0x0ffffffc0fffffffU;
  mask1 = (u64)0x0ffffffc0ffffffcU;
  lo1 = lo & mask0;
  hi1 = hi & mask1;
  r = pre;
  r5 = pre + (u32)5U;
  rn = pre + (u32)10U;
  rn_5 = pre + (u32)15U;
  r_vec0 = Lib_IntVector_Intrinsics_vec512_load64(lo1);
  r_vec1 = Lib_IntVector_Intrinsics_vec512_load64(hi1);
  f00 =
    Lib_IntVector_Intrinsics_vec512_and(r_vec0,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  f15 =
    Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(r_vec0,
        (u32)26U),
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  f25 =
    Lib_IntVector_Intrinsics_vec512_or(Lib_IntVector_Intrinsics_vec512_shift_right64(r_vec0,
        (u32)52U),
      Lib_IntVector_Intrinsics_vec512_shift_left64(Lib_IntVector_Intrinsics_vec512_and(r_vec1,
          Lib_IntVector_Intrinsics_vec512_load64((u64)0x3fffU)),
        (u32)12U));
  f30 =
    Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(r_vec1,
        (u32)14U),
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  f40 = Lib_IntVector_Intrinsics_vec512_shift_right64(r_vec1, (u32)40U);
  f0 = f00;
  f1 = f15;
  f2 = f25;
  f3 = f30;
  f4 = f40;
  r[0U] = f0;
  r[1U] = f1;
  r[2U] = f2;
  r[3U] = f3;
  r[4U] = f4;
  f200 = r[0U];
  f210 = r[1U];
  f220 = r[2U];
  f230 = r[3U];
  f240 = r[4U];
  r5[0U] = Lib_IntVector_Intrinsics_vec512_smul64(f200, (u32)(u64)5U);
  r5[1U] = Lib_IntVector_Intrinsics_vec512_smul64(f210, (u32)(u64)5U);
  r5[2U] = Lib_IntVector_Intrinsics_vec512_smul64(f220, (u32)(u64)5U);
  r5[3U] = Lib_IntVector_Intrinsics_vec512_smul64(f230, (u32)(u64)5U);
  r5[4U] = Lib_IntVector_Intrinsics_vec512_smul64(f240, (u32)(u64)5U);
  r00 = r[0U];
  r10 = r[1U];
  r20 = r[2U];
  r30 = r[3U];
  r40 = r[4U];
  r510 = r5[1U];
  r520 = r5[2U];
  r530 = r5[3U];
  r540 = r5[4U];
  f100 = r[0U];
  f110 = r[1U];
  f120 = r[2U];
  f130 = r[3U];
  f140 = r[4U];
  a00 = Lib_IntVector_Intrinsics_vec512_mul64(r00, f100);
  a10 = Lib_IntVector_Intrinsics_vec512_mul64(r10, f100);
  a20 = Lib_IntVector_Intrinsics_vec512_mul64(r20, f100);
  a30 = Lib_IntVector_Intrinsics_vec512_mul64(r30, f100);
  a40 = Lib_IntVector_Intrinsics_vec512_mul64(r40, f100);
  a010 =
    Lib_IntVector_Intrinsics_vec512_add64(a00,
      Lib_IntVector_Intrinsics_vec512_mul64(r540, f110));
  a110 =
    Lib_IntVector_Intrinsics_vec512_add64(a10,
      Lib_IntVector_Intrinsics_vec512_mul64(r00, f110));
  a210 =
    Lib_IntVector_Intrinsics_vec512_add64(a20,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, f110));
  a310 =
    Lib_IntVector_Intrinsics_vec512_add64(a30,
      Lib_IntVector_Intrinsics_vec512_mul64(r20, f110));
  a410 =
    Lib_IntVector_Intrinsics_vec512_add64(a40,
      Lib_IntVector_Intrinsics_vec512_mul64(r30, f110));
  a020 =
    Lib_IntVector_Intrinsics_vec512_add64(a010,
      Lib_IntVector_Intrinsics_vec512_mul64(r530, f120));
  a120 =
    Lib_IntVector_Intrinsics_vec512_add64(a110,
      Lib_IntVector_Intrinsics_vec512_mul64(r540, f120));
  a220 =
    Lib_IntVector_Intrinsics_vec512_add64(a210,
      Lib_IntVector_Intrinsics_vec512_mul64(r00, f120));
  a320 =
    Lib_IntVector_Intrinsics_vec512_add64(a310,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, f120));
  a420 =
    Lib_IntVector_Intrinsics_vec512_add64(a410,
      Lib_IntVector_Intrinsics_vec512_mul64(r20, f120));
  a030 =
    Lib_IntVector_Intrinsics_vec512_add64(a020,
      Lib_IntVector_Intrinsics_vec512_mul64(r520, f130));
  a130 =
    Lib_IntVector_Intrinsics_vec512_add64(a120,
      Lib_IntVector_Intrinsics_vec512_mul64(r530, f130));
  a230 =
    Lib_IntVector_Intrinsics_vec512_add64(a220,
      Lib_IntVector_Intrinsics_vec512_mul64(r540, f130));
  a330 =
    Lib_IntVector_Intrinsics_vec512_add64(a320,
      Lib_IntVector_Intrinsics_vec512_mul64(r00, f130));
  a430 =
    Lib_IntVector_Intrinsics_vec512_add64(a420,
      Lib_IntVector_Intrinsics_vec512_mul64(r10, f130));
  a040 =
    Lib_IntVector_Intrinsics_vec512_add64(a030,
      Lib_IntVector_Intrinsics_vec512_mul64(r510, f140));
  a140 =
    Lib_IntVector_Intrinsics_vec512_add64(a130,
      Lib_IntVector_Intrinsics_vec512_mul64(r520, f140));
  a240 =
    Lib_IntVector_Intrinsics_vec512_add64(a230,
      Lib_IntVector_Intrinsics_vec512_mul64(r530, f140));
  a340 =
    Lib_IntVector_Intrinsics_vec512_add64(a330,
      Lib_IntVector_Intrinsics_vec512_mul64(r540, f140));
  a440 =
    Lib_IntVector_Intrinsics_vec512_add64(a430,
      Lib_IntVector_Intrinsics_vec512_mul64(r00, f140));
  t00 = a040;
  t10 = a140;
  t20 = a240;
  t30 = a340;
  t40 = a440;
  mask260 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  z00 = Lib_IntVector_Intrinsics_vec512_shift_right64(t00, (u32)26U);
  z10 = Lib_IntVector_Intrinsics_vec512_shift_right64(t30, (u32)26U);
  x00 = Lib_IntVector_Intrinsics_vec512_and(t00, mask260);
  x30 = Lib_IntVector_Intrinsics_vec512_and(t30, mask260);
  x10 = Lib_IntVector_Intrinsics_vec512_add64(t10, z00);
  x40 = Lib_IntVector_Intrinsics_vec512_add64(t40, z10);
  z010 = Lib_IntVector_Intrinsics_vec512_shift_right64(x10, (u32)26U);
  z110 = Lib_IntVector_Intrinsics_vec512_shift_right64(x40, (u32)26U);
  t5 = Lib_IntVector_Intrinsics_vec512_shift_left64(z110, (u32)2U);
  z120 = Lib_IntVector_Intrinsics_vec512_add64(z110, t5);
  x110 = Lib_IntVector_Intrinsics_vec512_and(x10, mask260);
  x410 = Lib_IntVector_Intrinsics_vec512_and(x40, mask260);
  x20 = Lib_IntVector_Intrinsics_vec512_add64(t20, z010);
  x010 = Lib_IntVector_Intrinsics_vec512_add64(x00, z120);
  z020 = Lib_IntVector_Intrinsics_vec512_shift_right64(x20, (u32)26U);
  z130 = Lib_IntVector_Intrinsics_vec512_shift_right64(x010, (u32)26U);
  x210 = Lib_IntVector_Intrinsics_vec512_and(x20, mask260);
  x020 = Lib_IntVector_Intrinsics_vec512_and(x010, mask260);
  x310 = Lib_IntVector_Intrinsics_vec512_add64(x30, z020);
  x120 = Lib_IntVector_Intrinsics_vec512_add64(x110, z130);
  z030 = Lib_IntVector_Intrinsics_vec512_shift_right64(x310, (u32)26U);
  x320 = Lib_IntVector_Intrinsics_vec512_and(x310, mask260);
  x420 = Lib_IntVector_Intrinsics_vec512_add64(x410, z030);
  o00 = x020;
  o10 = x120;
  o20 = x210;
  o30 = x320;
  o40 = x420;
  rn[0U] = o00;
  rn[1U] = o10;
  rn[2U] = o20;
  rn[3U] = o30;
  rn[4U] = o40;
  f201 = rn[0U];
  f211 = rn[1U];
  f221 = rn[2U];
  f231 = rn[3U];
  f241 = rn[4U];
  rn_5[0U] = Lib_IntVector_Intrinsics_vec512_smul64(f201, (u32)(u64)5U);
  rn_5[1U] = Lib_IntVector_Intrinsics_vec512_smul64(f211, (u32)(u64)5U);
  rn_5[2U] = Lib_IntVector_Intrinsics_vec512_smul64(f221, (u32)(u64)5U);
  rn_5[3U] = Lib_IntVector_Intrinsics_vec512_smul64(f231, (u32)(u64)5U);
  rn_5[4U] = Lib_IntVector_Intrinsics_vec512_smul64(f241, (u32)(u64)5U);
  r01 = rn[0U];
  r11 = rn[1U];
  r21 = rn[2U];
  r31 = rn[3U];
  r41 = rn[4U];
  r511 = rn_5[1U];
  r521 = rn_5[2U];
  r531 = rn_5[3U];
  r541 = rn_5[4U];
  f101 = rn[0U];
  f111 = rn[1U];
  f121 = rn[2U];
  f131 = rn[3U];
  f141 = rn[4U];
  a05 = Lib_IntVector_Intrinsics_vec512_mul64(r01, f101);
  a15 = Lib_IntVector_Intrinsics_vec512_mul64(r11, f101);
  a25 = Lib_IntVector_Intrinsics_vec512_mul64(r21, f101);
  a35 = Lib_IntVector_Intrinsics_vec512_mul64(r31, f101);
  a45 = Lib_IntVector_Intrinsics_vec512_mul64(r41, f101);
  a011 =
    Lib_IntVector_Intrinsics_vec512_add64(a05,
      Lib_IntVector_Intrinsics_vec512_mul64(r541, f111));
  a111 =
    Lib_IntVector_Intrinsics_vec512_add64(a15,
      Lib_IntVector_Intrinsics_vec512_mul64(r01, f111));
  a211 =
    Lib_IntVector_Intrinsics_vec512_add64(a25,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, f111));
  a311 =
    Lib_IntVector_Intrinsics_vec512_add64(a35,
      Lib_IntVector_Intrinsics_vec512_mul64(r21, f111));
  a411 =
    Lib_IntVector_Intrinsics_vec512_add64(a45,
      Lib_IntVector_Intrinsics_vec512_mul64(r31, f111));
  a021 =
    Lib_IntVector_Intrinsics_vec512_add64(a011,
      Lib_IntVector_Intrinsics_vec512_mul64(r531, f121));
  a121 =
    Lib_IntVector_Intrinsics_vec512_add64(a111,
      Lib_IntVector_Intrinsics_vec512_mul64(r541, f121));
  a221 =
    Lib_IntVector_Intrinsics_vec512_add64(a211,
      Lib_IntVector_Intrinsics_vec512_mul64(r01, f121));
  a321 =
    Lib_IntVector_Intrinsics_vec512_add64(a311,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, f121));
  a421 =
    Lib_IntVector_Intrinsics_vec512_add64(a411,
      Lib_IntVector_Intrinsics_vec512_mul64(r21, f121));
  a031 =
    Lib_IntVector_Intrinsics_vec512_add64(a021,
      Lib_IntVector_Intrinsics_vec512_mul64(r521, f131));
  a131 =
    Lib_IntVector_Intrinsics_vec512_add64(a121,
      Lib_IntVector_Intrinsics_vec512_mul64(r531, f131));
  a231 =
    Lib_IntVector_Intrinsics_vec512_add64(a221,
      Lib_IntVector_Intrinsics_vec512_mul64(r541, f131));
  a331 =
    Lib_IntVector_Intrinsics_vec512_add64(a321,
      Lib_IntVector_Intrinsics_vec512_mul64(r01, f131));
  a431 =
    Lib_IntVector_Intrinsics_vec512_add64(a421,
      Lib_IntVector_Intrinsics_vec512_mul64(r11, f131));
  a041 =
    Lib_IntVector_Intrinsics_vec512_add64(a031,
      Lib_IntVector_Intrinsics_vec512_mul64(r511, f141));
  a141 =
    Lib_IntVector_Intrinsics_vec512_add64(a131,
      Lib_IntVector_Intrinsics_vec512_mul64(r521, f141));
  a241 =
    Lib_IntVector_Intrinsics_vec512_add64(a231,
      Lib_IntVector_Intrinsics_vec512_mul64(r531, f141));
  a341 =
    Lib_IntVector_Intrinsics_vec512_add64(a331,
      Lib_IntVector_Intrinsics_vec512_mul64(r541, f141));
  a441 =
    Lib_IntVector_Intrinsics_vec512_add64(a431,
      Lib_IntVector_Intrinsics_vec512_mul64(r01, f141));
  t01 = a041;
  t11 = a141;
  t21 = a241;
  t31 = a341;
  t41 = a441;
  mask261 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  z04 = Lib_IntVector_Intrinsics_vec512_shift_right64(t01, (u32)26U);
  z14 = Lib_IntVector_Intrinsics_vec512_shift_right64(t31, (u32)26U);
  x03 = Lib_IntVector_Intrinsics_vec512_and(t01, mask261);
  x33 = Lib_IntVector_Intrinsics_vec512_and(t31, mask261);
  x13 = Lib_IntVector_Intrinsics_vec512_add64(t11, z04);
  x43 = Lib_IntVector_Intrinsics_vec512_add64(t41, z14);
  z011 = Lib_IntVector_Intrinsics_vec512_shift_right64(x13, (u32)26U);
  z111 = Lib_IntVector_Intrinsics_vec512_shift_right64(x43, (u32)26U);
  t6 = Lib_IntVector_Intrinsics_vec512_shift_left64(z111, (u32)2U);
  z121 = Lib_IntVector_Intrinsics_vec512_add64(z111, t6);
  x111 = Lib_IntVector_Intrinsics_vec512_and(x13, mask261);
  x411 = Lib_IntVector_Intrinsics_vec512_and(x43, mask261);
  x22 = Lib_IntVector_Intrinsics_vec512_add64(t21, z011);
  x011 = Lib_IntVector_Intrinsics_vec512_add64(x03, z121);
  z021 = Lib_IntVector_Intrinsics_vec512_shift_right64(x22, (u32)26U);
  z131 = Lib_IntVector_Intrinsics_vec512_shift_right64(x011, (u32)26U);
  x211 = Lib_IntVector_Intrinsics_vec512_and(x22, mask261);
  x021 = Lib_IntVector_Intrinsics_vec512_and(x011, mask261);
  x311 = Lib_IntVector_Intrinsics_vec512_add64(x33, z021);
  x121 = Lib_IntVector_Intrinsics_vec512_add64(x111, z131);
  z031 = Lib_IntVector_Intrinsics_vec512_shift_right64(x311, (u32)26U);
  x321 = Lib_IntVector_Intrinsics_vec512_and(x311, mask261);
  x421 = Lib_IntVector_Intrinsics_vec512_add64(x411, z031);
  o01 = x021;
  o11 = x121;
  o21 = x211;
  o31 = x321;
  o41 = x421;
  rn[0U] = o01;
  rn[1U] = o11;
  rn[2U] = o21;
  rn[3U] = o31;
  rn[4U] = o41;
  f202 = rn[0U];
  f212 = rn[1U];
  f222 = rn[2U];
  f232 = rn[3U];
  f242 = rn[4U];
  rn_5[0U] = Lib_IntVector_Intrinsics_vec512_smul64(f202, (u32)(u64)5U);
  rn_5[1U] = Lib_IntVector_Intrinsics_vec512_smul64(f212, (u32)(u64)5U);
  rn_5[2U] = Lib_IntVector_Intrinsics_vec512_smul64(f222, (u32)(u64)5U);
  rn_5[3U] = Lib_IntVector_Intrinsics_vec512_smul64(f232, (u32)(u64)5U);
  rn_5[4U] = Lib_IntVector_Intrinsics_vec512_smul64(f242, (u32)(u64)5U);
  r0 = rn[0U];
  r1 = rn[1U];
  r2 = rn[2U];
  r3 = rn[3U];
  r4 = rn[4U];
  r51 = rn_5[1U];
  r52 = rn_5[2U];
  r53 = rn_5[3U];
  r54 = rn_5[4U];
  f10 = rn[0U];
  f11 = rn[1U];
  f12 = rn[2U];
  f13 = rn[3U];
  f14 = rn[4U];
  a0 = Lib_IntVector_Intrinsics_vec512_mul64(r0, f10);
  a1 = Lib_IntVector_Intrinsics_vec512_mul64(r1, f10);
  a2 = Lib_IntVector_Intrinsics_vec512_mul64(r2, f10);
  a3 = Lib_IntVector_Intrinsics_vec512_mul64(r3, f10);
  a4 = Lib_IntVector_Intrinsics_vec512_mul64(r4, f10);
  a01 =
    Lib_IntVector_Intrinsics_vec512_add64(a0,
      Lib_IntVector_Intrinsics_vec512_mul64(r54, f11));
  a11 = Lib_IntVector_Intrinsics_vec512_add64(a1, Lib_IntVector_Intrinsics_vec512_mul64(r0, f11));
  a21 = Lib_IntVector_Intrinsics_vec512_add64(a2, Lib_IntVector_Intrinsics_vec512_mul64(r1, f11));
  a31 = Lib_IntVector_Intrinsics_vec512_add64(a3, Lib_IntVector_Intrinsics_vec512_mul64(r2, f11));
  a41 = Lib_IntVector_Intrinsics_vec512_add64(a4, Lib_IntVector_Intrinsics_vec512_mul64(r3, f11));
  a02 =
    Lib_IntVector_Intrinsics_vec512_add64(a01,
      Lib_IntVector_Intrinsics_vec512_mul64(r53, f12));
  a12 =
    Lib_IntVector_Intrinsics_vec512_add64(a11,
      Lib_IntVector_Intrinsics_vec512_mul64(r54, f12));
  a22 =
    Lib_IntVector_Intrinsics_vec512_add64(a21,
      Lib_IntVector_Intrinsics_vec512_mul64(r0, f12));
  a32 =
    Lib_IntVector_Intrinsics_vec512_add64(a31,
      Lib_IntVector_Intrinsics_vec512_mul64(r1, f12));
  a42 =
    Lib_IntVector_Intrinsics_vec512_add64(a41,
      Lib_IntVector_Intrinsics_vec512_mul64(r2, f12));
  a03 =
    Lib_IntVector_Intrinsics_vec512_add64(a02,
      Lib_IntVector_Intrinsics_vec512_mul64(r52, f13));
  a13 =
    Lib_IntVector_Intrinsics_vec512_add64(a12,
      Lib_IntVector_Intrinsics_vec512_mul64(r53, f13));
  a23 =
    Lib_IntVector_Intrinsics_vec512_add64(a22,
      Lib_IntVector_Intrinsics_vec512_mul64(r54, f13));
  a33 =
    Lib_IntVector_Intrinsics_vec512_add64(a32,
      Lib_IntVector_Intrinsics_vec512_mul64(r0, f13));
  a43 =
    Lib_IntVector_Intrinsics_vec512_add64(a42,
      Lib_IntVector_Intrinsics_vec512_mul64(r1, f13));
  a04 =
    Lib_IntVector_Intrinsics_vec512_add64(a03,
      Lib_IntVector_Intrinsics_vec512_mul64(r51, f14));
  a14 =
    Lib_IntVector_Intrinsics_vec512_add64(a13,
      Lib_IntVector_Intrinsics_vec512_mul64(r52, f14));
  a24 =
    Lib_IntVector_Intrinsics_vec512_add64(a23,
      Lib_IntVector_Intrinsics_vec512_mul64(r53, f14));
  a34 =
    Lib_IntVector_Intrinsics_vec512_add64(a33,
      Lib_IntVector_Intrinsics_vec512_mul64(r54, f14));
  a44 =
    Lib_IntVector_Intrinsics_vec512_add64(a43,
      Lib_IntVector_Intrinsics_vec512_mul64(r0, f14));
  t0 = a04;
  t1 = a14;
  t2 = a24;
  t3 = a34;
  t4 = a44;
  mask26 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  z0 = Lib_IntVector_Intrinsics_vec512_shift_right64(t0, (u32)26U);
  z1 = Lib_IntVector_Intrinsics_vec512_shift_right64(t3, (u32)26U);
  x0 = Lib_IntVector_Intrinsics_vec512_and(t0, mask26);
  x3 = Lib_IntVector_Intrinsics_vec512_and(t3, mask26);
  x1 = Lib_IntVector_Intrinsics_vec512_add64(t1, z0);
  x4 = Lib_IntVector_Intrinsics_vec512_add64(t4, z1);
  z01 = Lib_IntVector_Intrinsics_vec512_shift_right64(x1, (u32)26U);
  z11 = Lib_IntVector_Intrinsics_vec512_shift_right64(x4, (u32)26U);
  t = Lib_IntVector_Intrinsics_vec512_shift_left64(z11, (u32)2U);
  z12 = Lib_IntVector_Intrinsics_vec512_add64(z11, t);
  x11 = Lib_IntVector_Intrinsics_vec512_and(x1, mask26);
  x41 = Lib_IntVector_Intrinsics_vec512_and(x4, mask26);
  x2 = Lib_IntVector_Intrinsics_vec512_add64(t2, z01);
  x01 = Lib_IntVector_Intrinsics_vec512_add64(x0, z12);
  z02 = Lib_IntVector_Intrinsics_vec512_shift_right64(x2, (u32)26U);
  z13 = Lib_IntVector_Intrinsics_vec512_shift_right64(x01, (u32)26U);
  x21 = Lib_IntVector_Intrinsics_vec512_and(x2, mask26);
  x02 = Lib_IntVector_Intrinsics_vec512_and(x01, mask26);
  x31 = Lib_IntVector_Intrinsics_vec512_add64(x3, z02);
  x12 = Lib_IntVector_Intrinsics_vec512_add64(x11, z13);
  z03 = Lib_IntVector_Intrinsics_vec512_shift_right64(x31, (u32)26U);
  x32 = Lib_IntVector_Intrinsics_vec512_and(x31, mask26);
  x42 = Lib_IntVector_Intrinsics_vec512_add64(x41, z03);
  o0 = x02;
  o1 = x12;
  o2 = x21;
  o3 = x32;
  o4 = x42;
  rn[0U] = o0;
  rn[1U] = o1;
  rn[2U] = o2;
  rn[3U] = o3;
  rn[4U] = o4;
  f20 = rn[0U];
  f21 = rn[1U];
  f22 = rn[2U];
  f23 = rn[3U];
  f24 = rn[4U];
  rn_5[0U] = Lib_IntVector_Intrinsics_vec512_smul64(f20, (u32)(u64)5U);
  rn_5[1U] = Lib_IntVector_Intrinsics_vec512_smul64(f21, (u32)(u64)5U);
  rn_5[2U] = Lib_IntVector_Intrinsics_vec512_smul64(f22, (u32)(u64)5U);
  rn_5[3U] = Lib_IntVector_Intrinsics_vec512_smul64(f23, (u32)(u64)5U);
  rn_5[4U] = Lib_IntVector_Intrinsics_vec512_smul64(f24, (u32)(u64)5U);
}

void Hacl_Poly1305_512_poly1305_update1(Lib_IntVector_Intrinsics_vec512 *ctx, u8 *text)
{
  Lib_IntVector_Intrinsics_vec512 *pre = ctx + (u32)5U;
  Lib_IntVector_Intrinsics_vec512 *acc = ctx;
  KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec512), (u32)5U);
  {
    Lib_IntVector_Intrinsics_vec512 e[5U];
    {
      u32 _i;
      for (_i = 0U; _i < (u32)5U; ++_i)
        e[_i] = Lib_IntVector_Intrinsics_vec512_zero;
    }
    {
      u64 u0 = load64_le(text);
      u64 lo = u0;
      u64 u = load64_le(text + (u32)8U);
      u64 hi = u;
      Lib_IntVector_Intrinsics_vec512 f0 = Lib_IntVector_Intrinsics_vec512_load64(lo);
      Lib_IntVector_Intrinsics_vec512 f1 = Lib_IntVector_Intrinsics_vec512_load64(hi);
      Lib_IntVector_Intrinsics_vec512
      f010 =
        Lib_IntVector_Intrinsics_vec512_and(f0,
          Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec512
      f110 =
        Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(f0,
            (u32)26U),
          Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec512
      f20 =
        Lib_IntVector_Intrinsics_vec512_or(Lib_IntVector_Intrinsics_vec512_shift_right64(f0,
            (u32)52U),
          Lib_IntVector_Intrinsics_vec512_shift_left64(Lib_IntVector_Intrinsics_vec512_and(f1,
              Lib_IntVector_Intrinsics_vec512_load64((u64)0x3fffU)),
            (u32)12U));
      Lib_IntVector_Intrinsics_vec512
      f30 =
        Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(f1,
            (u32)14U),
          Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec512
      f40 = Lib_IntVector_Intrinsics_vec512_shift_right64(f1, (u32)40U);
      Lib_IntVector_Intrinsics_vec512 f01 = f010;
      Lib_IntVector_Intrinsics_vec512 f111 = f110;
      Lib_IntVector_Intrinsics_vec512 f2 = f20;
      Lib_IntVector_Intrinsics_vec512 f3 = f30;
      Lib_IntVector_Intrinsics_vec512 f41 = f40;
      u64 b;
      Lib_IntVector_Intrinsics_vec512 mask;
      Lib_IntVector_Intrinsics_vec512 f4;
      Lib_IntVector_Intrinsics_vec512 *r;
      Lib_IntVector_Intrinsics_vec512 *r5;
      Lib_IntVector_Intrinsics_vec512 r0;
      Lib_IntVector_Intrinsics_vec512 r1;
      Lib_IntVector_Intrinsics_vec512 r2;
      Lib_IntVector_Intrinsics_vec512 r3;
      Lib_IntVector_Intrinsics_vec512 r4;
      Lib_IntVector_Intrinsics_vec512 r51;
      Lib_IntVector_Intrinsics_vec512 r52;
      Lib_IntVector_Intrinsics_vec512 r53;
      Lib_IntVector_Intrinsics_vec512 r54;
      Lib_IntVector_Intrinsics_vec512 f10;
      Lib_IntVector_Intrinsics_vec512 f11;
      Lib_IntVector_Intrinsics_vec512 f12;
      Lib_IntVector_Intrinsics_vec512 f13;
      Lib_IntVector_Intrinsics_vec512 f14;
      Lib_IntVector_Intrinsics_vec512 a0;
      Lib_IntVector_Intrinsics_vec512 a1;
      Lib_IntVector_Intrinsics_vec512 a2;
      Lib_IntVector_Intrinsics_vec512 a3;
      Lib_IntVector_Intrinsics_vec512 a4;
      Lib_IntVector_Intrinsics_vec512 a01;
      Lib_IntVector_Intrinsics_vec512 a11;
      Lib_IntVector_Intrinsics_vec512 a21;
      Lib_IntVector_Intrinsics_vec512 a31;
      Lib_IntVector_Intrinsics_vec512 a41;
      Lib_IntVector_Intrinsics_vec512 a02;
      Lib_IntVector_Intrinsics_vec512 a12;
      Lib_IntVector_Intrinsics_vec512 a22;
      Lib_IntVector_Intrinsics_vec512 a32;
      Lib_IntVector_Intrinsics_vec512 a42;
      Lib_IntVector_Intrinsics_vec512 a03;
      Lib_IntVector_Intrinsics_vec512 a13;
      Lib_IntVector_Intrinsics_vec512 a23;
      Lib_IntVector_Intrinsics_vec512 a33;
      Lib_IntVector_Intrinsics_vec512 a43;
      Lib_IntVector_Intrinsics_vec512 a04;
      Lib_IntVector_Intrinsics_vec512 a14;
      Lib_IntVector_Intrinsics_vec512 a24;
      Lib_IntVector_Intrinsics_vec512 a34;
      Lib_IntVector_Intrinsics_vec512 a44;
      Lib_IntVector_Intrinsics_vec512 a05;
      Lib_IntVector_Intrinsics_vec512 a15;
      Lib_IntVector_Intrinsics_vec512 a25;
      Lib_IntVector_Intrinsics_vec512 a35;
      Lib_IntVector_Intrinsics_vec512 a45;
      Lib_IntVector_Intrinsics_vec512 a06;
      Lib_IntVector_Intrinsics_vec512 a16;
      Lib_IntVector_Intrinsics_vec512 a26;
      Lib_IntVector_Intrinsics_vec512 a36;
      Lib_IntVector_Intrinsics_vec512 a46;
      Lib_IntVector_Intrinsics_vec512 t0;
      Lib_IntVector_Intrinsics_vec512 t1;
      Lib_IntVector_Intrinsics_vec512 t2;
      Lib_IntVector_Intrinsics_vec512 t3;
      Lib_IntVector_Intrinsics_vec512 t4;
      Lib_IntVector_Intrinsics_vec512 mask26;
      Lib_IntVector_Intrinsics_vec512 z0;
      Lib_IntVector_Intrinsics_vec512 z1;
      Lib_IntVector_Intrinsics_vec512 x0;
      Lib_IntVector_Intrinsics_vec512 x3;
      Lib_IntVector_Intrinsics_vec512 x1;
      Lib_IntVector_Intrinsics_vec512 x4;
      Lib_IntVector_Intrinsics_vec512 z01;
      Lib_IntVector_Intrinsics_vec512 z11;
      Lib_IntVector_Intrinsics_vec512 t;
      Lib_IntVector_Intrinsics_vec512 z12;
      Lib_IntVector_Intrinsics_vec512 x11;
      Lib_IntVector_Intrinsics_vec512 x41;
      Lib_IntVector_Intrinsics_vec512 x2;
      Lib_IntVector_Intrinsics_vec512 x01;
      Lib_IntVector_Intrinsics_vec512 z02;
      Lib_IntVector_Intrinsics_vec512 z13;
      Lib_IntVector_Intrinsics_vec512 x21;
      Lib_IntVector_Intrinsics_vec512 x02;
      Lib_IntVector_Intrinsics_vec512 x31;
      Lib_IntVector_Intrinsics_vec512 x12;
      Lib_IntVector_Intrinsics_vec512 z03;
      Lib_IntVector_Intrinsics_vec512 x32;
      Lib_IntVector_Intrinsics_vec512 x42;
      Lib_IntVector_Intrinsics_vec512 o0;
      Lib_IntVector_Intrinsics_vec512 o1;
      Lib_IntVector_Intrinsics_vec512 o2;
      Lib_IntVector_Intrinsics_vec512 o3;
      Lib_IntVector_Intrinsics_vec512 o4;
      e[0U] = f01;
      e[1U] = f111;
      e[2U] = f2;
      e[3U] = f3;
      e[4U] = f41;
      b = (u64)0x1000000U;
      mask = Lib_IntVector_Intrinsics_vec512_load64(b);
      f4 = e[4U];
      e[4U] = Lib_IntVector_Intrinsics_vec512_or(f4, mask);
      r = pre;
      r5 = pre + (u32)5U;
      r0 = r[0U];
      r1 = r[1U];
      r2 = r[2U];
      r3 = r[3U];
      r4 = r[4U];
      r51 = r5[1U];
      r52 = r5[2U];
      r53 = r5[3U];
      r54 = r5[4U];
      f10 = e[0U];
      f11 = e[1U];
      f12 = e[2U];
      f13 = e[3U];
      f14 = e[4U];
      a0 = acc[0U];
      a1 = acc[1U];
      a2 = acc[2U];
      a3 = acc[3U];
      a4 = acc[4U];
      a01 = Lib_IntVector_Intrinsics_vec512_add64(a0, f10);
      a11 = Lib_IntVector_Intrinsics_vec512_add64(a1, f11);
      a21 = Lib_IntVector_Intrinsics_vec512_add64(a2, f12);
      a31 = Lib_IntVector_Intrinsics_vec512_add64(a3, f13);
      a41 = Lib_IntVector_Intrinsics_vec512_add64(a4, f14);
      a02 = Lib_IntVector_Intrinsics_vec512_mul64(r0, a01);
      a12 = Lib_IntVector_Intrinsics_vec512_mul64(r1, a01);
      a22 = Lib_IntVector_Intrinsics_vec512_mul64(r2, a01);
      a32 = Lib_IntVector_Intrinsics_vec512_mul64(r3, a01);
      a42 = Lib_IntVector_Intrinsics_vec512_mul64(r4, a01);
      a03 =
        Lib_IntVector_Intrinsics_vec512_add64(a02,
          Lib_IntVector_Intrinsics_vec512_mul64(r54, a11));
      a13 =
        Lib_IntVector_Intrinsics_vec512_add64(a12,
          Lib_IntVector_Intrinsics_vec512_mul64(r0, a11));
      a23 =
        Lib_IntVector_Intrinsics_vec512_add64(a22,
          Lib_IntVector_Intrinsics_vec512_mul64(r1, a11));
      a33 =
        Lib_IntVector_Intrinsics_vec512_add64(a32,
          Lib_IntVector_Intrinsics_vec512_mul64(r2, a11));
      a43 =
        Lib_IntVector_Intrinsics_vec512_add64(a42,
          Lib_IntVector_Intrinsics_vec512_mul64(r3, a11));
      a04 =
        Lib_IntVector_Intrinsics_vec512_add64(a03,
          Lib_IntVector_Intrinsics_vec512_mul64(r53, a21));
      a14 =
        Lib_IntVector_Intrinsics_vec512_add64(a13,
          Lib_IntVector_Intrinsics_vec512_mul64(r54, a21));
      a24 =
        Lib_IntVector_Intrinsics_vec512_add64(a23,
          Lib_IntVector_Intrinsics_vec512_mul64(r0, a21));
      a34 =
        Lib_IntVector_Intrinsics_vec512_add64(a33,
          Lib_IntVector_Intrinsics_vec512_mul64(r1, a21));
      a44 =
        Lib_IntVector_Intrinsics_vec512_add64(a43,
          Lib_IntVector_Intrinsics_vec512_mul64(r2, a21));
      a05 =
        Lib_IntVector_Intrinsics_vec512_add64(a04,
          Lib_IntVector_Intrinsics_vec512_mul64(r52, a31));
      a15 =
        Lib_IntVector_Intrinsics_vec512_add64(a14,
          Lib_IntVector_Intrinsics_vec512_mul64(r53, a31));
      a25 =
        Lib_IntVector_Intrinsics_vec512_add64(a24,
          Lib_IntVector_Intrinsics_vec512_mul64(r54, a31));
      a35 =
        Lib_IntVector_Intrinsics_vec512_add64(a34,
          Lib_IntVector_Intrinsics_vec512_mul64(r0, a31));
      a45 =
        Lib_IntVector_Intrinsics_vec512_add64(a44,
          Lib_IntVector_Intrinsics_vec512_mul64(r1, a31));
      a06 =
        Lib_IntVector_Intrinsics_vec512_add64(a05,
          Lib_IntVector_Intrinsics_vec512_mul64(r51, a41));
      a16 =
        Lib_IntVector_Intrinsics_vec512_add64(a15,
          Lib_IntVector_Intrinsics_vec512_mul64(r52, a41));
      a26 =
        Lib_IntVector_Intrinsics_vec512_add64(a25,
          Lib_IntVector_Intrinsics_vec512_mul64(r53, a41));
      a36 =
        Lib_IntVector_Intrinsics_vec512_add64(a35,
          Lib_IntVector_Intrinsics_vec512_mul64(r54, a41));
      a46 =
        Lib_IntVector_Intrinsics_vec512_add64(a45,
          Lib_IntVector_Intrinsics_vec512_mul64(r0, a41));
      t0 = a06;
      t1 = a16;
      t2 = a26;
      t3 = a36;
      t4 = a46;
      mask26 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
      z0 = Lib_IntVector_Intrinsics_vec512_shift_right64(t0, (u32)26U);
      z1 = Lib_IntVector_Intrinsics_vec512_shift_right64(t3, (u32)26U);
      x0 = Lib_IntVector_Intrinsics_vec512_and(t0, mask26);
      x3 = Lib_IntVector_Intrinsics_vec512_and(t3, mask26);
      x1 = Lib_IntVector_Intrinsics_vec512_add64(t1, z0);
      x4 = Lib_IntVector_Intrinsics_vec512_add64(t4, z1);
      z01 = Lib_IntVector_Intrinsics_vec512_shift_right64(x1, (u32)26U);
      z11 = Lib_IntVector_Intrinsics_vec512_shift_right64(x4, (u32)26U);
      t = Lib_IntVector_Intrinsics_vec512_shift_left64(z11, (u32)2U);
      z12 = Lib_IntVector_Intrinsics_vec512_add64(z11, t);
      x11 = Lib_IntVector_Intrinsics_vec512_and(x1, mask26);
      x41 = Lib_IntVector_Intrinsics_vec512_and(x4, mask26);
      x2 = Lib_IntVector_Intrinsics_vec512_add64(t2, z01);
      x01 = Lib_IntVector_Intrinsics_vec512_add64(x0, z12);
      z02 = Lib_IntVector_Intrinsics_vec512_shift_right64(x2, (u32)26U);
      z13 = Lib_IntVector_Intrinsics_vec512_shift_right64(x01, (u32)26U);
      x21 = Lib_IntVector_Intrinsics_vec512_and(x2, mask26);
      x02 = Lib_IntVector_Intrinsics_vec512_and(x01, mask26);
      x31 = Lib_IntVector_Intrinsics_vec512_add64(x3, z02);
      x12 = Lib_IntVector_Intrinsics_vec512_add64(x11, z13);
      z03 = Lib_IntVector_Intrinsics_vec512_shift_right64(x31, (u32)26U);
      x32 = Lib_IntVector_Intrinsics_vec512_and(x31, mask26);
      x42 = Lib_IntVector_Intrinsics_vec512_add64(x41, z03);
      o0 = x02;
      o1 = x12;
      o2 = x21;
      o3 = x32;
      o4 = x42;
      acc[0U] = o0;
      acc[1U] = o1;
      acc[2U] = o2;
      acc[3U] = o3;
      acc[4U] = o4;
    }
  }
}

void Hacl_Poly1305_512_poly1305_update(Lib_IntVector_Intrinsics_vec512 *ctx, u32 len, u8 *text)
{
  Lib_IntVector_Intrinsics_vec512 *pre = ctx + (u32)5U;
  Lib_IntVector_Intrinsics_vec512 *acc = ctx;
  u32 sz_block = (u32)128U;
  u32 len0 = len / sz_block * sz_block;
  u8 *t0 = text;
  u32 len1;
  u8 *t10;
  u32 nb0;
  u32 rem;
  if (len0 > (u32)0U)
  {
    u32 bs = (u32)128U;
    u8 *text0 = t0;
    load_acc8(acc, text0);
    {
      u32 len10 = len0 - bs;
      u8 *text1 = t0 + bs;
      u32 nb = len10 / bs;
      {
        u32 i;
        for (i = (u32)0U; i < nb; i++)
        {
          u8 *block = text1 + i * bs;
          KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec512), (u32)5U);
          {
            Lib_IntVector_Intrinsics_vec512 e[5U];
            {
              u32 _i;
              for (_i = 0U; _i < (u32)5U; ++_i)
                e[_i] = Lib_IntVector_Intrinsics_vec512_zero;
            }
            {
              Lib_IntVector_Intrinsics_vec512 b1 = Lib_IntVector_Intrinsics_vec512_load_le(block);
              Lib_IntVector_Intrinsics_vec512
              b2 = Lib_IntVector_Intrinsics_vec512_load_le(block + (u32)64U);
              Lib_IntVector_Intrinsics_vec512
              lo0 = Lib_IntVector_Intrinsics_vec512_interleave_low256(b1, b2);
              Lib_IntVector_Intrinsics_vec512
              hi0 = Lib_IntVector_Intrinsics_vec512_interleave_high256(b1, b2);
              Lib_IntVector_Intrinsics_vec512
              lo1 = Lib_IntVector_Intrinsics_vec512_interleave_low128(lo0, hi0);
              Lib_IntVector_Intrinsics_vec512
              hi1 = Lib_IntVector_Intrinsics_vec512_interleave_high128(lo0, hi0);
              Lib_IntVector_Intrinsics_vec512
              lo = Lib_IntVector_Intrinsics_vec512_interleave_low64(lo1, hi1);
              Lib_IntVector_Intrinsics_vec512
              hi = Lib_IntVector_Intrinsics_vec512_interleave_high64(lo1, hi1);
              Lib_IntVector_Intrinsics_vec512
              f00 =
                Lib_IntVector_Intrinsics_vec512_and(lo,
                  Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
              Lib_IntVector_Intrinsics_vec512
              f15 =
                Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(lo,
                    (u32)26U),
                  Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
              Lib_IntVector_Intrinsics_vec512
              f25 =
                Lib_IntVector_Intrinsics_vec512_or(Lib_IntVector_Intrinsics_vec512_shift_right64(lo,
                    (u32)52U),
                  Lib_IntVector_Intrinsics_vec512_shift_left64(Lib_IntVector_Intrinsics_vec512_and(hi,
                      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3fffU)),
                    (u32)12U));
              Lib_IntVector_Intrinsics_vec512
              f30 =
                Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(hi,
                    (u32)14U),
                  Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
              Lib_IntVector_Intrinsics_vec512
              f40 = Lib_IntVector_Intrinsics_vec512_shift_right64(hi, (u32)40U);
              Lib_IntVector_Intrinsics_vec512 f0 = f00;
              Lib_IntVector_Intrinsics_vec512 f1 = f15;
              Lib_IntVector_Intrinsics_vec512 f2 = f25;
              Lib_IntVector_Intrinsics_vec512 f3 = f30;
              Lib_IntVector_Intrinsics_vec512 f41 = f40;
              e[0U] = f0;
              e[1U] = f1;
              e[2U] = f2;
              e[3U] = f3;
              e[4U] = f41;
              {
                u64 b = (u64)0x1000000U;
                Lib_IntVector_Intrinsics_vec512 mask = Lib_IntVector_Intrinsics_vec512_load64(b);
                Lib_IntVector_Intrinsics_vec512 f4 = e[4U];
                e[4U] = Lib_IntVector_Intrinsics_vec512_or(f4, mask);
                {
                  Lib_IntVector_Intrinsics_vec512 *rn = pre + (u32)10U;
                  Lib_IntVector_Intrinsics_vec512 *rn5 = pre + (u32)15U;
                  Lib_IntVector_Intrinsics_vec512 r0 = rn[0U];
                  Lib_IntVector_Intrinsics_vec512 r1 = rn[1U];
                  Lib_IntVector_Intrinsics_vec512 r2 = rn[2U];
                  Lib_IntVector_Intrinsics_vec512 r3 = rn[3U];
                  Lib_IntVector_Intrinsics_vec512 r4 = rn[4U];
                  Lib_IntVector_Intrinsics_vec512 r51 = rn5[1U];
                  Lib_IntVector_Intrinsics_vec512 r52 = rn5[2U];
                  Lib_IntVector_Intrinsics_vec512 r53 = rn5[3U];
                  Lib_IntVector_Intrinsics_vec512 r54 = rn5[4U];
                  Lib_IntVector_Intrinsics_vec512 f10 = acc[0U];
                  Lib_IntVector_Intrinsics_vec512 f110 = acc[1U];
                  Lib_IntVector_Intrinsics_vec512 f120 = acc[2U];
                  Lib_IntVector_Intrinsics_vec512 f130 = acc[3U];
                  Lib_IntVector_Intrinsics_vec512 f140 = acc[4U];
                  Lib_IntVector_Intrinsics_vec512
                  a0 = Lib_IntVector_Intrinsics_vec512_mul64(r0, f10);
                  Lib_IntVector_Intrinsics_vec512
                  a1 = Lib_IntVector_Intrinsics_vec512_mul64(r1, f10);
                  Lib_IntVector_Intrinsics_vec512
                  a2 = Lib_IntVector_Intrinsics_vec512_mul64(r2, f10);
                  Lib_IntVector_Intrinsics_vec512
                  a3 = Lib_IntVector_Intrinsics_vec512_mul64(r3, f10);
                  Lib_IntVector_Intrinsics_vec512
                  a4 = Lib_IntVector_Intrinsics_vec512_mul64(r4, f10);
                  Lib_IntVector_Intrinsics_vec512
                  a01 =
                    Lib_IntVector_Intrinsics_vec512_add64(a0,
                      Lib_IntVector_Intrinsics_vec512_mul64(r54, f110));
                  Lib_IntVector_Intrinsics_vec512
                  a11 =
                    Lib_IntVector_Intrinsics_vec512_add64(a1,
                      Lib_IntVector_Intrinsics_vec512_mul64(r0, f110));
                  Lib_IntVector_Intrinsics_vec512
                  a21 =
                    Lib_IntVector_Intrinsics_vec512_add64(a2,
                      Lib_IntVector_Intrinsics_vec512_mul64(r1, f110));
                  Lib_IntVector_Intrinsics_vec512
                  a31 =
                    Lib_IntVector_Intrinsics_vec512_add64(a3,
                      Lib_IntVector_Intrinsics_vec512_mul64(r2, f110));
                  Lib_IntVector_Intrinsics_vec512
                  a41 =
                    Lib_IntVector_Intrinsics_vec512_add64(a4,
                      Lib_IntVector_Intrinsics_vec512_mul64(r3, f110));
                  Lib_IntVector_Intrinsics_vec512
                  a02 =
                    Lib_IntVector_Intrinsics_vec512_add64(a01,
                      Lib_IntVector_Intrinsics_vec512_mul64(r53, f120));
                  Lib_IntVector_Intrinsics_vec512
                  a12 =
                    Lib_IntVector_Intrinsics_vec512_add64(a11,
                      Lib_IntVector_Intrinsics_vec512_mul64(r54, f120));
                  Lib_IntVector_Intrinsics_vec512
                  a22 =
                    Lib_IntVector_Intrinsics_vec512_add64(a21,
                      Lib_IntVector_Intrinsics_vec512_mul64(r0, f120));
                  Lib_IntVector_Intrinsics_vec512
                  a32 =
                    Lib_IntVector_Intrinsics_vec512_add64(a31,
                      Lib_IntVector_Intrinsics_vec512_mul64(r1, f120));
                  Lib_IntVector_Intrinsics_vec512
                  a42 =
                    Lib_IntVector_Intrinsics_vec512_add64(a41,
                      Lib_IntVector_Intrinsics_vec512_mul64(r2, f120));
                  Lib_IntVector_Intrinsics_vec512
                  a03 =
                    Lib_IntVector_Intrinsics_vec512_add64(a02,
                      Lib_IntVector_Intrinsics_vec512_mul64(r52, f130));
                  Lib_IntVector_Intrinsics_vec512
                  a13 =
                    Lib_IntVector_Intrinsics_vec512_add64(a12,
                      Lib_IntVector_Intrinsics_vec512_mul64(r53, f130));
                  Lib_IntVector_Intrinsics_vec512
                  a23 =
                    Lib_IntVector_Intrinsics_vec512_add64(a22,
                      Lib_IntVector_Intrinsics_vec512_mul64(r54, f130));
                  Lib_IntVector_Intrinsics_vec512
                  a33 =
                    Lib_IntVector_Intrinsics_vec512_add64(a32,
                      Lib_IntVector_Intrinsics_vec512_mul64(r0, f130));
                  Lib_IntVector_Intrinsics_vec512
                  a43 =
                    Lib_IntVector_Intrinsics_vec512_add64(a42,
                      Lib_IntVector_Intrinsics_vec512_mul64(r1, f130));
                  Lib_IntVector_Intrinsics_vec512
                  a04 =
                    Lib_IntVector_Intrinsics_vec512_add64(a03,
                      Lib_IntVector_Intrinsics_vec512_mul64(r51, f140));
                  Lib_IntVector_Intrinsics_vec512
                  a14 =
                    Lib_IntVector_Intrinsics_vec512_add64(a13,
                      Lib_IntVector_Intrinsics_vec512_mul64(r52, f140));
                  Lib_IntVector_Intrinsics_vec512
                  a24 =
                    Lib_IntVector_Intrinsics_vec512_add64(a23,
                      Lib_IntVector_Intrinsics_vec512_mul64(r53, f140));
                  Lib_IntVector_Intrinsics_vec512
                  a34 =
                    Lib_IntVector_Intrinsics_vec512_add64(a33,
                      Lib_IntVector_Intrinsics_vec512_mul64(r54, f140));
                  Lib_IntVector_Intrinsics_vec512
                  a44 =
                    Lib_IntVector_Intrinsics_vec512_add64(a43,
                      Lib_IntVector_Intrinsics_vec512_mul64(r0, f140));
                  Lib_IntVector_Intrinsics_vec512 t01 = a04;
                  Lib_IntVector_Intrinsics_vec512 t1 = a14;
                  Lib_IntVector_Intrinsics_vec512 t2 = a24;
                  Lib_IntVector_Intrinsics_vec512 t3 = a34;
                  Lib_IntVector_Intrinsics_vec512 t4 = a44;
                  Lib_IntVector_Intrinsics_vec512
                  mask26 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
                  Lib_IntVector_Intrinsics_vec512
                  z0 = Lib_IntVector_Intrinsics_vec512_shift_right64(t01, (u32)26U);
                  Lib_IntVector_Intrinsics_vec512
                  z1 = Lib_IntVector_Intrinsics_vec512_shift_right64(t3, (u32)26U);
                  Lib_IntVector_Intrinsics_vec512
                  x0 = Lib_IntVector_Intrinsics_vec512_and(t01, mask26);
                  Lib_IntVector_Intrinsics_vec512
                  x3 = Lib_IntVector_Intrinsics_vec512_and(t3, mask26);
                  Lib_IntVector_Intrinsics_vec512
                  x1 = Lib_IntVector_Intrinsics_vec512_add64(t1, z0);
                  Lib_IntVector_Intrinsics_vec512
                  x4 = Lib_IntVector_Intrinsics_vec512_add64(t4, z1);
                  Lib_IntVector_Intrinsics_vec512
                  z01 = Lib_IntVector_Intrinsics_vec512_shift_right64(x1, (u32)26U);
                  Lib_IntVector_Intrinsics_vec512
                  z11 = Lib_IntVector_Intrinsics_vec512_shift_right64(x4, (u32)26U);
                  Lib_IntVector_Intrinsics_vec512
                  t = Lib_IntVector_Intrinsics_vec512_shift_left64(z11, (u32)2U);
                  Lib_IntVector_Intrinsics_vec512
                  z12 = Lib_IntVector_Intrinsics_vec512_add64(z11, t);
                  Lib_IntVector_Intrinsics_vec512
                  x11 = Lib_IntVector_Intrinsics_vec512_and(x1, mask26);
                  Lib_IntVector_Intrinsics_vec512
                  x41 = Lib_IntVector_Intrinsics_vec512_and(x4, mask26);
                  Lib_IntVector_Intrinsics_vec512
                  x2 = Lib_IntVector_Intrinsics_vec512_add64(t2, z01);
                  Lib_IntVector_Intrinsics_vec512
                  x01 = Lib_IntVector_Intrinsics_vec512_add64(x0, z12);
                  Lib_IntVector_Intrinsics_vec512
                  z02 = Lib_IntVector_Intrinsics_vec512_shift_right64(x2, (u32)26U);
                  Lib_IntVector_Intrinsics_vec512
                  z13 = Lib_IntVector_Intrinsics_vec512_shift_right64(x01, (u32)26U);
                  Lib_IntVector_Intrinsics_vec512
                  x21 = Lib_IntVector_Intrinsics_vec512_and(x2, mask26);
                  Lib_IntVector_Intrinsics_vec512
                  x02 = Lib_IntVector_Intrinsics_vec512_and(x01, mask26);
                  Lib_IntVector_Intrinsics_vec512
                  x31 = Lib_IntVector_Intrinsics_vec512_add64(x3, z02);
                  Lib_IntVector_Intrinsics_vec512
                  x12 = Lib_IntVector_Intrinsics_vec512_add64(x11, z13);
                  Lib_IntVector_Intrinsics_vec512
                  z03 = Lib_IntVector_Intrinsics_vec512_shift_right64(x31, (u32)26U);
                  Lib_IntVector_Intrinsics_vec512
                  x32 = Lib_IntVector_Intrinsics_vec512_and(x31, mask26);
                  Lib_IntVector_Intrinsics_vec512
                  x42 = Lib_IntVector_Intrinsics_vec512_add64(x41, z03);
                  Lib_IntVector_Intrinsics_vec512 o00 = x02;
                  Lib_IntVector_Intrinsics_vec512 o10 = x12;
                  Lib_IntVector_Intrinsics_vec512 o20 = x21;
                  Lib_IntVector_Intrinsics_vec512 o30 = x32;
                  Lib_IntVector_Intrinsics_vec512 o40 = x42;
                  acc[0U] = o00;
                  acc[1U] = o10;
                  acc[2U] = o20;
                  acc[3U] = o30;
                  acc[4U] = o40;
                  {
                    Lib_IntVector_Intrinsics_vec512 f100 = acc[0U];
                    Lib_IntVector_Intrinsics_vec512 f11 = acc[1U];
                    Lib_IntVector_Intrinsics_vec512 f12 = acc[2U];
                    Lib_IntVector_Intrinsics_vec512 f13 = acc[3U];
                    Lib_IntVector_Intrinsics_vec512 f14 = acc[4U];
                    Lib_IntVector_Intrinsics_vec512 f20 = e[0U];
                    Lib_IntVector_Intrinsics_vec512 f21 = e[1U];
                    Lib_IntVector_Intrinsics_vec512 f22 = e[2U];
                    Lib_IntVector_Intrinsics_vec512 f23 = e[3U];
                    Lib_IntVector_Intrinsics_vec512 f24 = e[4U];
                    Lib_IntVector_Intrinsics_vec512
                    o0 = Lib_IntVector_Intrinsics_vec512_add64(f100, f20);
                    Lib_IntVector_Intrinsics_vec512
                    o1 = Lib_IntVector_Intrinsics_vec512_add64(f11, f21);
                    Lib_IntVector_Intrinsics_vec512
                    o2 = Lib_IntVector_Intrinsics_vec512_add64(f12, f22);
                    Lib_IntVector_Intrinsics_vec512
                    o3 = Lib_IntVector_Intrinsics_vec512_add64(f13, f23);
                    Lib_IntVector_Intrinsics_vec512
                    o4 = Lib_IntVector_Intrinsics_vec512_add64(f14, f24);
                    acc[0U] = o0;
                    acc[1U] = o1;
                    acc[2U] = o2;
                    acc[3U] = o3;
                    acc[4U] = o4;
                  }
                }
              }
            }
          }
        }
      }
      fmul_r8_normalize(acc, pre);
    }
  }
  len1 = len - len0;
  t10 = text + len0;
  nb0 = len1 / (u32)16U;
  rem = len1 % (u32)16U;
  {
    u32 i;
    for (i = (u32)0U; i < nb0; i++)
    {
      u8 *block = t10 + i * (u32)16U;
      KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec512), (u32)5U);
      {
        Lib_IntVector_Intrinsics_vec512 e[5U];
        {
          u32 _i;
          for (_i = 0U; _i < (u32)5U; ++_i)
            e[_i] = Lib_IntVector_Intrinsics_vec512_zero;
        }
        {
          u64 u0 = load64_le(block);
          u64 lo = u0;
          u64 u = load64_le(block + (u32)8U);
          u64 hi = u;
          Lib_IntVector_Intrinsics_vec512 f0 = Lib_IntVector_Intrinsics_vec512_load64(lo);
          Lib_IntVector_Intrinsics_vec512 f1 = Lib_IntVector_Intrinsics_vec512_load64(hi);
          Lib_IntVector_Intrinsics_vec512
          f010 =
            Lib_IntVector_Intrinsics_vec512_and(f0,
              Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
          Lib_IntVector_Intrinsics_vec512
          f110 =
            Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(f0,
                (u32)26U),
              Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
          Lib_IntVector_Intrinsics_vec512
          f20 =
            Lib_IntVector_Intrinsics_vec512_or(Lib_IntVector_Intrinsics_vec512_shift_right64(f0,
                (u32)52U),
              Lib_IntVector_Intrinsics_vec512_shift_left64(Lib_IntVector_Intrinsics_vec512_and(f1,
                  Lib_IntVector_Intrinsics_vec512_load64((u64)0x3fffU)),
                (u32)12U));
          Lib_IntVector_Intrinsics_vec512
          f30 =
            Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(f1,
                (u32)14U),
              Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
          Lib_IntVector_Intrinsics_vec512
          f40 = Lib_IntVector_Intrinsics_vec512_shift_right64(f1, (u32)40U);
          Lib_IntVector_Intrinsics_vec512 f01 = f010;
          Lib_IntVector_Intrinsics_vec512 f111 = f110;
          Lib_IntVector_Intrinsics_vec512 f2 = f20;
          Lib_IntVector_Intrinsics_vec512 f3 = f30;
          Lib_IntVector_Intrinsics_vec512 f41 = f40;
          e[0U] = f01;
          e[1U] = f111;
          e[2U] = f2;
          e[3U] = f3;
          e[4U] = f41;
          {
            u64 b = (u64)0x1000000U;
            Lib_IntVector_Intrinsics_vec512 mask = Lib_IntVector_Intrinsics_vec512_load64(b);
            Lib_IntVector_Intrinsics_vec512 f4 = e[4U];
            e[4U] = Lib_IntVector_Intrinsics_vec512_or(f4, mask);
            {
              Lib_IntVector_Intrinsics_vec512 *r = pre;
              Lib_IntVector_Intrinsics_vec512 *r5 = pre + (u32)5U;
              Lib_IntVector_Intrinsics_vec512 r0 = r[0U];
              Lib_IntVector_Intrinsics_vec512 r1 = r[1U];
              Lib_IntVector_Intrinsics_vec512 r2 = r[2U];
              Lib_IntVector_Intrinsics_vec512 r3 = r[3U];
              Lib_IntVector_Intrinsics_vec512 r4 = r[4U];
              Lib_IntVector_Intrinsics_vec512 r51 = r5[1U];
              Lib_IntVector_Intrinsics_vec512 r52 = r5[2U];
              Lib_IntVector_Intrinsics_vec512 r53 = r5[3U];
              Lib_IntVector_Intrinsics_vec512 r54 = r5[4U];
              Lib_IntVector_Intrinsics_vec512 f10 = e[0U];
              Lib_IntVector_Intrinsics_vec512 f11 = e[1U];
              Lib_IntVector_Intrinsics_vec512 f12 = e[2U];
              Lib_IntVector_Intrinsics_vec512 f13 = e[3U];
              Lib_IntVector_Intrinsics_vec512 f14 = e[4U];
              Lib_IntVector_Intrinsics_vec512 a0 = acc[0U];
              Lib_IntVector_Intrinsics_vec512 a1 = acc[1U];
              Lib_IntVector_Intrinsics_vec512 a2 = acc[2U];
              Lib_IntVector_Intrinsics_vec512 a3 = acc[3U];
              Lib_IntVector_Intrinsics_vec512 a4 = acc[4U];
              Lib_IntVector_Intrinsics_vec512 a01 = Lib_IntVector_Intrinsics_vec512_add64(a0, f10);
              Lib_IntVector_Intrinsics_vec512 a11 = Lib_IntVector_Intrinsics_vec512_add64(a1, f11);
              Lib_IntVector_Intrinsics_vec512 a21 = Lib_IntVector_Intrinsics_vec512_add64(a2, f12);
              Lib_IntVector_Intrinsics_vec512 a31 = Lib_IntVector_Intrinsics_vec512_add64(a3, f13);
              Lib_IntVector_Intrinsics_vec512 a41 = Lib_IntVector_Intrinsics_vec512_add64(a4, f14);
              Lib_IntVector_Intrinsics_vec512 a02 = Lib_IntVector_Intrinsics_vec512_mul64(r0, a01);
              Lib_IntVector_Intrinsics_vec512 a12 = Lib_IntVector_Intrinsics_vec512_mul64(r1, a01);
              Lib_IntVector_Intrinsics_vec512 a22 = Lib_IntVector_Intrinsics_vec512_mul64(r2, a01);
              Lib_IntVector_Intrinsics_vec512 a32 = Lib_IntVector_Intrinsics_vec512_mul64(r3, a01);
              Lib_IntVector_Intrinsics_vec512 a42 = Lib_IntVector_Intrinsics_vec512_mul64(r4, a01);
              Lib_IntVector_Intrinsics_vec512
              a03 =
                Lib_IntVector_Intrinsics_vec512_add64(a02,
                  Lib_IntVector_Intrinsics_vec512_mul64(r54, a11));
              Lib_IntVector_Intrinsics_vec512
              a13 =
                Lib_IntVector_Intrinsics_vec512_add64(a12,
                  Lib_IntVector_Intrinsics_vec512_mul64(r0, a11));
              Lib_IntVector_Intrinsics_vec512
              a23 =
                Lib_IntVector_Intrinsics_vec512_add64(a22,
                  Lib_IntVector_Intrinsics_vec512_mul64(r1, a11));
              Lib_IntVector_Intrinsics_vec512
              a33 =
                Lib_IntVector_Intrinsics_vec512_add64(a32,
                  Lib_IntVector_Intrinsics_vec512_mul64(r2, a11));
              Lib_IntVector_Intrinsics_vec512
              a43 =
                Lib_IntVector_Intrinsics_vec512_add64(a42,
                  Lib_IntVector_Intrinsics_vec512_mul64(r3, a11));
              Lib_IntVector_Intrinsics_vec512
              a04 =
                Lib_IntVector_Intrinsics_vec512_add64(a03,
                  Lib_IntVector_Intrinsics_vec512_mul64(r53, a21));
              Lib_IntVector_Intrinsics_vec512
              a14 =
                Lib_IntVector_Intrinsics_vec512_add64(a13,
                  Lib_IntVector_Intrinsics_vec512_mul64(r54, a21));
              Lib_IntVector_Intrinsics_vec512
              a24 =
                Lib_IntVector_Intrinsics_vec512_add64(a23,
                  Lib_IntVector_Intrinsics_vec512_mul64(r0, a21));
              Lib_IntVector_Intrinsics_vec512
              a34 =
                Lib_IntVector_Intrinsics_vec512_add64(a33,
                  Lib_IntVector_Intrinsics_vec512_mul64(r1, a21));
              Lib_IntVector_Intrinsics_vec512
              a44 =
                Lib_IntVector_Intrinsics_vec512_add64(a43,
                  Lib_IntVector_Intrinsics_vec512_mul64(r2, a21));
              Lib_IntVector_Intrinsics_vec512
              a05 =
                Lib_IntVector_Intrinsics_vec512_add64(a04,
                  Lib_IntVector_Intrinsics_vec512_mul64(r52, a31));
              Lib_IntVector_Intrinsics_vec512
              a15 =
                Lib_IntVector_Intrinsics_vec512_add64(a14,
                  Lib_IntVector_Intrinsics_vec512_mul64(r53, a31));
              Lib_IntVector_Intrinsics_vec512
              a25 =
                Lib_IntVector_Intrinsics_vec512_add64(a24,
                  Lib_IntVector_Intrinsics_vec512_mul64(r54, a31));
              Lib_IntVector_Intrinsics_vec512
              a35 =
                Lib_IntVector_Intrinsics_vec512_add64(a34,
                  Lib_IntVector_Intrinsics_vec512_mul64(r0, a31));
              Lib_IntVector_Intrinsics_vec512
              a45 =
                Lib_IntVector_Intrinsics_vec512_add64(a44,
                  Lib_IntVector_Intrinsics_vec512_mul64(r1, a31));
              Lib_IntVector_Intrinsics_vec512
              a06 =
                Lib_IntVector_Intrinsics_vec512_add64(a05,
                  Lib_IntVector_Intrinsics_vec512_mul64(r51, a41));
              Lib_IntVector_Intrinsics_vec512
              a16 =
                Lib_IntVector_Intrinsics_vec512_add64(a15,
                  Lib_IntVector_Intrinsics_vec512_mul64(r52, a41));
              Lib_IntVector_Intrinsics_vec512
              a26 =
                Lib_IntVector_Intrinsics_vec512_add64(a25,
                  Lib_IntVector_Intrinsics_vec512_mul64(r53, a41));
              Lib_IntVector_Intrinsics_vec512
              a36 =
                Lib_IntVector_Intrinsics_vec512_add64(a35,
                  Lib_IntVector_Intrinsics_vec512_mul64(r54, a41));
              Lib_IntVector_Intrinsics_vec512
              a46 =
                Lib_IntVector_Intrinsics_vec512_add64(a45,
                  Lib_IntVector_Intrinsics_vec512_mul64(r0, a41));
              Lib_IntVector_Intrinsics_vec512 t01 = a06;
              Lib_IntVector_Intrinsics_vec512 t11 = a16;
              Lib_IntVector_Intrinsics_vec512 t2 = a26;
              Lib_IntVector_Intrinsics_vec512 t3 = a36;
              Lib_IntVector_Intrinsics_vec512 t4 = a46;
              Lib_IntVector_Intrinsics_vec512
              mask26 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
              Lib_IntVector_Intrinsics_vec512
              z0 = Lib_IntVector_Intrinsics_vec512_shift_right64(t01, (u32)26U);
              Lib_IntVector_Intrinsics_vec512
              z1 = Lib_IntVector_Intrinsics_vec512_shift_right64(t3, (u32)26U);
              Lib_IntVector_Intrinsics_vec512 x0 = Lib_IntVector_Intrinsics_vec512_and(t01, mask26);
              Lib_IntVector_Intrinsics_vec512 x3 = Lib_IntVector_Intrinsics_vec512_and(t3, mask26);
              Lib_IntVector_Intrinsics_vec512 x1 = Lib_IntVector_Intrinsics_vec512_add64(t11, z0);
              Lib_IntVector_Intrinsics_vec512 x4 = Lib_IntVector_Intrinsics_vec512_add64(t4, z1);
              Lib_IntVector_Intrinsics_vec512
              z01 = Lib_IntVector_Intrinsics_vec512_shift_right64(x1, (u32)26U);
              Lib_IntVector_Intrinsics_vec512
              z11 = Lib_IntVector_Intrinsics_vec512_shift_right64(x4, (u32)26U);
              Lib_IntVector_Intrinsics_vec512
              t = Lib_IntVector_Intrinsics_vec512_shift_left64(z11, (u32)2U);
              Lib_IntVector_Intrinsics_vec512 z12 = Lib_IntVector_Intrinsics_vec512_add64(z11, t);
              Lib_IntVector_Intrinsics_vec512 x11 = Lib_IntVector_Intrinsics_vec512_and(x1, mask26);
              Lib_IntVector_Intrinsics_vec512 x41 = Lib_IntVector_Intrinsics_vec512_and(x4, mask26);
              Lib_IntVector_Intrinsics_vec512 x2 = Lib_IntVector_Intrinsics_vec512_add64(t2, z01);
              Lib_IntVector_Intrinsics_vec512 x01 = Lib_IntVector_Intrinsics_vec512_add64(x0, z12);
              Lib_IntVector_Intrinsics_vec512
              z02 = Lib_IntVector_Intrinsics_vec512_shift_right64(x2, (u32)26U);
              Lib_IntVector_Intrinsics_vec512
              z13 = Lib_IntVector_Intrinsics_vec512_shift_right64(x01, (u32)26U);
              Lib_IntVector_Intrinsics_vec512 x21 = Lib_IntVector_Intrinsics_vec512_and(x2, mask26);
              Lib_IntVector_Intrinsics_vec512
              x02 = Lib_IntVector_Intrinsics_vec512_and(x01, mask26);
              Lib_IntVector_Intrinsics_vec512 x31 = Lib_IntVector_Intrinsics_vec512_add64(x3, z02);
              Lib_IntVector_Intrinsics_vec512 x12 = Lib_IntVector_Intrinsics_vec512_add64(x11, z13);
              Lib_IntVector_Intrinsics_vec512
              z03 = Lib_IntVector_Intrinsics_vec512_shift_right64(x31, (u32)26U);
              Lib_IntVector_Intrinsics_vec512
              x32 = Lib_IntVector_Intrinsics_vec512_and(x31, mask26);
              Lib_IntVector_Intrinsics_vec512 x42 = Lib_IntVector_Intrinsics_vec512_add64(x41, z03);
              Lib_IntVector_Intrinsics_vec512 o0 = x02;
              Lib_IntVector_Intrinsics_vec512 o1 = x12;
              Lib_IntVector_Intrinsics_vec512 o2 = x21;
              Lib_IntVector_Intrinsics_vec512 o3 = x32;
              Lib_IntVector_Intrinsics_vec512 o4 = x42;
              acc[0U] = o0;
              acc[1U] = o1;
              acc[2U] = o2;
              acc[3U] = o3;
              acc[4U] = o4;
            }
          }
        }
      }
    }
  }
  if (rem > (u32)0U)
  {
    u8 *last = t10 + nb0 * (u32)16U;
    KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec512), (u32)5U);
    {
      Lib_IntVector_Intrinsics_vec512 e[5U];
      {
        u32 _i;
        for (_i = 0U; _i < (u32)5U; ++_i)
          e[_i] = Lib_IntVector_Intrinsics_vec512_zero;
      }
      {
        u8 tmp[16U] = { 0U };
        u64 u0;
        u64 lo;
        u64 u;
        u64 hi;
        Lib_IntVector_Intrinsics_vec512 f0;
        Lib_IntVector_Intrinsics_vec512 f1;
        Lib_IntVector_Intrinsics_vec512 f010;
        Lib_IntVector_Intrinsics_vec512 f110;
        Lib_IntVector_Intrinsics_vec512 f20;
        Lib_IntVector_Intrinsics_vec512 f30;
        Lib_IntVector_Intrinsics_vec512 f40;
        Lib_IntVector_Intrinsics_vec512 f01;
        Lib_IntVector_Intrinsics_vec512 f111;
        Lib_IntVector_Intrinsics_vec512 f2;
        Lib_IntVector_Intrinsics_vec512 f3;
        Lib_IntVector_Intrinsics_vec512 f4;
        u64 b;
        Lib_IntVector_Intrinsics_vec512 mask;
        Lib_IntVector_Intrinsics_vec512 fi;
        Lib_IntVector_Intrinsics_vec512 *r;
        Lib_IntVector_Intrinsics_vec512 *r5;
        Lib_IntVector_Intrinsics_vec512 r0;
        Lib_IntVector_Intrinsics_vec512 r1;
        Lib_IntVector_Intrinsics_vec512 r2;
        Lib_IntVector_Intrinsics_vec512 r3;
        Lib_IntVector_Intrinsics_vec512 r4;
        Lib_IntVector_Intrinsics_vec512 r51;
        Lib_IntVector_Intrinsics_vec512 r52;
        Lib_IntVector_Intrinsics_vec512 r53;
        Lib_IntVector_Intrinsics_vec512 r54;
        Lib_IntVector_Intrinsics_vec512 f10;
        Lib_IntVector_Intrinsics_vec512 f11;
        Lib_IntVector_Intrinsics_vec512 f12;
        Lib_IntVector_Intrinsics_vec512 f13;
        Lib_IntVector_Intrinsics_vec512 f14;
        Lib_IntVector_Intrinsics_vec512 a0;
        Lib_IntVector_Intrinsics_vec512 a1;
        Lib_IntVector_Intrinsics_vec512 a2;
        Lib_IntVector_Intrinsics_vec512 a3;
        Lib_IntVector_Intrinsics_vec512 a4;
        Lib_IntVector_Intrinsics_vec512 a01;
        Lib_IntVector_Intrinsics_vec512 a11;
        Lib_IntVector_Intrinsics_vec512 a21;
        Lib_IntVector_Intrinsics_vec512 a31;
        Lib_IntVector_Intrinsics_vec512 a41;
        Lib_IntVector_Intrinsics_vec512 a02;
        Lib_IntVector_Intrinsics_vec512 a12;
        Lib_IntVector_Intrinsics_vec512 a22;
        Lib_IntVector_Intrinsics_vec512 a32;
        Lib_IntVector_Intrinsics_vec512 a42;
        Lib_IntVector_Intrinsics_vec512 a03;
        Lib_IntVector_Intrinsics_vec512 a13;
        Lib_IntVector_Intrinsics_vec512 a23;
        Lib_IntVector_Intrinsics_vec512 a33;
        Lib_IntVector_Intrinsics_vec512 a43;
        Lib_IntVector_Intrinsics_vec512 a04;
        Lib_IntVector_Intrinsics_vec512 a14;
        Lib_IntVector_Intrinsics_vec512 a24;
        Lib_IntVector_Intrinsics_vec512 a34;
        Lib_IntVector_Intrinsics_vec512 a44;
        Lib_IntVector_Intrinsics_vec512 a05;
        Lib_IntVector_Intrinsics_vec512 a15;
        Lib_IntVector_Intrinsics_vec512 a25;
        Lib_IntVector_Intrinsics_vec512 a35;
        Lib_IntVector_Intrinsics_vec512 a45;
        Lib_IntVector_Intrinsics_vec512 a06;
        Lib_IntVector_Intrinsics_vec512 a16;
        Lib_IntVector_Intrinsics_vec512 a26;
        Lib_IntVector_Intrinsics_vec512 a36;
        Lib_IntVector_Intrinsics_vec512 a46;
        Lib_IntVector_Intrinsics_vec512 t01;
        Lib_IntVector_Intrinsics_vec512 t11;
        Lib_IntVector_Intrinsics_vec512 t2;
        Lib_IntVector_Intrinsics_vec512 t3;
        Lib_IntVector_Intrinsics_vec512 t4;
        Lib_IntVector_Intrinsics_vec512 mask26;
        Lib_IntVector_Intrinsics_vec512 z0;
        Lib_IntVector_Intrinsics_vec512 z1;
        Lib_IntVector_Intrinsics_vec512 x0;
        Lib_IntVector_Intrinsics_vec512 x3;
        Lib_IntVector_Intrinsics_vec512 x1;
        Lib_IntVector_Intrinsics_vec512 x4;
        Lib_IntVector_Intrinsics_vec512 z01;
        Lib_IntVector_Intrinsics_vec512 z11;
        Lib_IntVector_Intrinsics_vec512 t;
        Lib_IntVector_Intrinsics_vec512 z12;
        Lib_IntVector_Intrinsics_vec512 x11;
        Lib_IntVector_Intrinsics_vec512 x41;
        Lib_IntVector_Intrinsics_vec512 x2;
        Lib_IntVector_Intrinsics_vec512 x01;
        Lib_IntVector_Intrinsics_vec512 z02;
        Lib_IntVector_Intrinsics_vec512 z13;
        Lib_IntVector_Intrinsics_vec512 x21;
        Lib_IntVector_Intrinsics_vec512 x02;
        Lib_IntVector_Intrinsics_vec512 x31;
        Lib_IntVector_Intrinsics_vec512 x12;
        Lib_IntVector_Intrinsics_vec512 z03;
        Lib_IntVector_Intrinsics_vec512 x32;
        Lib_IntVector_Intrinsics_vec512 x42;
        Lib_IntVector_Intrinsics_vec512 o0;
        Lib_IntVector_Intrinsics_vec512 o1;
        Lib_IntVector_Intrinsics_vec512 o2;
        Lib_IntVector_Intrinsics_vec512 o3;
        Lib_IntVector_Intrinsics_vec512 o4;
        memcpy(tmp, last, rem * sizeof (last[0U]));
        u0 = load64_le(tmp);
        lo = u0;
        u = load64_le(tmp + (u32)8U);
        hi = u;
        f0 = Lib_IntVector_Intrinsics_vec512_load64(lo);
        f1 = Lib_IntVector_Intrinsics_vec512_load64(hi);
        f010 =
          Lib_IntVector_Intrinsics_vec512_and(f0,
            Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
        f110 =
          Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(f0,
              (u32)26U),
            Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
        f20 =
          Lib_IntVector_Intrinsics_vec512_or(Lib_IntVector_Intrinsics_vec512_shift_right64(f0,
              (u32)52U),
            Lib_IntVector_Intrinsics_vec512_shift_left64(Lib_IntVector_Intrinsics_vec512_and(f1,
                Lib_IntVector_Intrinsics_vec512_load64((u64)0x3fffU)),
              (u32)12U));
        f30 =
          Lib_IntVector_Intrinsics_vec512_and(Lib_IntVector_Intrinsics_vec512_shift_right64(f1,
              (u32)14U),
            Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
        f40 = Lib_IntVector_Intrinsics_vec512_shift_right64(f1, (u32)40U);
        f01 = f010;
        f111 = f110;
        f2 = f20;
        f3 = f30;
        f4 = f40;
        e[0U] = f01;
        e[1U] = f111;
        e[2U] = f2;
        e[3U] = f3;
        e[4U] = f4;
        b = (u64)1U << rem * (u32)8U % (u32)26U;
        mask = Lib_IntVector_Intrinsics_vec512_load64(b);
        fi = e[rem * (u32)8U / (u32)26U];
        e[rem * (u32)8U / (u32)26U] = Lib_IntVector_Intrinsics_vec512_or(fi, mask);
        r = pre;
        r5 = pre + (u32)5U;
        r0 = r[0U];
        r1 = r[1U];
        r2 = r[2U];
        r3 = r[3U];
        r4 = r[4U];
        r51 = r5[1U];
        r52 = r5[2U];
        r53 = r5[3U];
        r54 = r5[4U];
        f10 = e[0U];
        f11 = e[1U];
        f12 = e[2U];
        f13 = e[3U];
        f14 = e[4U];
        a0 = acc[0U];
        a1 = acc[1U];
        a2 = acc[2U];
        a3 = acc[3U];
        a4 = acc[4U];
        a01 = Lib_IntVector_Intrinsics_vec512_add64(a0, f10);
        a11 = Lib_IntVector_Intrinsics_vec512_add64(a1, f11);
        a21 = Lib_IntVector_Intrinsics_vec512_add64(a2, f12);
        a31 = Lib_IntVector_Intrinsics_vec512_add64(a3, f13);
        a41 = Lib_IntVector_Intrinsics_vec512_add64(a4, f14);
        a02 = Lib_IntVector_Intrinsics_vec512_mul64(r0, a01);
        a12 = Lib_IntVector_Intrinsics_vec512_mul64(r1, a01);
        a22 = Lib_IntVector_Intrinsics_vec512_mul64(r2, a01);
        a32 = Lib_IntVector_Intrinsics_vec512_mul64(r3, a01);
        a42 = Lib_IntVector_Intrinsics_vec512_mul64(r4, a01);
        a03 =
          Lib_IntVector_Intrinsics_vec512_add64(a02,
            Lib_IntVector_Intrinsics_vec512_mul64(r54, a11));
        a13 =
          Lib_IntVector_Intrinsics_vec512_add64(a12,
            Lib_IntVector_Intrinsics_vec512_mul64(r0, a11));
        a23 =
          Lib_IntVector_Intrinsics_vec512_add64(a22,
            Lib_IntVector_Intrinsics_vec512_mul64(r1, a11));
        a33 =
          Lib_IntVector_Intrinsics_vec512_add64(a32,
            Lib_IntVector_Intrinsics_vec512_mul64(r2, a11));
        a43 =
          Lib_IntVector_Intrinsics_vec512_add64(a42,
            Lib_IntVector_Intrinsics_vec512_mul64(r3, a11));
        a04 =
          Lib_IntVector_Intrinsics_vec512_add64(a03,
            Lib_IntVector_Intrinsics_vec512_mul64(r53, a21));
        a14 =
          Lib_IntVector_Intrinsics_vec512_add64(a13,
            Lib_IntVector_Intrinsics_vec512_mul64(r54, a21));
        a24 =
          Lib_IntVector_Intrinsics_vec512_add64(a23,
            Lib_IntVector_Intrinsics_vec512_mul64(r0, a21));
        a34 =
          Lib_IntVector_Intrinsics_vec512_add64(a33,
            Lib_IntVector_Intrinsics_vec512_mul64(r1, a21));
        a44 =
          Lib_IntVector_Intrinsics_vec512_add64(a43,
            Lib_IntVector_Intrinsics_vec512_mul64(r2, a21));
        a05 =
          Lib_IntVector_Intrinsics_vec512_add64(a04,
            Lib_IntVector_Intrinsics_vec512_mul64(r52, a31));
        a15 =
          Lib_IntVector_Intrinsics_vec512_add64(a14,
            Lib_IntVector_Intrinsics_vec512_mul64(r53, a31));
        a25 =
          Lib_IntVector_Intrinsics_vec512_add64(a24,
            Lib_IntVector_Intrinsics_vec512_mul64(r54, a31));
        a35 =
          Lib_IntVector_Intrinsics_vec512_add64(a34,
            Lib_IntVector_Intrinsics_vec512_mul64(r0, a31));
        a45 =
          Lib_IntVector_Intrinsics_vec512_add64(a44,
            Lib_IntVector_Intrinsics_vec512_mul64(r1, a31));
        a06 =
          Lib_IntVector_Intrinsics_vec512_add64(a05,
            Lib_IntVector_Intrinsics_vec512_mul64(r51, a41));
        a16 =
          Lib_IntVector_Intrinsics_vec512_add64(a15,
            Lib_IntVector_Intrinsics_vec512_mul64(r52, a41));
        a26 =
          Lib_IntVector_Intrinsics_vec512_add64(a25,
            Lib_IntVector_Intrinsics_vec512_mul64(r53, a41));
        a36 =
          Lib_IntVector_Intrinsics_vec512_add64(a35,
            Lib_IntVector_Intrinsics_vec512_mul64(r54, a41));
        a46 =
          Lib_IntVector_Intrinsics_vec512_add64(a45,
            Lib_IntVector_Intrinsics_vec512_mul64(r0, a41));
        t01 = a06;
        t11 = a16;
        t2 = a26;
        t3 = a36;
        t4 = a46;
        mask26 = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
        z0 = Lib_IntVector_Intrinsics_vec512_shift_right64(t01, (u32)26U);
        z1 = Lib_IntVector_Intrinsics_vec512_shift_right64(t3, (u32)26U);
        x0 = Lib_IntVector_Intrinsics_vec512_and(t01, mask26);
        x3 = Lib_IntVector_Intrinsics_vec512_and(t3, mask26);
        x1 = Lib_IntVector_Intrinsics_vec512_add64(t11, z0);
        x4 = Lib_IntVector_Intrinsics_vec512_add64(t4, z1);
        z01 = Lib_IntVector_Intrinsics_vec512_shift_right64(x1, (u32)26U);
        z11 = Lib_IntVector_Intrinsics_vec512_shift_right64(x4, (u32)26U);
        t = Lib_IntVector_Intrinsics_vec512_shift_left64(z11, (u32)2U);
        z12 = Lib_IntVector_Intrinsics_vec512_add64(z11, t);
        x11 = Lib_IntVector_Intrinsics_vec512_and(x1, mask26);
        x41 = Lib_IntVector_Intrinsics_vec512_and(x4, mask26);
        x2 = Lib_IntVector_Intrinsics_vec512_add64(t2, z01);
        x01 = Lib_IntVector_Intrinsics_vec512_add64(x0, z12);
        z02 = Lib_IntVector_Intrinsics_vec512_shift_right64(x2, (u32)26U);
        z13 = Lib_IntVector_Intrinsics_vec512_shift_right64(x01, (u32)26U);
        x21 = Lib_IntVector_Intrinsics_vec512_and(x2, mask26);
        x02 = Lib_IntVector_Intrinsics_vec512_and(x01, mask26);
        x31 = Lib_IntVector_Intrinsics_vec512_add64(x3, z02);
        x12 = Lib_IntVector_Intrinsics_vec512_add64(x11, z13);
        z03 = Lib_IntVector_Intrinsics_vec512_shift_right64(x31, (u32)26U);
        x32 = Lib_IntVector_Intrinsics_vec512_and(x31, mask26);
        x42 = Lib_IntVector_Intrinsics_vec512_add64(x41, z03);
        o0 = x02;
        o1 = x12;
        o2 = x21;
        o3 = x32;
        o4 = x42;
        acc[0U] = o0;
        acc[1U] = o1;
        acc[2U] = o2;
        acc[3U] = o3;
        acc[4U] = o4;
        return;
      }
    }
  }
}

void Hacl_Poly1305_512_poly1305_finish(u8 *tag, u8 *key, Lib_IntVector_Intrinsics_vec512 *ctx)
{
  Lib_IntVector_Intrinsics_vec512 *acc = ctx;
  u8 *ks = key + (u32)16U;
  Lib_IntVector_Intrinsics_vec512 f00 = acc[0U];
  Lib_IntVector_Intrinsics_vec512 f13 = acc[1U];
  Lib_IntVector_Intrinsics_vec512 f23 = acc[2U];
  Lib_IntVector_Intrinsics_vec512 f33 = acc[3U];
  Lib_IntVector_Intrinsics_vec512 f40 = acc[4U];
  Lib_IntVector_Intrinsics_vec512
  l0 = Lib_IntVector_Intrinsics_vec512_add64(f00, Lib_IntVector_Intrinsics_vec512_zero);
  Lib_IntVector_Intrinsics_vec512
  tmp00 =
    Lib_IntVector_Intrinsics_vec512_and(l0,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c00 = Lib_IntVector_Intrinsics_vec512_shift_right64(l0, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l1 = Lib_IntVector_Intrinsics_vec512_add64(f13, c00);
  Lib_IntVector_Intrinsics_vec512
  tmp10 =
    Lib_IntVector_Intrinsics_vec512_and(l1,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c10 = Lib_IntVector_Intrinsics_vec512_shift_right64(l1, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l2 = Lib_IntVector_Intrinsics_vec512_add64(f23, c10);
  Lib_IntVector_Intrinsics_vec512
  tmp20 =
    Lib_IntVector_Intrinsics_vec512_and(l2,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c20 = Lib_IntVector_Intrinsics_vec512_shift_right64(l2, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l3 = Lib_IntVector_Intrinsics_vec512_add64(f33, c20);
  Lib_IntVector_Intrinsics_vec512
  tmp30 =
    Lib_IntVector_Intrinsics_vec512_and(l3,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c30 = Lib_IntVector_Intrinsics_vec512_shift_right64(l3, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l4 = Lib_IntVector_Intrinsics_vec512_add64(f40, c30);
  Lib_IntVector_Intrinsics_vec512
  tmp40 =
    Lib_IntVector_Intrinsics_vec512_and(l4,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c40 = Lib_IntVector_Intrinsics_vec512_shift_right64(l4, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  f010 =
    Lib_IntVector_Intrinsics_vec512_add64(tmp00,
      Lib_IntVector_Intrinsics_vec512_smul64(c40, (u32)(u64)5U));
  Lib_IntVector_Intrinsics_vec512 f110 = tmp10;
  Lib_IntVector_Intrinsics_vec512 f210 = tmp20;
  Lib_IntVector_Intrinsics_vec512 f310 = tmp30;
  Lib_IntVector_Intrinsics_vec512 f410 = tmp40;
  Lib_IntVector_Intrinsics_vec512
  l = Lib_IntVector_Intrinsics_vec512_add64(f010, Lib_IntVector_Intrinsics_vec512_zero);
  Lib_IntVector_Intrinsics_vec512
  tmp0 =
    Lib_IntVector_Intrinsics_vec512_and(l,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c0 = Lib_IntVector_Intrinsics_vec512_shift_right64(l, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l5 = Lib_IntVector_Intrinsics_vec512_add64(f110, c0);
  Lib_IntVector_Intrinsics_vec512
  tmp1 =
    Lib_IntVector_Intrinsics_vec512_and(l5,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c1 = Lib_IntVector_Intrinsics_vec512_shift_right64(l5, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l6 = Lib_IntVector_Intrinsics_vec512_add64(f210, c1);
  Lib_IntVector_Intrinsics_vec512
  tmp2 =
    Lib_IntVector_Intrinsics_vec512_and(l6,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c2 = Lib_IntVector_Intrinsics_vec512_shift_right64(l6, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l7 = Lib_IntVector_Intrinsics_vec512_add64(f310, c2);
  Lib_IntVector_Intrinsics_vec512
  tmp3 =
    Lib_IntVector_Intrinsics_vec512_and(l7,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c3 = Lib_IntVector_Intrinsics_vec512_shift_right64(l7, (u32)26U);
  Lib_IntVector_Intrinsics_vec512 l8 = Lib_IntVector_Intrinsics_vec512_add64(f410, c3);
  Lib_IntVector_Intrinsics_vec512
  tmp4 =
    Lib_IntVector_Intrinsics_vec512_and(l8,
      Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec512
  c4 = Lib_IntVector_Intrinsics_vec512_shift_right64(l8, (u32)26U);
  Lib_IntVector_Intrinsics_vec512
  f02 =
    Lib_IntVector_Intrinsics_vec512_add64(tmp0,
      Lib_IntVector_Intrinsics_vec512_smul64(c4, (u32)(u64)5U));
  Lib_IntVector_Intrinsics_vec512 f12 = tmp1;
  Lib_IntVector_Intrinsics_vec512 f22 = tmp2;
  Lib_IntVector_Intrinsics_vec512 f32 = tmp3;
  Lib_IntVector_Intrinsics_vec512 f42 = tmp4;
  Lib_IntVector_Intrinsics_vec512 mh = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3ffffffU);
  Lib_IntVector_Intrinsics_vec512 ml = Lib_IntVector_Intrinsics_vec512_load64((u64)0x3fffffbU);
  Lib_IntVector_Intrinsics_vec512 mask = Lib_IntVector_Intrinsics_vec512_eq64(f42, mh);
  Lib_IntVector_Intrinsics_vec512
  mask1 =
    Lib_IntVector_Intrinsics_vec512_and(mask,
      Lib_IntVector_Intrinsics_vec512_eq64(f32, mh));
  Lib_IntVector_Intrinsics_vec512
  mask2 =
    Lib_IntVector_Intrinsics_vec512_and(mask1,
      Lib_IntVector_Intrinsics_vec512_eq64(f22, mh));
  Lib_IntVector_Intrinsics_vec512
  mask3 =
    Lib_IntVector_Intrinsics_vec512_and(mask2,
      Lib_IntVector_Intrinsics_vec512_eq64(f12, mh));
  Lib_IntVector_Intrinsics_vec512
  mask4 =
    Lib_IntVector_Intrinsics_vec512_and(mask3,
      Lib_IntVector_Intrinsics_vec512_lognot(Lib_IntVector_Intrinsics_vec512_gt64(ml, f02)));
  Lib_IntVector_Intrinsics_vec512 ph = Lib_IntVector_Intrinsics_vec512_and(mask4, mh);
  Lib_IntVector_Intrinsics_vec512 pl = Lib_IntVector_Intrinsics_vec512_and(mask4, ml);
  Lib_IntVector_Intrinsics_vec512 o0 = Lib_IntVector_Intrinsics_vec512_sub64(f02, pl);
  Lib_IntVector_Intrinsics_vec512 o1 = Lib_IntVector_Intrinsics_vec512_sub64(f12, ph);
  Lib_IntVector_Intrinsics_vec512 o2 = Lib_IntVector_Intrinsics_vec512_sub64(f22, ph);
  Lib_IntVector_Intrinsics_vec512 o3 = Lib_IntVector_Intrinsics_vec512_sub64(f32, ph);
  Lib_IntVector_Intrinsics_vec512 o4 = Lib_IntVector_Intrinsics_vec512_sub64(f42, ph);
  Lib_IntVector_Intrinsics_vec512 f011 = o0;
  Lib_IntVector_Intrinsics_vec512 f111 = o1;
  Lib_IntVector_Intrinsics_vec512 f211 = o2;
  Lib_IntVector_Intrinsics_vec512 f311 = o3;
  Lib_IntVector_Intrinsics_vec512 f411 = o4;
  Lib_IntVector_Intrinsics_vec512 f0;
  Lib_IntVector_Intrinsics_vec512 f1;
  Lib_IntVector_Intrinsics_vec512 f2;
  Lib_IntVector_Intrinsics_vec512 f3;
  Lib_IntVector_Intrinsics_vec512 f4;
  u64 f01;
  u64 f112;
  u64 f212;
  u64 f312;
  u64 f41;
  u64 lo0;
  u64 hi0;
  u64 f10;
  u64 f11;
  u64 u0;
  u64 lo;
  u64 u;
  u64 hi;
  u64 f20;
  u64 f21;
  u64 r0;
  u64 r1;
  u64 c;
  u64 r11;
  u64 f30;
  u64 f31;
  acc[0U] = f011;
  acc[1U] = f111;
  acc[2U] = f211;
  acc[3U] = f311;
  acc[4U] = f411;
  f0 = acc[0U];
  f1 = acc[1U];
  f2 = acc[2U];
  f3 = acc[3U];
  f4 = acc[4U];
  f01 = Lib_IntVector_Intrinsics_vec512_extract64(f0, (u32)0U);
  f112 = Lib_IntVector_Intrinsics_vec512_extract64(f1, (u32)0U);
  f212 = Lib_IntVector_Intrinsics_vec512_extract64(f2, (u32)0U);
  f312 = Lib_IntVector_Intrinsics_vec512_extract64(f3, (u32)0U);
  f41 = Lib_IntVector_Intrinsics_vec512_extract64(f4, (u32)0U);
  lo0 = (f01 | f112 << (u32)26U) | f212 << (u32)52U;
  hi0 = (f212 >> (u32)12U | f312 << (u32)14U) | f41 << (u32)40U;
  f10 = lo0;
  f11 = hi0;
  u0 = load64_le(ks);
  lo = u0;
  u = load64_le(ks + (u32)8U);
  hi = u;
  f20 = lo;
  f21 = hi;
  r0 = f10 + f20;
  r1 = f11 + f21;
  c = (r0 ^ ((r0 ^ f20) | ((r0 - f20) ^ f20))) >> (u32)63U;
  r11 = r1 + c;
  f30 = r0;
  f31 = r11;
  store64_le(tag, f30);
  store64_le(tag + (u32)8U, f31);
}

void Hacl_Poly1305_512_poly1305_mac(u8 *tag, u32 len, u8 *text, u8 *key)
{
  KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec512), (u32)25U);
  {
    Lib_IntVector_Intrinsics_vec512 ctx[25U];
    {
      u32 _i;
      for (_i = 0U; _i < (u32)25U; ++_i)
        ctx[_i] = Lib_IntVector_Intrinsics_vec512_zero;
    }
    Hacl_Poly1305_512_poly1305_init(ctx, key);
    Hacl_Poly1305_512_poly1305_update(ctx, len, text);
    Hacl_Poly1305_512_poly1305_finish(tag, key, ctx);
  }
}
