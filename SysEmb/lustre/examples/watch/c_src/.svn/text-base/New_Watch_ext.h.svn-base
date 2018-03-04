
/*
BASIC TYPES
*/

#define _EC2C_PREDEF_TYPES
typedef int _boolean;
typedef int _integer;
typedef char* _string;
typedef double _real;
typedef double _double;
typedef float _float;
#define _false 0
#define _true 1

/*****************************************************
EXTERNAL TYPES
------------------------------------------------------
NB: no need of _eq_XX nor _ne_xXX functions
NB: _assign_XX and _cond_XX can be inlined
******************************************************/

/*----------------------------------------------------
string TYPE
-----------------------------------------------------*/
typedef char* string;
#define _cond_string(A,B,C) (A?B:C)
#define _assign_string(X,Y) (*(X)=(Y))

/*----------------------------------------------------
MAIN DISPLAY TYPE
-----------------------------------------------------*/
typedef struct {
   char hours[4]; /* should be 3, but bugs in some C compilers */
   char minutes[4];
   char seconds [4];
   char timemode[4];
} MAIN_DISPLAY_TYPE;

#define _cond_MAIN_DISPLAY_TYPE(A,B,C) (A?B:C)
#define _assign_MAIN_DISPLAY_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
MINI DISPLAY TYPE
-----------------------------------------------------*/

typedef struct {
   char fst[3];
   char sep[2];
   char snd[3];
} MINI_DISPLAY_TYPE;
#define _cond_MINI_DISPLAY_TYPE(A,B,C) (A?B:C)
#define _assign_MINI_DISPLAY_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
STATUS TYPE
-----------------------------------------------------*/

typedef struct {
   _boolean alarm_set;
   _boolean chime_set;
   _boolean stopwatch_running;
   _boolean stopwatch_lapping;
} STATUS_TYPE;
#define _cond_STATUS_TYPE(A,B,C) (A?B:C)
#define _assign_STATUS_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
DISPLAY POSITION TYPE
-----------------------------------------------------*/

typedef int DISPLAY_POSITION;
#define _cond_DISPLAY_POSITION(A,B,C) (A?B:C)
#define _assign_DISPLAY_POSITION(X,Y) (*(X)=(Y))

/*----------------------------------------------------
TYPE OF BUTTON LABELS
-----------------------------------------------------*/

typedef struct {
   char ul_lab[14];
   char ll_lab[14];
   char ur_lab[4];
   char lr_lab[12];
} LABELS_TYPE;
#define _cond_LABELS_TYPE(A,B,C) (A?B:C)
#define _assign_LABELS_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
DISPLAY TYPE
-----------------------------------------------------*/

typedef struct{
   MAIN_DISPLAY_TYPE _main;
   MINI_DISPLAY_TYPE mini;
   string alpha;
   STATUS_TYPE status;
   DISPLAY_POSITION enhanced;
   LABELS_TYPE lab;
} DISPLAY_TYPE;
#define _cond_DISPLAY_TYPE(A,B,C) (A?B:C)
#define _assign_DISPLAY_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
WATCH_TIME_TYPE
-----------------------------------------------------*/
typedef struct {int day_in_week;
   int month;
   int day;
   int hours;
   int minutes;
   int seconds;
   int mode12h;
} WATCH_TIME_TYPE;
#define _cond_WATCH_TIME_TYPE(A,B,C) (A?B:C)
#define _assign_WATCH_TIME_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
WATCH_TIME_POSITION
-----------------------------------------------------*/

typedef int WATCH_TIME_POSITION;
#define _cond_WATCH_TIME_POSITION(A,B,C) (A?B:C)
#define _assign_WATCH_TIME_POSITION(X,Y) (*(X)=(Y))

/*----------------------------------------------------
ALARM_TIME_TYPE
-----------------------------------------------------*/

typedef struct {
   int hours;
   int minutes;
   int mode12h;
} ALARM_TIME_TYPE;
#define _cond_ALARM_TIME_TYPE(A,B,C) (A?B:C)
#define _assign_ALARM_TIME_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
ALARM_TIME_POSITION
-----------------------------------------------------*/

typedef int ALARM_TIME_POSITION;
#define _cond_ALARM_TIME_POSITION(A,B,C) (A?B:C)
#define _assign_ALARM_TIME_POSITION(X,Y) (*(X)=(Y))

