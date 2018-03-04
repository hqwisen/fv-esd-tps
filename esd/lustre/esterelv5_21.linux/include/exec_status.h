
#ifndef __EXEC_STATUS_H_LOADED
#define __EXEC_STATUS_H_LOADED

#ifndef NULL
#define NULL ((char*)0)
#endif

typedef struct {
    unsigned int start          : 1 ;
    unsigned int kill           : 1 ;
    unsigned int active         : 1 ;
    unsigned int suspended      : 1 ;
    unsigned int prev_active    : 1 ;
    unsigned int prev_suspended : 1 ;
    unsigned int exec_index;
    unsigned int task_exec_index;
    void (*pStart)();
    int (*pRet)();
} __ExecStatus;


#if defined(ANSIC) || defined(__STDC__)
#define name2(a,b) _name2_aux(a,b)
#define _name2_aux(a,b) a##b
#define name3(a,b,c) _name3_aux(a,b,c)
#define _name3_aux(a,b,c) a##b##c
#define name4(a,b,c,d) _name4_aux(a,b,c,d)
#define _name4_aux(a,b,c,d) a##b##c##d
#else
#define name2(a,b) a/**/b
#define name3(a,b,c) a/**/b/**/c
#define name4(a,b,c,d) a/**/b/**/c/**/d
#endif

static void __DUMMY__() {};

#define RET_STAT(Ret, Mod) name3(Mod,_exec_status_,Ret)

#define STD_EXEC(Ret, Mod, Start, Kill, Suspend, Resume) \
{ \
    extern __ExecStatus RET_STAT(Ret,Mod); \
    if (RET_STAT(Ret,Mod).kill || RET_STAT(Ret,Mod).start) { \
        if (RET_STAT(Ret,Mod).kill) { \
           Kill(&RET_STAT(Ret,Mod)); \
        } \
        if (RET_STAT(Ret,Mod).start) { \
           (*(RET_STAT(Ret,Mod).pStart))(Start); \
        } \
    } else if (   RET_STAT(Ret,Mod).suspended \
               && !RET_STAT(Ret,Mod).prev_suspended) { \
        Suspend(&RET_STAT(Ret,Mod)); \
    } else if (   !RET_STAT(Ret,Mod).suspended \
               && RET_STAT(Ret,Mod).prev_suspended) { \
        Resume(&RET_STAT(Ret,Mod)); \
    } \
}

#define TASK_ARRAY(Task, Mod) name3(Mod,_exec_status_array_of_,Task)

#define STD_EXEC_FOR_TASK(Task, Mod, Start, Kill, Suspend, Resume) \
{ \
    extern __ExecStatus *TASK_ARRAY(Task,Mod)[]; \
    int index; \
    for (index = 0; \
         TASK_ARRAY(Task,Mod)[index] != (__ExecStatus*)NULL; \
         index++) { \
       if (   TASK_ARRAY(Task,Mod)[index]->kill \
           || TASK_ARRAY(Task,Mod)[index]->start) { \
          if (TASK_ARRAY(Task,Mod)[index]->kill) { \
              Kill(TASK_ARRAY(Task,Mod)[index]); \
          } \
          if (TASK_ARRAY(Task,Mod)[index]->start) { \
              (*(TASK_ARRAY(Task,Mod)[index]->pStart))(Start); \
          } \
       } else if (   TASK_ARRAY(Task,Mod)[index]->suspended \
                  && !TASK_ARRAY(Task,Mod)[index]->prev_suspended) { \
           Suspend(TASK_ARRAY(Task,Mod)[index]); \
       } else if (   !TASK_ARRAY(Task,Mod)[index]->suspended \
                  && TASK_ARRAY(Task,Mod)[index]->prev_suspended) { \
           Resume(TASK_ARRAY(Task,Mod)[index]); \
       } \
   } \
}

#endif
