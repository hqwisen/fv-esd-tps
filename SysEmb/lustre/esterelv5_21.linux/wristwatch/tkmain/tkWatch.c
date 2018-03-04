/*
Files to include
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef WIN32
#   include <signal.h>
#   include <sys/time.h>
#else
#   define _WIN32_WINNT 0x4000
#   include <windows.h>
#   include <winbase.h>
#   include <time.h>
#endif

#if  defined(__BUILTIN_VA_ARG_INCR) || defined(OSF1) || defined(AIX)
#   define HAS_STDARG
#endif

#include "tkWatch.h"

Tcl_Interp* watch_interp;


static Tcl_DString tcl_command;

static PrintErrorTrace (line) 
int line ;
{
    char buffer[256];
    sprintf(buffer, "*** Error (line %d) : %s\n%s\n",
	    line,
	    watch_interp->result,
	    Tcl_GetVar(watch_interp, "errorInfo", TCL_GLOBAL_ONLY));

#ifndef WIN32
    fprintf(stderr, buffer);
#else

    WishMessageBox(buffer);
#endif
    exit(1);
	    
}

#define PRINT_ERROR_AND_EXIT()  PrintErrorTrace(__LINE__)

/*
 * Defines my eval to use a DString for Tcl_Eval
 */
static int Eval TCL_VARARGS_DEF(char *,arg1)
{
    va_list argList;
    char *str;

    Tcl_DStringFree(&tcl_command);
    str = TCL_VARARGS_START(char*, arg1, argList);
    while (str != (char*)NULL) {
	Tcl_DStringAppend(&tcl_command, str, -1);
	str = va_arg(argList, char*);
    }
    va_end(argList);
    return Tcl_Eval(watch_interp, Tcl_DStringValue(&tcl_command));
}



/*----------------------------------------------------------------------
 *
 * Ouput functions
 *
 */
WRISTWATCH_O_MAIN_DISPLAY (maindt)
MAIN_DISPLAY_TYPE maindt; {

    if (Eval("WRISTWATCH_O_MAIN_DISPLAY",
	     " {",
	     maindt.hours,
	     "} {",
	     maindt.minutes,
	     "} {",
	     maindt.seconds,
	     "} {",
	     maindt.timemode,
	     "}",
	     (char*)NULL) != TCL_OK) {
	PRINT_ERROR_AND_EXIT();
    }
}


WRISTWATCH_O_MINI_DISPLAY (minidt)
MINI_DISPLAY_TYPE (minidt); {
    if (Eval("WRISTWATCH_O_MINI_DISPLAY",
	     " {",
	     minidt.fst,
	     "} {",
	     minidt.sep,
	     "} {",
	     minidt.snd,
	     "}",
	     (char*)NULL) != TCL_OK) {
	PRINT_ERROR_AND_EXIT();
    }
}


WRISTWATCH_O_ALPHABETIC_DISPLAY (s)
char *s; {
    if (Eval("WRISTWATCH_O_ALPHABETIC_DISPLAY",
	     " {",
	     s,
	     "}",
	     (char*)NULL) != TCL_OK) {
	PRINT_ERROR_AND_EXIT();
    }
}


static char* PosToWidget[] = {
    "main,sec_or_cent",
    "main,hour_or_mn",
    "main,10mn_or_sec",
    "main,mn_or_sec",
    "mini,hour_or_day",
    "mini,mn_or_month",
    "alphabetic"
};

WRISTWATCH_O_START_ENHANCING (dp)
DISPLAY_POSITION dp; 
{
    if (Eval("WRISTWATCH_O_START_ENHANCING ",
	     PosToWidget[dp],
	     (char*) NULL) != TCL_OK ) {
	PRINT_ERROR_AND_EXIT();
    }
}


WRISTWATCH_O_STOP_ENHANCING (dp)
DISPLAY_POSITION dp; 
{
    if (Eval("WRISTWATCH_O_STOP_ENHANCING ",
	     PosToWidget[dp],
	     (char*)NULL) != TCL_OK ) {
	PRINT_ERROR_AND_EXIT();
    }
}


WRISTWATCH_O_CHIME_STATUS (bool) {

    if (Eval("WRISTWATCH_O_CHIME_STATUS ",
	     (bool ? "1" : "0"),
	     (char*)NULL) != TCL_OK ) {
	PRINT_ERROR_AND_EXIT();
    }
}

WRISTWATCH_O_ALARM_STATUS (bool) {

    if (Eval("WRISTWATCH_O_ALARM_STATUS ",
	     (bool ? "1" : "0"),
	     (char*)NULL) != TCL_OK ) {
	PRINT_ERROR_AND_EXIT();
    }

}


