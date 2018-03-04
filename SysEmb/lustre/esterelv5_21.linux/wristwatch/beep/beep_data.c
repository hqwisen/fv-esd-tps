/*
\SubSection{The \COMBINEBEEPS\ function}

\noindent
This is file ``beep.c''.

*/

#include "beep.h"

char* _BEEP_TYPE_to_text (b)
BEEP_TYPE b; {
   static char res[2];
   sprintf(res, "%1d", b);
   return res;
}


BEEP_TYPE COMBINE_BEEPS (beep1,beep2)
BEEP_TYPE beep1, beep2; {
   return (beep1+beep2);
}
