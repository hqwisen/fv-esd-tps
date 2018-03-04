/********
* ec2c version 0.67
* c file generated for node : EDGE 
* context   method = HEAP
* ext call  method = PROCEDURES
********/
#include <stdlib.h>
#include <string.h>
#define _EDGE_EC2C_SRC_FILE
#include "EDGE.h"
/*--------
Internal structure for the call
--------*/
typedef struct  {
   void* client_data;
   //INPUTS
   _boolean _X;
   //OUTPUTS
   _boolean _state;
   //REGISTERS
   _boolean M7;
   _boolean M7_nil;
   _boolean M2;
} EDGE_ctx;
/*--------
Output procedures must be defined,
Input procedures must be used:
--------*/
void EDGE_I_X(EDGE_ctx* ctx, _boolean V){
   ctx->_X = V;
}
extern void EDGE_O_state(void* cdata, _boolean);
#ifdef CKCHECK
extern void EDGE_BOT_state(void* cdata);
#endif
/*--------
Internal reset input procedure
--------*/
static void EDGE_reset_input(EDGE_ctx* ctx){
   //NOTHING FOR THIS VERSION...
}
/*--------
Reset procedure
--------*/
void EDGE_reset(EDGE_ctx* ctx){
   ctx->M7_nil = _true;
   ctx->M2 = _true;
   EDGE_reset_input(ctx);
}
/*--------
Copy the value of an internal structure
--------*/
void EDGE_copy_ctx(EDGE_ctx* dest, EDGE_ctx* src){
   memcpy((void*)dest, (void*)src, sizeof(EDGE_ctx));
}
/*--------
Dynamic allocation of an internal structure
--------*/
EDGE_ctx* EDGE_new_ctx(void* cdata){
   EDGE_ctx* ctx = (EDGE_ctx*)calloc(1, sizeof(EDGE_ctx));
   ctx->client_data = cdata;
   EDGE_reset(ctx);
   return ctx;
}
/*--------
Step procedure
--------*/
void EDGE_step(EDGE_ctx* ctx){
//LOCAL VARIABLES
   _boolean L6;
   _boolean L5;
   _boolean L1;
   _boolean T7;
//CODE
   L6 = (! ctx->M7);
   L5 = (ctx->_X && L6);
   if (ctx->M2) {
      L1 = _false;
   } else {
      L1 = L5;
   }
   EDGE_O_state(ctx->client_data, L1);
   T7 = ctx->_X;
   ctx->M7 = T7;
   ctx->M7_nil = _false;
   ctx->M2 = ctx->M2 && !(_true);
}