WRISTWATCH_O_STOPWATCH_RUN_STATUS (bool) {

    if (Eval("WRISTWATCH_O_STOPWATCH_RUN_STATUS ",
	     (bool ? "1" : "0"),
	     (char*)NULL) != TCL_OK ) {
	PRINT_ERROR_AND_EXIT();
    }

}


WRISTWATCH_O_STOPWATCH_LAP_STATUS (bool) {

    if (Eval("WRISTWATCH_O_STOPWATCH_LAP_STATUS ",
	     (bool ? "1" : "0"),
	     (char*)NULL) != TCL_OK ) {
	PRINT_ERROR_AND_EXIT();
    }
}


WRISTWATCH_O_BEEP(beep)
BEEP_TYPE beep; 
{
    static char buffer[BUFSIZ];
    sprintf(buffer,"%d",beep);
    if (Eval("WRISTWATCH_O_BEEP ", 
	     buffer,
	     (char*)NULL) != TCL_OK) {
	PRINT_ERROR_AND_EXIT();
    }
}


/*----------------------------------------------------------------------------
 *
 * new interpreter commands (inputs)
 */

int Tcl_SetSpeed (data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    if ( argc != 2 ) {
	interp->result = "bad # of arguments";
	return TCL_ERROR;
    }

    if ( ! strcmp(argv[1], "-slow" ) ) {
	HUNDREDTHS_PER_INCREMENT = HUNDREDTHS_PER_SECOND;
    } else if ( ! strcmp(argv[1], "-fast" ) ) {
	HUNDREDTHS_PER_INCREMENT = 1;
    } 
    else {
	interp->result = "bad argument, must be -slow or -fast";
	return TCL_ERROR;
    } 
    return TCL_OK;
}

extern int WRISTWATCH();
extern void WRISTWATCH_I_UL();
extern void WRISTWATCH_I_UR();
extern void WRISTWATCH_I_LL();
extern void WRISTWATCH_I_LR();

int Tcl_UL(data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    WRISTWATCH_I_UL();
    return TCL_OK;
}

int Tcl_UR(data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    WRISTWATCH_I_UR();
    return TCL_OK;
}

int Tcl_LL(data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    WRISTWATCH_I_LL();
    return TCL_OK;
}


int Tcl_LR(data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    WRISTWATCH_I_LR();
    return TCL_OK;
}

int Tcl_S(data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    WRISTWATCH_I_S();
    return TCL_OK;
}

int Tcl_HS(data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    WRISTWATCH_I_HS();
    return TCL_OK;
}

int Tcl_WRISTWATCH(data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    WRISTWATCH();
    return TCL_OK;
}


/*------------------------------------------------------------
 * timer handler
 *------------------------------------------------------------
 */


static Tcl_AsyncHandler tclAsyncToken;
static int hundredth = 0;

static Tcl_DString interpResult;
static Tcl_DString errorInfo;
static Tcl_DString errorCode;

int tkWatch_AsyncHandler(clientData,
			 interp,
			 code)
ClientData clientData;
Tcl_Interp *interp;
int code;
{
    Tcl_Interp* local_interp;
    int local_code;


    Tcl_DStringFree(&interpResult);
    Tcl_DStringFree(&errorInfo);
    Tcl_DStringFree(&errorCode);

    local_interp = (interp != (Tcl_Interp*)NULL) ? interp : watch_interp;
    local_code = (interp != (Tcl_Interp*)NULL) ? code : TCL_OK;

    /* 
     * save some info : see Async.3 man tcl 
     */
    Tcl_DStringGetResult(local_interp, &interpResult);
    Tcl_DStringAppend(&errorInfo,
		      Tcl_GetVar(local_interp, "errorInfo", TCL_GLOBAL_ONLY),
		      -1);
    Tcl_DStringAppend(&errorCode,
		      Tcl_GetVar(local_interp, "errorCode", TCL_GLOBAL_ONLY),
		      -1);

    /* 
     * actual action 
     */
    hundredth += HUNDREDTHS_PER_INCREMENT;
    if ( hundredth == HUNDREDTHS_PER_SECOND ) {
	hundredth = 0;
	Tcl_Eval(local_interp, "WatchAppendEvent HS S");
    } else {
	Tcl_Eval(local_interp, "WatchAppendEvent HS");
    }

    /* 
     * restore saved info 
     */
    Tcl_DStringResult(local_interp, &interpResult);
    Tcl_SetVar(local_interp, 
	       "errorInfo", 
	       Tcl_DStringValue(&errorInfo), 
	       TCL_GLOBAL_ONLY);
    Tcl_SetVar(local_interp, 
	       "errorCode", 
	       Tcl_DStringValue(&errorCode), 
	       TCL_GLOBAL_ONLY);

    return local_code;
}


