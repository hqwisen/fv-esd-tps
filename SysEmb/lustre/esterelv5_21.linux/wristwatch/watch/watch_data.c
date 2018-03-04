/*
\vfill\eject
\Section{File ``watch_data.c'' : constants, functions and procedures of the \WATCH\
module}

\noindent
The files to include :
*/

#ifndef WATCH_LOADED
#include "watch.h"
#endif

#include <time.h>

/*
\SubSection{Time handling constants}

The time handling routines use constants that are set to their usual values
except in SIMUL mode where they are set to artificially low values
(setting the 10 minutes position becomes impossible).
*/

#ifdef SIMUL

#define SECONDS_PER_MINUTE 2
#define MINUTES_PER_10MN 2
#define MINUTES_PER_HOUR 2
#define HOURS_PER_DAY 2
#define PM_VALUE 1
#define DAYS_PER_WEEK 2
#define MONTHS_PER_YEAR 2

static short monthlength [] = {2, 2};

#else

#define SECONDS_PER_MINUTE 60
#define MINUTES_PER_10MN 10
#define MINUTES_PER_HOUR 60
#define HOURS_PER_DAY 24
#define PM_VALUE 12
#define DAYS_PER_WEEK 7
#define MONTHS_PER_YEAR 12

static short monthlength [] = {31,28,31,30,31,30,31,31,30,31,30,31};

#endif

/*
\SubSection{The printing functions for simulation}
*/

#ifdef SIMUL

static char *day_names [7] = {"SU","MO","TU","WE","TH","FR","SA"};

char* _WATCH_TIME_TYPE_to_text (wt)
WATCH_TIME_TYPE wt; {
   static char res[22];
   sprintf (res, "%s %d-%d %d:%d:%d%s",
                 day_names[wt.day_in_week],
                 wt.month+1,
                 wt.day,
                 (wt.mode12h ? ((wt.hours % PM_VALUE ==0) ?
                                    PM_VALUE :
                                    wt.hours % PM_VALUE)
                             : wt.hours),
                 wt.minutes,
                 wt.seconds,
                (wt.mode12h
                         ? ((wt.hours>=PM_VALUE) ? " PM" : " AM") 
                         : " 24H"));
   return res;
}

static char *position_name [7] = {"seconds", "hours", "10 minutes",
                                  "minutes", "month", "day", "day name"};

char* _WATCH_TIME_POSITION_to_text (wtp)
WATCH_TIME_POSITION wtp; {
   static char res[12];
   sprintf (res, "%s", position_name[wtp]);
   return res;
}

#endif

/*
\SubSection{The \INITIALWATCHTIME\ constant}

The \INITIALWATCHTIME\ constant is declared here and
initialized in the main program, using the function \GETINITIALWATCHTIME,
unless in SIMUL mode where it is initialized here.
*/

#ifdef SIMUL

WATCH_TIME_TYPE INITIAL_WATCH_TIME = 
      {0, 0, 1, PM_VALUE, 0, 0, 0};

#else

WATCH_TIME_TYPE INITIAL_WATCH_TIME;

#endif

WATCH_TIME_TYPE GET_INITIAL_WATCH_TIME () {
   WATCH_TIME_TYPE wt;
   struct tm *ptm;
   long tloc;
   time(&tloc);
   ptm=localtime(&tloc);
   wt.day_in_week = ptm->tm_wday;
   wt.month = ptm->tm_mon;
   wt.day = ptm->tm_mday;
   wt.hours = ptm->tm_hour;
   wt.minutes = ptm->tm_min;
   wt.seconds = ptm->tm_sec;
   wt.mode12h = 0;
   return(wt);
}

/*
\SubSection{The \INCREMENTWATCHTIME\ procedure}
*/

INCREMENT_WATCH_TIME (pwt)
WATCH_TIME_TYPE *pwt; {
   pwt->seconds ++;
   if (pwt->seconds == SECONDS_PER_MINUTE) {
      pwt->seconds = 0;
      pwt->minutes ++;
      if (pwt->minutes == MINUTES_PER_HOUR) {
         pwt->minutes = 0;
         pwt->hours ++;
         if (pwt->hours == HOURS_PER_DAY) {
            pwt->hours = 0;
            pwt->day ++;
            pwt->day_in_week = (pwt->day_in_week+1) % DAYS_PER_WEEK;
            if (pwt->day > monthlength[pwt->month]) {
               pwt->day = 1;
               pwt->month = (pwt->month+1) % MONTHS_PER_YEAR;
            }
         }
      }
   }
}

