/*
\headline={\hss\nineit C code for the \STOPWATCH\ module\hss}
\Section{File ``stopwatch.h'' : types and defined constants for
the \STOPWATCH\ module}
*/

#define STOPWATCH_LOADED

/*
\SubSection{The \STOPWATCHTIMETYPE\ type and its copy function}
*/

typedef struct {int hundredths;
                int seconds;
                int minutes;} STOPWATCH_TIME_TYPE;

/*
\noindent
Copying is simply done by assignment :
*/

#define _STOPWATCH_TIME_TYPE(X,Y) (*(X)=(Y))

/*
\noindent
Equality is never used.
*/

/*
\SubSection{The \STOPWATCHBEEPVALUE\ constant}

\noindent
This constant is defined only if the \LOADBEEP\ flag is \#defined
*/

#ifdef LOAD_BEEP

#ifndef BEEP_LOADED
#include "beep.h"
#endif

#define STOPWATCH_BEEP_VALUE ONE_BEEP

#endif
/*
\SubSection{Time handling constants}
*/

#ifdef SIMUL

#define HUNDREDTHS_PER_INCREMENT 1
#define HUNDREDTHS_PER_SECOND 2
#define SECONDS_PER_MINUTE 2
#define MINUTES_PER_HOUR 2
#define MINUTES_TO_BEEP 1

#else

extern int HUNDREDTHS_PER_INCREMENT;
#define HUNDREDTHS_PER_SECOND 100
#define SECONDS_PER_MINUTE 60
#define MINUTES_PER_HOUR 60
#define MINUTES_TO_BEEP 1 /* should be 10, but set to 1 for demos */

#endif


