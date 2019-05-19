module Vale.Wrapper.X64.Fadd

open Vale.Interop.Base
module DV = LowStar.BufferView.Down

#set-options "--z3rlimit 50"

let add1 out f1 f2 =
  DV.length_eq (get_downview f1);
  DV.length_eq (get_downview out);
  let x, _ = Vale.Stdcalls.X64.Fadd.add1 out f1 f2 () in
  x

#push-options "--max_fuel 0 --max_ifuel 0 --z3rlimit 100"

let fadd out f1 f2 =
  DV.length_eq (get_downview out);
  DV.length_eq (get_downview f1);
  DV.length_eq (get_downview f2);
  let x, _ = Vale.Stdcalls.X64.Fadd.fadd_ out f1 f2 () in
  ()

#pop-options
