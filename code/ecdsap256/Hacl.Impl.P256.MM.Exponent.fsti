module Hacl.Impl.P256.MM.Exponent

open FStar.HyperStack.All
open FStar.HyperStack
module ST = FStar.HyperStack.ST

open Lib.IntTypes
open Lib.Buffer

open Hacl.Spec.P256.MontgomeryMultiplication
open Hacl.Spec.P256.Definition
open Spec.P256


val square_root: #c: curve -> a: felem c -> result: felem c -> Stack unit 
  (requires fun h -> live h a /\ live h result /\ as_nat c h a < prime256)
  (ensures fun h0 _ h1 -> modifies (loc a |+| loc result) h0 h1 /\
    as_nat c h1 result < prime256 /\
    fromDomain_ #c (as_nat c h1 result) = sq_root_spec #c (fromDomain_ #c (as_nat c h0 a)) /\
    fromDomain_ #c (as_nat c h1 result) = pow (fromDomain_ #c (as_nat c h0 a)) ((getPrime c+ 1) / 4) % getPrime c
  )
