/*
\vfill\eject
\Section{File ``display.c'' : constants, functions and procedures
of the \DISPLAY\ module}

\noindent
Files to include:
*/

#ifndef DISPLAY_LOADED
#include "display.h"
#endif

/*
\SubSection{Constants}
*/

#ifdef SIMUL
#define PM_VALUE 1
#else
#define PM_VALUE 12
#endif

/*
\SubSection{Printing functions for simulation}
*/

#ifdef SIMUL

static char* clear_blanks (s) 
char *s; {
   char *res;
   for (res=s; (*res)==' '; res++);
   return res;
}

char* _MAIN_DISPLAY_TYPE_to_text (md)
MAIN_DISPLAY_TYPE md; {
   static char res[14];
   sprintf (res, "%s:%s%s%s", 
                 clear_blanks(md.hours),
                 clear_blanks(md.minutes),
                 clear_blanks(md.seconds),
                 md.timemode);
   return res;
}

char* _MINI_DISPLAY_TYPE_to_text (md)
MINI_DISPLAY_TYPE md; {
   static char res[6];
   sprintf (res, "%s%s%s", 
                 clear_blanks(md.fst),
                 clear_blanks(md.sep), 
                 clear_blanks(md.snd));
   return res;
}

static char *position_name [7] = {"seconds", "hours", "10 minutes",
                                  "minutes", "month", "day", "day name"};

char* _DISPLAY_POSITION_to_text (dp)
DISPLAY_POSITION dp; {
   static char res[11];
   sprintf (res, "%s", position_name[dp]);
   return res;
}

#endif

/*
\SubSection{The \WATCHTIMETOMAINDISPLAY\ function}
*/

MAIN_DISPLAY_TYPE WATCH_TIME_TO_MAIN_DISPLAY (wt)
WATCH_TIME_TYPE wt; {
   static MAIN_DISPLAY_TYPE maindt;
   static hours;
   if (wt.mode12h) {
     hours = wt.hours % PM_VALUE;
     if (!hours) hours=PM_VALUE;
   }
   else {
     hours=wt.hours;
   }
   sprintf(maindt.hours,"%2d",hours);
   sprintf(maindt.minutes,"%02d",wt.minutes);
#ifdef SIMUL
   sprintf(maindt.seconds,":%02d",wt.seconds);
#else
   sprintf(maindt.seconds,"%02d",wt.seconds);
#endif
   if (wt.mode12h) {
      if (wt.hours>(PM_VALUE-1))
#ifdef SIMUL
        strcpy(maindt.timemode," PM");
        else strcpy(maindt.timemode,"");
   } else strcpy(maindt.timemode," 24H");
#else
        strcpy(maindt.timemode,"PM ");
        else strcpy(maindt.timemode,"   ");
   } else strcpy(maindt.timemode,"24H");
#endif
   return(maindt);
}
                           
/*
\SubSection{The \WATCHTIMETOMINIDISPLAY\ function}
*/

MINI_DISPLAY_TYPE WATCH_TIME_TO_MINI_DISPLAY (wt)
WATCH_TIME_TYPE wt; {
   static MINI_DISPLAY_TYPE minidt;
   sprintf(minidt.fst,"%2d",wt.hours);
   strcpy(minidt.sep,":");
   sprintf(minidt.snd,"%02d",wt.minutes);
   return(minidt);
}

/*
\SubSection{The \WATCHDATETOMINIDISPLAY\ function}
*/

MINI_DISPLAY_TYPE WATCH_DATE_TO_MINI_DISPLAY (wt)
WATCH_TIME_TYPE wt; {
   static MINI_DISPLAY_TYPE minidt;
   sprintf(minidt.fst,"%2d",wt.month+1);
   strcpy(minidt.sep,"-");
   sprintf(minidt.snd,"%2d",wt.day);
   return(minidt);
}


/*
\SubSection{The \WATCHDAYTOALPHABETICDISPLAY\ function}
*/

static char *day_names [7] = {"SU","MO","TU","WE","TH","FR","SA"};

char * WATCH_DAY_TO_ALPHABETIC_DISPLAY (wt)
WATCH_TIME_TYPE wt; {
   return(day_names[wt.day_in_week]);
}

/*
\vfill\eject
\SubSection{The \WATCHDISPLAYPOSITION\ function}

\noindent
The two positions are identical:
*/

DISPLAY_POSITION WATCH_DISPLAY_POSITION (wtp)
WATCH_TIME_POSITION wtp; {
   return(wtp);
}

/*
\SubSection{The \STOPWATCHTIMETOMAINDISPLAY\ function}
*/

MAIN_DISPLAY_TYPE STOPWATCH_TIME_TO_MAIN_DISPLAY (st)
STOPWATCH_TIME_TYPE st; {
   static MAIN_DISPLAY_TYPE maindt;
   sprintf(maindt.hours,"%2d",st.minutes);
   sprintf(maindt.minutes,"%02d",st.seconds);
#ifdef SIMUL
   sprintf(maindt.seconds,":%02d",st.hundredths);
   strcpy(maindt.timemode,"");
#else
   sprintf(maindt.seconds,"%02d",st.hundredths);
   strcpy(maindt.timemode,"   ");
#endif
   return(maindt);
}

/*
\SubSection{The \ALARMTIMETOMAINDISPLAY\ function}
*/

MAIN_DISPLAY_TYPE ALARM_TIME_TO_MAIN_DISPLAY (at)
ALARM_TIME_TYPE at; {
   static MAIN_DISPLAY_TYPE maindt;
   static hours;
   if (at.mode12h) {
     hours = at.hours % PM_VALUE;
     if (!hours) hours = PM_VALUE;
   }
   else {
     hours=at.hours;
   }
   sprintf(maindt.hours,"%2d",hours);
   sprintf(maindt.minutes,"%02d",at.minutes);
   sprintf(maindt.seconds,"  ");
   if (at.mode12h) {
     if (at.hours > PM_VALUE-1)
#ifdef SIMUL
        strcpy(maindt.timemode," PM");
        else strcpy(maindt.timemode,"");
     } else strcpy(maindt.timemode," 24H");
#else
        strcpy(maindt.timemode,"PM ");
        else strcpy(maindt.timemode,"   ");
     } else strcpy(maindt.timemode,"24H");
#endif
   return(maindt);
}

/*
\SubSection{The \ALARMDISPLAYPOSITION\ function}
*/

ALARM_DISPLAY_POSITION (atp)
ALARM_TIME_POSITION atp; {
   return(atp+1);
}

