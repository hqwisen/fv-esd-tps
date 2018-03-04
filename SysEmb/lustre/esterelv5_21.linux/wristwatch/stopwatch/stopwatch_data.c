/*
\vfill\eject
\Section{File ``stopwatch.c'' : constants, functions and procedures
of the \STOPWATCH\ module}
*/

#ifndef STOPWATCH_LOADED
#include "stopwatch.h"
#endif

#ifndef SIMUL
int HUNDREDTHS_PER_INCREMENT = 25; /* 1/4 seconds */
#endif
/*
\SubSection{The printing functions for simulation}
*/

char* _STOPWATCH_TIME_TYPE_to_text (st)
STOPWATCH_TIME_TYPE st; {
   static char res[9];
   sprintf (res, "%d:%02d:%02d",
	    st.minutes, st.seconds, st.hundredths);
   return res;
}

/*
\SubSection{The \ZEROSTOPWATCHTIME\ constant}
*/

STOPWATCH_TIME_TYPE ZERO_STOPWATCH_TIME = {0, 0, 0};

/*
\SubSection{The \INCREMENTSTOPWATCHTIME\ procedure}
*/

INCREMENT_STOPWATCH_TIME (pst)
STOPWATCH_TIME_TYPE *pst; {
   pst->hundredths += HUNDREDTHS_PER_INCREMENT;
   if (pst->hundredths == HUNDREDTHS_PER_SECOND) {
     pst->hundredths = 0;
     pst->seconds ++;
     if (pst->seconds == SECONDS_PER_MINUTE) {
       pst->seconds = 0;
       pst->minutes ++;
       if (pst->minutes == MINUTES_PER_HOUR) 
         pst->minutes = 0;
     }
   }
}

/*
\SubSection{The \STOPWATCHBEEP\ function}
*/

BEEP_TYPE STOPWATCH_BEEP (st)
STOPWATCH_TIME_TYPE st; {
   return (((st.hundredths == 0) &&
            (st.seconds == 0) &&
            (st.minutes % MINUTES_TO_BEEP == 0))
         ? STOPWATCH_BEEP_VALUE : NO_BEEP_VALUE);
}

