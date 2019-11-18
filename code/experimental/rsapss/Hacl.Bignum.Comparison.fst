module Hacl.Bignum.Comparison

open FStar.HyperStack
open FStar.HyperStack.ST
open FStar.Mul

open Lib.IntTypes
open Lib.Buffer

open Hacl.Bignum
open Hacl.Bignum.Base

module ST = FStar.HyperStack.ST


#set-options "--z3rlimit 50 --max_fuel 0 --max_ifuel 0"

val bn_is_less_:
    aLen:size_t
  -> a:lbignum aLen
  -> bLen:size_t{v bLen <= v aLen}
  -> b:lbignum bLen
  -> i:size_t{v i <= v aLen} ->
  Stack bool
  (requires fun h -> live h a /\ live h b)
  (ensures  fun h0 _ h1 -> h0 == h1)

let rec bn_is_less_ aLen a bLen b i =
  if i >. 0ul then
    let i = i -. size 1 in
    let t1 = a.(i) in
    let t2 = bval bLen b i in
    (if not (eq_u64 t1 t2) then
      if lt_u64 t1 t2 then true else false
    else bn_is_less_ aLen a bLen b i)
  else false


val bn_is_less:
    aLen:size_t
  -> a:lbignum aLen
  -> bLen:size_t{v bLen <= v aLen}
  -> b:lbignum bLen ->
  Stack bool
  (requires fun h -> live h a /\ live h b)
  (ensures  fun h0 r h1 -> h0 == h1 /\ r == (bn_v h0 a < bn_v h0 b))

[@"c_inline"]
let bn_is_less aLen a bLen b =
  let res = bn_is_less_ aLen a bLen b aLen in
  admit();
  res
