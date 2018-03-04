/*
\Section{File ``alarm.c'' : constants, functions, and
procedures of the \ALARM\ module}

\noindent
Files to include:
*/

#ifndef ALARM_LOADED
#include "alarm.h"
#endif

/*
\SubSection{Time handling constants}

The time handling routines use constants that are set to their usual values
except in SIMUL mode where they are set to artificially low values
(setting the 10 minutes position becomes impossible).
*/

#ifdef SIMUL

#define MINUTES_PER_HOUR 2
#define MINUTES_PER_10MN 2
#define HOURS_PER_DAY 2
#define PM_VALUE 1

#else

#define MINUTES_PER_HOUR 60
#define MINUTES_PER_10MN 10
#define HOURS_PER_DAY 24
#define PM_VALUE 12

#endif

/*
\SubSection{The printing functions for simulation}
*/

#ifdef SIMUL

char* _ALARM_TIME_TYPE_to_text (at)
ALARM_TIME_TYPE at; {
   static char res[10];
   sprintf (res, "%d:%02d%s",
                 (at.mode12h ? ((at.hours % PM_VALUE) == 0 ?
                                    PM_VALUE  :
                                    at.hours % PM_VALUE)
                             : at.hours),
                 at.minutes,
                 (at.mode12h ? (at.hours>12 ? " PM" : " AM") : " 24H"));
   return res;
}

static char *position_name [3] = {"hours", "10 minutes", "minutes"};

char* _ALARM_TIME_POSITION_to_text (atp)
ALARM_TIME_POSITION atp; {
   static char res[11];
   sprintf (res, "%s", position_name[atp]);
   return res;
}

#endif

/*
\SubSection{The \INITIALALARMTIME\ constant}

\noindent
The alarm is initially set a 00:00, \VQH\ mode:
*/

ALARM_TIME_TYPE INITIAL_ALARM_TIME = {0,0,0};

/*
\SubSection{The \TOGGLEVQHMODEINALARMTIME\ procedure}
*/

TOGGLE_24H_MODE_IN_ALARM_TIME (pat)
ALARM_TIME_TYPE* pat; {
   pat->mode12h = ! pat->mode12h;
}

/*
\SubSection{The \NEXTALARMTIMEPOSITION\ function}
*/

NEXT_ALARM_TIME_POSITION (atp) {
   return((atp+1)%3);
}

/*
\SubSection{The \SETALARMTIME\ procedure}
*/

SET_ALARM_TIME (pat,atp)
ALARM_TIME_TYPE *pat; {
   switch (atp) {
      case 0 : /* hours */
         pat->hours = (pat->hours+1) % HOURS_PER_DAY;
         break;
      case 1 : /* 10 minutes */
         pat->minutes = (pat->minutes >= MINUTES_PER_HOUR-MINUTES_PER_10MN
                           ? pat->minutes-(MINUTES_PER_HOUR-MINUTES_PER_10MN)
                           : pat->minutes+MINUTES_PER_10MN);
         break; 
      case 2 : /* minutes */
         pat->minutes = (pat->minutes %10 == MINUTES_PER_10MN-1
                               ? pat->minutes-(MINUTES_PER_10MN-1)
                               : pat->minutes+1);
         break;
   }
}

/*
\SubSection{The \COMPAREALARMTIMETOWATCHTIME\ function}
*/

COMPARE_ALARM_TIME_TO_WATCH_TIME (at,wt)
ALARM_TIME_TYPE at;
WATCH_TIME_TYPE wt; {
   return(wt.seconds==0 && at.hours==wt.hours && at.minutes==wt.minutes);
}

