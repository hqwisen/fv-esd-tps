/*
\headline={\hss\nineit C code for the \ALARM\ module\hss}
\Section{File ``alarm.h'' : types and defined
constants for the \ALARM\ module}
*/

#define ALARM_LOADED

/*
\SubSection{The \ALARMTIMETYPE\ type and its copy function}
*/

typedef struct {int hours;
                int minutes;
                int mode12h;} ALARM_TIME_TYPE;

/*
\noindent
Copying is simply done by assignment :
*/

#define _ALARM_TIME_TYPE(X,Y) (*(X)=(Y))

/*
\noindent
Equality is never used.
*/

/*
\SubSection{The \ALARMTIMEPOSITION\ type and its copy function}

\noindent
The type is just integer
*/

typedef int ALARM_TIME_POSITION;

/*
\noindent
Copying is simply done by assignment :
*/

#define _ALARM_TIME_POSITION(X,Y) (*(X)=(Y))

/*
\noindent
Equality is never used.
*/

/*
\SubSection{The \INITIALALARMTIMEPOSITION\ constant}
*/

#define INITIAL_ALARM_TIME_POSITION 0

/*
\SubSection{The \ALARMDURATION\ constant}
*/

#ifdef SIMUL

#define ALARM_DURATION 3

#else

#define ALARM_DURATION 30

#endif

/*
\SubSection{The \ALARMBEEPVALUE\ constant}

\noindent
This constant is defined only if the \LOADBEEP\ flag is \#defined.
*/

#ifdef LOAD_BEEP

#ifndef BEEP_LOADED
#include "beep.h"
#endif

#define ALARM_BEEP_VALUE FOUR_BEEPS

#endif

/*
\SubSection{Loading the WATCH.h definitions}
*/

#ifndef WATCH_LOADED

#include "watch.h"

#endif
