node XOR
  (a: bool;
  b: bool)
returns
  (Xor: bool);

let
  Xor = (if a then (not b) else b);
tel

