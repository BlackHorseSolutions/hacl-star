module Hacl.Impl.Generic.DH

open FStar.HyperStack
open FStar.HyperStack.All

open Lib.Buffer
open Lib.IntTypes

module DH = Spec.Agile.DH
module S = Spec.Agile.HPKE

#set-options "--z3rlimit 20 --max_fuel 0 --initial_ifuel 1 --max_ifuel 1"

unfold noextract
let nsize_key (a:DH.algorithm) =
  match a with
  | DH.DH_Curve25519 -> 32ul
  | DH.DH_P256 -> 32ul

unfold noextract
let nsize_public (a:DH.algorithm) =
  match a with
  | DH.DH_Curve25519 -> 32ul
  | DH.DH_P256 -> 64ul

inline_for_extraction noextract
let dh_st (a:DH.algorithm) =
     o:lbuffer uint8 (nsize_public a)
  -> k:lbuffer uint8 (nsize_key a)
  -> i:lbuffer uint8 (nsize_public a)
  -> ST UInt32.t
     (requires fun h0 ->
       (a = DH.DH_Curve25519 ==> Vale.X64.CPU_Features_s.(adx_enabled /\ bmi2_enabled)) /\
       live h0 o /\ live h0 k /\ live h0 i /\
       disjoint o i /\ disjoint o k)
     (ensures fun h0 result h1 -> modifies (loc o) h0 h1 /\ (
       let output = DH.dh a (as_seq h0 k) (as_seq h0 i) in
       match result with
       | 0ul -> Some? output /\ as_seq h1 o == Some?.v output // DH succeeded
       | 1ul -> None? output
       | _ -> False))

inline_for_extraction noextract
let secret_to_public_st (a: DH.algorithm) =
    o:lbuffer uint8 (nsize_public a)
  -> i:lbuffer uint8 (nsize_key a)
  -> Stack UInt32.t
    (requires fun h0 ->
      (a = DH.DH_Curve25519 ==> Vale.X64.CPU_Features_s.(adx_enabled /\ bmi2_enabled)) /\
      live h0 o /\ live h0 i /\ disjoint o i)
    (ensures  fun h0 result h1 -> modifies (loc o) h0 h1 /\
      (let output = DH.secret_to_public a (as_seq h0 i) in
      match result with
      | 0ul -> Some? output /\ as_seq h1 o == Some?.v output
      | 1ul -> None? output
      | _ -> False))

[@ Meta.Attribute.specialize]
assume val dh: #a:S.ciphersuite -> dh_st (S.curve_of_cs a)

[@ Meta.Attribute.specialize]
assume val secret_to_public: #a:S.ciphersuite -> secret_to_public_st (S.curve_of_cs a)

(** Instantiations for Curve25519 **)

inline_for_extraction noextract
let secret_to_public_c51 : secret_to_public_st (DH.DH_Curve25519) = admit()
//  Hacl.Curve25519_51.secret_to_public
inline_for_extraction noextract
let dh_c51 : dh_st (DH.DH_Curve25519) = admit()
//  Hacl.Curve25519_51.scalarmult

inline_for_extraction noextract
let secret_to_public_c64 : secret_to_public_st (DH.DH_Curve25519) = admit()
//  Hacl.Curve25519_64.secret_to_public
inline_for_extraction noextract
let dh_c64 : dh_st (DH.DH_Curve25519) = admit()
//  Hacl.Curve25519_64.scalarmult