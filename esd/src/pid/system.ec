node system
  (r: real;
  P: real;
  I: real;
  D: real;
  w: real)
returns
  (y: real);

var
  V22_e: real;
  V23_et: real;
  V24_u: real;
  V74_first: bool;
  V75_pass: bool;
  V76_sum_errors: real;

let
  y = (20.000000 -> (((0.700000 * (pre y)) + (0.500000 * V24_u)) - w));
  V22_e = (0.000000 -> (pre V23_et));
  V23_et = (r - y);
  V24_u = (if V75_pass then (((P * V22_e) + (D * (V22_e - (pre V22_e)))) + (I * 
  V76_sum_errors)) else 0.000000);
  V74_first = (true -> false);
  V75_pass = (false -> (if (pre V74_first) then false else true));
  V76_sum_errors = (V22_e -> ((pre V76_sum_errors) + V22_e));
tel

