node pid
  (P: real;
  I: real;
  D: real;
  e: real)
returns
  (u: real);

var
  V11_first: bool;
  V12_pass: bool;

let
  u = (if V12_pass then (((P * (pre e)) + (D * ((pre e) - (pre (pre e))))) + (I 
  * e)) else 0.000000);
  V11_first = (true -> false);
  V12_pass = (false -> (if (pre V11_first) then false else true));
tel