#ifndef WIN32
void sigalrm(sig)
int sig;
{
    /* indicates that the asynchrounous event is ready */
    signal(SIGALRM, sigalrm);
    Tcl_AsyncMark(tclAsyncToken);
}

static struct itimerval value;
static struct itimerval ovalue;


int Tcl_StartTimer(data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    if ( HUNDREDTHS_PER_INCREMENT < 100 ) {
      /* 
       * setitimer sets the timer to the given value 
       * it_interval is the value to used when reloading the timer
       */
      value.it_value.tv_sec = 0;
      value.it_value.tv_usec = 10000 * HUNDREDTHS_PER_INCREMENT; /* 1 hundredth of second */
      value.it_interval.tv_sec = 0;
      value.it_interval.tv_usec = 10000 * HUNDREDTHS_PER_INCREMENT; 

    }
    else {
      /* slow mode */
      value.it_value.tv_sec = 1;
      value.it_value.tv_usec = 0;
      value.it_interval.tv_sec = 1;
      value.it_interval.tv_usec = 0;
    }

    if (setitimer(ITIMER_REAL, &value, &ovalue)) {
      interp->result = "setitimer error";
      return TCL_ERROR;
    }

    signal(SIGALRM, sigalrm);
    INITIAL_WATCH_TIME = GET_INITIAL_WATCH_TIME();
    return TCL_OK;
}

#else 
static int basic_timer_period;
static SYSTEMTIME start_time;

char buffer[256];

void Tcl_WatchTimer(ClientData data)
{
    SYSTEMTIME saved;
    FILETIME ftEnd, ftStart;
    LARGE_INTEGER liEnd, liStart;
    int period;
    int delay;

    saved = start_time;

    GetSystemTime(&start_time);

    SystemTimeToFileTime(&start_time, &ftEnd);
    SystemTimeToFileTime(&saved, &ftStart);

    liEnd.HighPart = ftEnd.dwHighDateTime;
    liEnd.LowPart = ftEnd.dwLowDateTime;
    liStart.HighPart = ftStart.dwHighDateTime;
    liStart.LowPart = ftStart.dwLowDateTime;

    liEnd.QuadPart -= liStart.QuadPart;

    ftEnd.dwHighDateTime = liEnd.HighPart;
    ftEnd.dwLowDateTime = liEnd.LowPart;

    FileTimeToSystemTime(&ftEnd, &saved);

    /* delay in millesec between start and now */
    delay = ( saved.wSecond * 1000 + saved.wMilliseconds);

    /* try to recover lost time */
    period = basic_timer_period
	- (  delay - basic_timer_period);

    if ( period <= 0 ) {
	period = basic_timer_period;
    }


    Tcl_GlobalEval(watch_interp, buffer);

    Tcl_CreateTimerHandler(period, 
			   Tcl_WatchTimer,
			   (ClientData)NULL);
    /* 
     * actual action 
     */
    hundredth += HUNDREDTHS_PER_INCREMENT;
    if ( hundredth == HUNDREDTHS_PER_SECOND ) {
	hundredth = 0;
	Tcl_Eval(watch_interp, "WatchAppendEvent HS S");
    } else {
	Tcl_Eval(watch_interp, "WatchAppendEvent HS");
    }
}

int Tcl_StartTimer(data, interp, argc, argv)
ClientData data;
Tcl_Interp* interp;
int argc;
char** argv;
{
    if ( HUNDREDTHS_PER_INCREMENT < 100 ) {
	/* in ms */
	basic_timer_period = HUNDREDTHS_PER_INCREMENT * 10;
    } 
    else {
	/* 1 s */
	basic_timer_period = 1000;
    }

    Tcl_CreateTimerHandler(basic_timer_period, 
			   Tcl_WatchTimer,
			   (ClientData)NULL);

    GetSystemTime(&start_time);

    INITIAL_WATCH_TIME = GET_INITIAL_WATCH_TIME();
    return TCL_OK;
}

#endif


