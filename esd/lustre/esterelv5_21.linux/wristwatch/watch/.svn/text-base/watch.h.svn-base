/*
\headline={\hss\nineit C code for the \WATCH\ module\hss}
\Section{File ``WATCH.h'': types and defined
constants for the \WATCH\ module}
*/

#define WATCH_LOADED

/*
\SubSection{The \WATCHTIMETYPE\ type and its copy function}
*/

typedef struct {int day_in_week;
                int month;
                int day;
                int hours;
                int minutes;
                int seconds;
                int mode12h;} WATCH_TIME_TYPE;

/*
\noindent
Copying is simply done by assignment :
*/

#define _WATCH_TIME_TYPE(X,Y) (*(X)=(Y))

/*
\noindent
Equality is never used and needs not be declared.
*/

/*
\SubSection{ The \WATCHTIMEPOSITION\ type and its copy function}
*/

typedef int WATCH_TIME_POSITION;

/*
\noindent
Copying is simply done by assignment :
*/

#define _WATCH_TIME_POSITION(X,Y) (*(X)=(Y))

/*
\noindent
Equality is never used.
*/

/*
\SubSection{The \INITIALWATCHTIMEPOSITION\ constant}
*/

#define INITIAL_WATCH_TIME_POSITION 0

/*
\SubSection{The \WATCHBEEPVALUE\ constant}

\noindent
This constant is defined only if the \LOADBEEP\ flag is \#defined
*/

#ifdef LOAD_BEEP

#ifndef BEEP_LOADED
#include "beep.h"
#endif

#define WATCH_BEEP_VALUE TWO_BEEPS

#endif


