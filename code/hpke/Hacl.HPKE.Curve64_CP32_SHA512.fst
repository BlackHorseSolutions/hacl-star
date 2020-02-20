module Hacl.HPKE.Curve64_CP32_SHA512

open Hacl.Meta.HPKE

module IDH = Hacl.Impl.Generic.DH
module IHK = Hacl.Impl.Generic.HKDF
module IHash = Hacl.Impl.Generic.Hash
module IAEAD = Hacl.Impl.Instantiate.AEAD

friend Hacl.Meta.HPKE

let setupBaseI = hpke_setupBaseI_higher #cs IHK.hkdf_expand512 IHK.hkdf_extract512 IHash.hash_sha512 IDH.secret_to_public_c64 IDH.dh_c64

let setupBaseR = hpke_setupBaseR_higher #cs IHK.hkdf_expand512 IHK.hkdf_extract512 IHash.hash_sha512 IDH.dh_c64 IDH.secret_to_public_c64

let sealBase = hpke_sealBase_higher #cs setupBaseI IAEAD.aead_encrypt_cp32

let openBase = hpke_openBase_higher #cs setupBaseR IAEAD.aead_decrypt_cp32