/*----------------------------------------------------
STOPWATCH_TIME_TYPE
-----------------------------------------------------*/
typedef struct {
   int hours;
   int minutes;
   int seconds;
   int hsec;
} STOPWATCH_TIME_TYPE;
#define _cond_STOPWATCH_TIME_TYPE(A,B,C) (A?B:C)
#define _assign_STOPWATCH_TIME_TYPE(X,Y) (*(X)=(Y))

/*****************************************************
CONSTANTS DECLARATIONS
******************************************************/
#define NULL_POSITION (-1)
#define stringST ("ST")
#define stringAL ("AL")
#define ALARM_DURATION (30)
extern ALARM_TIME_TYPE INITIAL_ALARM_TIME;
#define INITIAL_ALARM_POSITION (0)
extern WATCH_TIME_TYPE INITIAL_WATCH_TIME;
#define INITIAL_WATCH_POSITION (0)
extern STOPWATCH_TIME_TYPE INITIAL_STOPWATCH_TIME;


/*****************************************************
OUTPUT FUNCTION DECLARATIONS
******************************************************/
extern void New_Watch_O_display(void*, DISPLAY_TYPE);
extern void New_Watch_O_beep(void*, _integer);

/*****************************************************
EXTERNAL FUNCTION DECLARATIONS
******************************************************/

extern void LABELS(
   LABELS_TYPE*, _boolean, _boolean, _boolean, _boolean, _boolean
);
extern void WATCH_TO_DISPLAY_POS(DISPLAY_POSITION*, WATCH_TIME_POSITION);
extern void ALARM_TO_DISPLAY_POS(DISPLAY_POSITION*, ALARM_TIME_POSITION);
extern void STATUS(
   STATUS_TYPE*, _boolean, _boolean, _boolean, _boolean
);
extern void MAKE_DISPLAY(
   DISPLAY_TYPE*, MAIN_DISPLAY_TYPE, MINI_DISPLAY_TYPE,
   string, STATUS_TYPE, DISPLAY_POSITION, LABELS_TYPE
);
extern void WATCH_TIME_TO_MAIN_DISPLAY(MAIN_DISPLAY_TYPE*, WATCH_TIME_TYPE);
extern void STOPWATCH_TIME_TO_MAIN_DISPLAY(
   MAIN_DISPLAY_TYPE*, STOPWATCH_TIME_TYPE
);
extern void ALARM_TIME_TO_MAIN_DISPLAY(MAIN_DISPLAY_TYPE*, ALARM_TIME_TYPE);
extern void WATCH_DATE_TO_MINI_DISPLAY(MINI_DISPLAY_TYPE*, WATCH_TIME_TYPE);
extern void WATCH_TIME_TO_MINI_DISPLAY(MINI_DISPLAY_TYPE*, WATCH_TIME_TYPE);
extern void WATCH_DAY_TO_ALPHA_DISPLAY(string*, WATCH_TIME_TYPE);
extern void TOGGLE_24H_IN_ALARM_MODE(ALARM_TIME_TYPE*, ALARM_TIME_TYPE);
extern void SET_ALARM_TIME(
   ALARM_TIME_TYPE*, ALARM_TIME_TYPE, ALARM_TIME_POSITION
);
extern void NEXT_ALARM_TIME_POSITION(
   ALARM_TIME_POSITION*, ALARM_TIME_POSITION
);
extern void COMPARE_WATCH_ALARM_TIME(
   _boolean*, WATCH_TIME_TYPE, ALARM_TIME_TYPE
);
extern void INCREMENT_WATCH_TIME(WATCH_TIME_TYPE*, WATCH_TIME_TYPE);
extern void TOGGLE_24H_IN_WATCH_MODE(WATCH_TIME_TYPE*, WATCH_TIME_TYPE);
extern void CONFIRM_TIME(WATCH_TIME_TYPE*, WATCH_TIME_TYPE);
extern void INCREMENT_WATCH_TIME_IN_SET_MODE(
   WATCH_TIME_TYPE*, WATCH_TIME_TYPE , WATCH_TIME_POSITION
);
extern void NEXT_WATCH_TIME_POSITION(
   WATCH_TIME_POSITION*, WATCH_TIME_POSITION
);
extern void SET_WATCH_TIME(
   WATCH_TIME_TYPE*, WATCH_TIME_TYPE, WATCH_TIME_POSITION
);
extern void IS_O_CLOCK(_boolean*, WATCH_TIME_TYPE);
extern void INCREMENT_STOPWATCH_TIME(
   STOPWATCH_TIME_TYPE*, STOPWATCH_TIME_TYPE
);
extern void IS_ZERO_MOD_10_MN(_boolean*, STOPWATCH_TIME_TYPE);
