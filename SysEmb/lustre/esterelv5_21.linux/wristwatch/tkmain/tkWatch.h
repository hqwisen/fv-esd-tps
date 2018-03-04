#include "tk.h"

typedef struct Tcl_GenericCommand { 
    /* see Tcl_CreateCommand */
    char             * cmdName;      /* name of the command to create */
    Tcl_CmdProc      * proc;         /* Implementation of new command: proc
                                      * will be called whenever cmdName is 
                                      * invoked as a command */
    ClientData       clientData;     /* arbitrary on word value to pass to proc
                                      * and deleteProc */
    Tcl_CmdDeleteProc * deleteProc;  /* Procedure to call before cmdName
                                      * is deleted from the interpreter.
                                      * if NULL the no procedure will be 
                                      * called */

} Tcl_GenericCommand ;

extern int TkWatch_Init _ANSI_ARGS_((Tcl_Interp*));


#include "wristwatch.h"

extern WATCH_TIME_TYPE INITIAL_WATCH_TIME;
extern WATCH_TIME_TYPE GET_INITIAL_WATCH_TIME();


