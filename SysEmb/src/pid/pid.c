/********
* ec2c version 0.67
* c file generated for node : pid 
* context   method = HEAP
* ext call  method = PROCEDURES
********/
#include <stdlib.h>
#include <string.h>
#define _pid_EC2C_SRC_FILE
#include "pid.h"
/*--------
Internal structure for the call
--------*/
typedef struct  {
   void* client_data;
   //INPUTS
   _integer _r;
   //OUTPUTS
   _integer _v;
   //REGISTERS
   _boolean M2;
} pid_ctx;
/*--------
Output procedures must be defined,
Input procedures must be used:
--------*/
void pid_I_r(pid_ctx* ctx, _integer V){
   ctx->_r = V;
}
extern void pid_O_v(void* cdata, _integer);
#ifdef CKCHECK
extern void pid_BOT_v(void* cdata);
#endif
/*--------
Internal reset input procedure
--------*/
static void pid_reset_input(pid_ctx* ctx){
   //NOTHING FOR THIS VERSION...
}
/*--------
Reset procedure
--------*/
void pid_reset(pid_ctx* ctx){
   ctx->M2 = _true;
   pid_reset_input(ctx);
}
/*--------
Copy the value of an internal structure
--------*/
void pid_copy_ctx(pid_ctx* dest, pid_ctx* src){
   memcpy((void*)dest, (void*)src, sizeof(pid_ctx));
}
/*--------
Dynamic allocation of an internal structure
--------*/
pid_ctx* pid_new_ctx(void* cdata){
   pid_ctx* ctx = (pid_ctx*)calloc(1, sizeof(pid_ctx));
   ctx->client_data = cdata;
   pid_reset(ctx);
   return ctx;
}
/*--------
Step procedure
--------*/
void pid_step(pid_ctx* ctx){
//LOCAL VARIABLES
   _integer L1;
//CODE
   if (ctx->M2) {
      L1 = 20;
   } else {
      L1 = 3;
   }
   pid_O_v(ctx->client_data, L1);
   ctx->M2 = ctx->M2 && !(_true);
}
