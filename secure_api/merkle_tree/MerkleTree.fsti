module MerkleTree

module HST = FStar.HyperStack.ST
module HH = FStar.Monotonic.HyperHeap

module B = LowStar.Buffer
module CB = LowStar.ConstBuffer

module U32 = FStar.UInt32
module U64 = FStar.UInt64

module MTS = MerkleTree.Spec
module MTNL = MerkleTree.Low
module MTNLHF = MerkleTree.Low.Hashfunctions
module MTNLE = MerkleTree.EverCrypt
module MTNLD = MerkleTree.Low.Datastructures
module MTNLS = MerkleTree.Low.Serialization


let hash_size_t = MTNLD.hash_size_t
let offset_t = MTNL.offset_t
let index_t = MTNL.index_t
let hash #hash_size = MTNLD.hash #hash_size

let path #hash_size = MTNL.path #hash_size
let path_p #hash_size = MTNL.path_p #hash_size
let const_path_p #hash_size = MTNL.const_path_p #hash_size

let merkle_tree = MTNL.merkle_tree
let mt_p = MTNL.mt_p
let const_mt_p = MTNL.const_mt_p

let pf = fun _ -> False
let pt = fun _ _ _ -> True

[@ (Comment "  Constructors and destructors for hashes") "c_inline"]
let mt_init_hash (hash_size:hash_size_t) (r:HST.erid): HST.ST (hash #hash_size) pf pt = MTNLHF.init_hash hash_size r
[@"c_inline"] let mt_free_hash (hash_size:hash_size_t) (h:hash #hash_size): HST.ST unit pf pt = MTNLHF.free_hash hash_size h


[@ (Comment "  Constructors and destructors for paths") "c_inline"]
let mt_init_path (#hash_size:hash_size_t) (mtr:HH.rid) (r:HST.erid): HST.ST (path_p #hash_size) pf pt = MTNL.init_path #hash_size mtr r
[@"c_inline"] let mt_clear_path (hash_size:hash_size_t) (mtr:HH.rid) (p:path_p #hash_size): HST.ST unit pf pt = MTNL.clear_path hash_size mtr p
[@"c_inline"] let mt_free_path (hash_size:hash_size_t) (p:path_p #hash_size): HST.ST unit pf pt = MTNL.free_path hash_size p

[@ (Comment "  Construction with custom hash functions

  @param[in]  hash_size Hash size (in bytes)
  @param[in]  i         The initial hash") "c_inline"]
let mt_create_custom
  (hash_size:hash_size_t)
  (hash_spec:Ghost.erased (MTS.hash_fun_t #(U32.v hash_size)))
  (r:HST.erid)
  (i:hash #hash_size)
  (hash_fun:MTNLHF.hash_fun_t #hash_size #hash_spec)
: HST.ST mt_p pf pt
= MTNL.mt_create_custom hash_size hash_spec r i hash_fun


[@ (Comment "    Destruction

  @param[in]  mt  The Merkle tree") "c_inline"]
let mt_free (mt:mt_p): HST.ST unit pf pt = MTNL.mt_free mt


[@ (Comment "  Insertion

  @param[in]  mt  The Merkle tree
  @param[in]  v   The tree does not take ownership of the hash, it makes a copy of its content.

 Note: The content of the hash will be overwritten with an arbitrary value.") "c_inline"]
let mt_insert (hash_size:Ghost.erased hash_size_t) (mt:mt_p) (v:hash #hash_size): HST.ST unit pf pt = MTNL.mt_insert hash_size mt v

[@ (Comment "  Precondition predicate for mt_insert") "c_inline"]
let mt_insert_pre (#hash_size:Ghost.erased hash_size_t) (mt:const_mt_p) (v:hash #hash_size): HST.ST bool  pf pt = MTNL.mt_insert_pre #hash_size mt v


[@ (Comment "  Getting the Merkle root

  @param[in]  mt   The Merkle tree
  @param[out] root The Merkle root") "c_inline"]
let mt_get_root (#hash_size:Ghost.erased hash_size_t) (mt:const_mt_p) (root:hash #hash_size): HST.ST unit pf pt = MTNL.mt_get_root #hash_size mt root

[@ (Comment "  Precondition predicate for mt_get_root") "c_inline"]
let mt_get_root_pre (#hash_size:Ghost.erased hash_size_t) (mt:const_mt_p) (root:hash #hash_size): HST.ST bool pf pt = MTNL.mt_get_root_pre #hash_size mt root


[@ (Comment "  Getting a Merkle path

  @param[in]  mt   The Merkle tree
  @param[in]  idx  The index of the target hash
  @param[out] path A resulting Merkle path that contains the leaf hash.
  @param[out] root The Merkle root

  return The number of elements in the tree

  Notes:
  - The resulting path contains pointers to hashes in the tree, not copies of
    the hash values.
  - idx must be within the currently held indices in the tree (past the
    last flush index).") "c_inline"]
let mt_get_path
  (#hash_size:Ghost.erased hash_size_t)
  (mt:const_mt_p)
  (idx:offset_t)
  (path:path_p #hash_size)
  (root:hash #hash_size)
: HST.ST index_t pf pt
= MTNL.mt_get_path #hash_size mt idx path root

[@ (Comment "  Precondition predicate for mt_get_path") "c_inline"]
let mt_get_path_pre
  (#hash_size:Ghost.erased hash_size_t)
  (mt:const_mt_p)
  (idx:offset_t)
  (path:const_path_p #hash_size)
  (root:hash #hash_size)
: HST.ST bool pf pt
= MTNL.mt_get_path_pre #hash_size mt idx path root


[@ (Comment "  Flush the Merkle tree

  @param[in]  mt   The Merkle tree") "c_inline"]
let mt_flush (mt:mt_p): HST.ST unit pf pt = MTNL.mt_flush mt

[@ (Comment "  Precondition predicate for mt_flush") "c_inline"]
let mt_flush_pre (mt:const_mt_p): HST.ST bool pf pt = MTNL.mt_flush_pre mt


[@ (Comment "  Flush the Merkle tree up to a given index

  @param[in]  mt   The Merkle tree
  @param[in]  idx  The index up to which to flush the tree") "c_inline"]
let mt_flush_to (mt:mt_p) (idx:offset_t): HST.ST unit pf pt = MTNL.mt_flush_to mt idx

[@ (Comment "  Precondition predicate for mt_flush_to")]
let mt_flush_to_pre (mt:const_mt_p) (idx:offset_t): HST.ST bool pf pt = MTNL.mt_flush_to_pre mt idx


[@ (Comment "  Retract the Merkle tree down to a given index

  @param[in]  mt   The Merkle tree
  @param[in]  idx  The index to retract the tree to

 Note: The element and idx will remain in the tree.") "c_inline"]
let mt_retract_to (mt:mt_p) (idx:offset_t): HST.ST unit pf pt = MTNL.mt_retract_to mt idx

[@ (Comment "  Precondition predicate for mt_retract_to") "c_inline"]
let mt_retract_to_pre (mt:const_mt_p) (idx:offset_t): HST.ST bool pf pt = MTNL.mt_retract_to_pre mt idx


[@ (Comment "  Client-side verification

  @param[in]  mt   The Merkle tree
  @param[in]  tgt  The index of the target hash
  @param[in]  max  The maximum index + 1 of the tree when the path was generated
  @param[in]  path The Merkle path to verify
  @param[in]  root

  return true if the verification succeeded, false otherwise

  Note: max - tgt must be less than 2^32.") "c_inline"]
let mt_verify
  (#hash_size:Ghost.erased hash_size_t)
  (#hash_spec:MTS.hash_fun_t #(U32.v hash_size))
  (mt:const_mt_p)
  (tgt:UInt64.t)
  (max:UInt64.t)
  (mtr:HH.rid)
  (path:const_path_p #hash_size)
  (root:hash #hash_size)
: HST.ST bool pf pt
= MTNL.mt_verify #hash_size #hash_spec mt tgt max mtr path root

[@ (Comment "  Precondition predicate for mt_verify") "c_inline"]
let mt_verify_pre (#hash_size:Ghost.erased hash_size_t) (mt:const_mt_p) (tgt:UInt64.t) (max:UInt64.t) (mtr:HH.rid) (path:const_path_p #hash_size) (root:hash #hash_size): HST.ST bool pf pt
= MTNL.mt_verify_pre #hash_size mt tgt max mtr path root


[@ (Comment "  Serialization size

  @param[in]  mt   The Merkle tree

  return the number of bytes required to serialize the tree") "c_inline"]
let mt_serialize_size (mt:const_mt_p): HST.ST UInt64.t pf pt = MTNLS.mt_serialize_size mt


[@ (Comment "  Merkle tree serialization

  @param[in]  mt   The Merkle tree
  @param[out] buf  The buffer to serialize the tree into
  @param[in]  len  Length of buf

  return the number of bytes written

  Note: buf must be a buffer of size mt_serialize_size(mt) or larger, but
  smaller than 2^32 (larger buffers are currently not supported).") "c_inline"]
let mt_serialize (mt:const_mt_p) (buf:MTNLS.uint8_p) (len:UInt64.t): HST.ST UInt64.t pf pt = MTNLS.mt_serialize mt buf len


[@ (Comment "  Merkle tree deserialization

  @param[in]  buf  The buffer to deserialize the tree from
  @param[in]  len  Length of buf

  return pointer to the new tree if successful, NULL otherwise

  Note: buf must point to an allocated buffer.") "c_inline"]
let mt_deserialize
  (#hash_size:hash_size_t)
  (rid:HST.erid)
  (buf:MTNLS.const_uint8_p)
  (len:UInt64.t{CB.length buf = U64.v len})
  (hash_spec:Ghost.erased(MTS.hash_fun_t #(U32.v hash_size)))
  (hash_fun:MTNLHF.hash_fun_t #hash_size #hash_spec)
: HST.ST (B.pointer_or_null merkle_tree) pf pt
= MTNLS.mt_deserialize #hash_size rid buf len hash_spec hash_fun


[@ (Comment "  Path serialization

  @param[in]  path The path
  @param[in]  mt   The Merkle tree the path belongs to
  @param[out] buf  The buffer to serialize the path into
  @param[in]  len  Length of buf

  return the number of bytes written") "c_inline"]
let mt_serialize_path
  (#hash_size:Ghost.erased hash_size_t)
  (path:const_path_p #hash_size)
  (mt:const_mt_p)
  (buf:MTNLS.uint8_p)
  (len:UInt64.t)
: HST.ST UInt64.t pf pt
= MTNLS.mt_serialize_path #hash_size path mt buf len


[@ (Comment "  Path deserialization

  @param[in]  buf  The buffer to deserialize the path from
  @param[in]  len  Length of buf

  return pointer to the new path if successful, NULL otherwise

 Note: buf must point to an allocated buffer.") "c_inline"]
let mt_deserialize_path
  (#hash_size:hash_size_t)
  (rid:HST.erid)
  (buf:MTNLS.const_uint8_p)
  (len:UInt64.t{CB.length buf = U64.v len})
: HST.ST (B.pointer_or_null (path #hash_size)) pf pt
= MTNLS.mt_deserialize_path #hash_size rid buf len

[@ (Comment "  Default hash function")]
let mt_sha256_compress: MTNLHF.hash_fun_t #32ul #(Ghost.hide MTS.sha256_compress) = MTNLE.sha256_compress
