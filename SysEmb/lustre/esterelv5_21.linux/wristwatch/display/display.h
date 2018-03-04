/*
\headline={\hss\nineit C code for the \DISPLAY\ module\hss}
\Section{File ``display.h'' : types and defined
constants for the \DISPLAY\ module}
*/

#define DISPLAY_LOADED

/*
\SubSection{The \MAINDISPLAYTYPE\ type and its copy function}
*/

#ifdef SIMUL

typedef struct {char hours[3]; 
                char minutes[3];
                char seconds [4]; /* for the trailing : */
                char timemode[5];} MAIN_DISPLAY_TYPE;

#else

typedef struct {char hours[3]; 
                char minutes[3];
                char seconds [3];
                char timemode[4];} MAIN_DISPLAY_TYPE;

#endif

/*
\noindent
Copying is simply done by assignment :
*/

#define _MAIN_DISPLAY_TYPE(X,Y) (*(X)=(Y))

/*
\noindent
No equality function is needed.
*/

/*
\SubSection{The \MINIDISPLAYTYPE\ type and its copy function}
*/

typedef struct {char fst[3];
                char sep[2];
                char snd[3];} MINI_DISPLAY_TYPE;

/*
\noindent
Copying is simply done by assignment :
*/

#define _MINI_DISPLAY_TYPE(X,Y) (*(X)=(Y))

/*
\noindent
No equality function is needed.
*/

/*
\SubSection{ the \DISPLAYPOSITION\ type and its copy function}
*/

typedef int DISPLAY_POSITION;

/*
\noindent
Copying is simply done by assignment :
*/

#define _DISPLAY_POSITION(X,Y) (*(X)=(Y))

/*
\noindent
No equality function is needed.
*/

/*
\SubSection{Loading auxiliary definition files}
*/

#ifndef WATCH_LOADED
#include "watch.h"
#endif

#ifndef STOPWATCH_LOADED
#include "stopwatch.h"
#endif

#ifndef ALARM_LOADED
#include "alarm.h"
#endif
