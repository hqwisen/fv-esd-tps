node EDGE
  (X: bool)
returns
  (state: bool);

let
  state = (false -> (X and (not (pre X))));
tel