/*
\SubSection{The \TOGGLEVQHMODEINWATCHTIME\ procedure}
*/

TOGGLE_24H_MODE_IN_WATCH_TIME (pwt)
WATCH_TIME_TYPE *pwt; {
   pwt->mode12h = ! pwt->mode12h;
}

/*
\SubSection{The \NEXTWATCHTIMEPOSITION\ function}
*/

NEXT_WATCH_TIME_POSITION (wtp)
WATCH_TIME_POSITION wtp; {
   return((wtp+1)%7);
}

/*
\SubSection{The \SETWATCHTIME\ procedure}
*/

SET_WATCH_TIME (pwt,wtp)
WATCH_TIME_TYPE *pwt; 
WATCH_TIME_POSITION wtp; {
   switch (wtp) {
      case 0 : /* seconds */
         pwt->seconds=0;
         break;
      case 1 : /* hours */
         pwt->hours = (pwt->hours+1) % HOURS_PER_DAY;
         break;
      case 2 : /* 10 minutes */
         pwt->minutes = (pwt->minutes >= MINUTES_PER_HOUR-MINUTES_PER_10MN
                           ? pwt->minutes-(MINUTES_PER_HOUR-MINUTES_PER_10MN)
                           : pwt->minutes+MINUTES_PER_10MN);
         break;
      case 3 : /* minutes */
         pwt->minutes = (pwt->minutes % MINUTES_PER_10MN == MINUTES_PER_10MN-1
                               ? pwt->minutes-(MINUTES_PER_10MN-1)
                               : pwt->minutes+1);
         break;
      case 4 : /* month */
         pwt->month = (pwt->month+1) % MONTHS_PER_YEAR;
         break;
      case 5 : /* day */
         pwt->day = (pwt->day == monthlength[pwt->month]
                               ? 1
                               : pwt->day+1 );
         break;
      case 6 : /* day in week */
         pwt->day_in_week = (pwt->day_in_week+1) % DAYS_PER_WEEK;
         break;
   }
}

/*
\SubSection{The \INCREMENTWATCHTIMEINSETMODE\ procedure}

\noindent
The incrementation is done only up to the watch time position being currently
set.
*/

INCREMENT_WATCH_TIME_IN_SET_MODE (pwt,wtp)
WATCH_TIME_TYPE *pwt;
WATCH_TIME_POSITION wtp; {
   pwt->seconds ++;
   if (pwt->seconds == SECONDS_PER_MINUTE) {
      pwt->seconds = 0;
      if (wtp == 3) return 0; /* in set minutes mode */
      if (wtp == 2) {  /* set 10 minutes mode */
#ifdef SIMUL
         return 0;
#else
         if (pwt->minutes % 10 == 9) pwt->minutes -= 9;
         else 
         pwt->minutes ++;
         return 0;
#endif
      }
      pwt->minutes ++;
      if (pwt->minutes == MINUTES_PER_HOUR) {
         pwt->minutes = 0;
         if (wtp == 1) return 0; /* set hours mode */
         pwt->hours ++;
         if (pwt->hours == HOURS_PER_DAY) {
            pwt->hours = 0;
            if (wtp == 4 || wtp == 6) return 0; /* set day mode */
            pwt->day ++;
            pwt->day_in_week = (pwt->day_in_week+1) % DAYS_PER_WEEK;
            if (pwt->day > monthlength[pwt->month]) {
               pwt->day = 1;
               if (wtp == 5) return 0;   /* set month mode */
               pwt->month = (pwt->month+1) % MONTHS_PER_YEAR;
            }
         }
      }
   }
}

/*
\SubSection{The \WATCHBEEP\ function}
*/

WATCH_BEEP (wt, b)
WATCH_TIME_TYPE wt; {
   return ((b && (wt.seconds == 0) && (wt.minutes==0)) ?
         WATCH_BEEP_VALUE : NO_BEEP_VALUE);
}