Tcl_GenericCommand input_commands[] = {
    {
	"WRISTWATCH", 
	(Tcl_CmdProc*)Tcl_WRISTWATCH, 
	(ClientData)NULL, 
	(Tcl_CmdDeleteProc *)NULL
    },
    {
	"WRISTWATCH_I_UL",
	(Tcl_CmdProc*)Tcl_UL,
	(ClientData)NULL,
	(Tcl_CmdDeleteProc *)NULL
    },
    {
	"WRISTWATCH_I_UR",
	(Tcl_CmdProc*)Tcl_UR,
	(ClientData)NULL,
	(Tcl_CmdDeleteProc *)NULL
    },
    {
	"WRISTWATCH_I_LL",
	(Tcl_CmdProc*)Tcl_LL,
	(ClientData)NULL,
	(Tcl_CmdDeleteProc *)NULL
    },
    {
	"WRISTWATCH_I_LR",
	(Tcl_CmdProc*)Tcl_LR,
	(ClientData)NULL,
	(Tcl_CmdDeleteProc *)NULL
    },
    {
	"WRISTWATCH_I_HS",
	(Tcl_CmdProc*)Tcl_HS,
	(ClientData)NULL,
	(Tcl_CmdDeleteProc *)NULL
    },
    {
	"WRISTWATCH_I_S",
	(Tcl_CmdProc*)Tcl_S,
	(ClientData)NULL,
	(Tcl_CmdDeleteProc *)NULL
    },
    {
	"WatchStartTimer",
	(Tcl_CmdProc*)Tcl_StartTimer,
	(ClientData)NULL,
	(Tcl_CmdDeleteProc *)NULL
    },
    {
	"WatchSetSpeed",
	(Tcl_CmdProc*)Tcl_SetSpeed,
	(ClientData)NULL,
	(Tcl_CmdDeleteProc *)NULL
    },
    { 
	(char*)NULL , 
	(Tcl_CmdProc*)NULL, 
	(ClientData)NULL, 
	(Tcl_CmdDeleteProc*)NULL 
    }
};



/*
 * tkWatch_Init
 *
 * initialization procedure
 */

typedef struct {
    char *name;
    char **tcl_code;
    long lines;
    long chars;
} Tcl2array;

extern int 
Tcl_LoadCodeArray _ANSI_ARGS_((Tcl_Interp *interp, Tcl2array code_array));

extern Tcl2array watch_script;

int TkWatch_Init(interp) 
Tcl_Interp* interp;
{
    int i=0;
    
    /*
	 * Set Tcl/Tk environment variables according to the ESTEREL global environment variable
	 */

    if ( getenv("ESTEREL") != (char*)NULL) {
	Tcl_DString library;
#ifndef WIN32
	char esterel[256];
	int size;
	strcpy(esterel, getenv("ESTEREL"));
	size = strlen(esterel);
#else
	char esterel[256];
	int size = 255;
	int i;
	size = GetShortPathName(getenv("ESTEREL"), esterel, (DWORD)size);
	for ( i = 0 ; i < size; i++ ) {
	    if (esterel[i] == '\\') {
		esterel[i] = '/';
	    }
	}
#endif
	/*
	 * Tcl library
	 */
	Tcl_DStringInit(&library);
	Tcl_DStringAppend(&library, esterel, size);
	Tcl_DStringAppend(&library, "/tcltk/lib/tcl", -1);
	Tcl_SetVar2(interp, "env", "TCL_LIBRARY", 
		    Tcl_DStringValue(&library), TCL_GLOBAL_ONLY);
	Tcl_DStringFree(&library);
	/*
	 * Tk library
	 */
	Tcl_DStringInit(&library);
	Tcl_DStringAppend(&library, esterel, size);
	Tcl_DStringAppend(&library, "/tcltk/lib/tk", -1);
	Tcl_SetVar2(interp, "env", "TK_LIBRARY", 
		    Tcl_DStringValue(&library), TCL_GLOBAL_ONLY);
	Tcl_DStringFree(&library);
    }


    if (Tcl_Init(interp) == TCL_ERROR) {
	return TCL_ERROR;
    }

    if (Tk_Init(interp) == TCL_ERROR) {
	return TCL_ERROR;
    }


    while (input_commands[i].cmdName != (char*)NULL) {
	Tcl_CreateCommand(interp,
			  input_commands[i].cmdName,
			  input_commands[i].proc,
			  input_commands[i].clientData,
			  input_commands[i].deleteProc);
	i++;
    }
    watch_interp = interp;  

    /* Creates an asynchronous handler */
    tclAsyncToken = Tcl_AsyncCreate(tkWatch_AsyncHandler, 
				    (ClientData)NULL);

    Tcl_DStringInit(&interpResult);
    Tcl_DStringInit(&errorInfo);
    Tcl_DStringInit(&errorCode);
    Tcl_DStringInit(&tcl_command);

    if ( Tcl_LoadCodeArray(interp, watch_script) != TCL_OK ) {
	/* error */
	return TCL_ERROR;
    }
    return TCL_OK;
}

