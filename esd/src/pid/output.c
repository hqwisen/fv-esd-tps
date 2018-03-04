/********
* ec2c version 0.67
* c file generated for node : output 
* context   method = HEAP
* ext call  method = PROCEDURES
********/
#include <stdlib.h>
#include <string.h>
#define _output_EC2C_SRC_FILE
#include "output.h"
/*--------
Internal structure for the call
--------*/
typedef struct  {
   void* client_data;
   //INPUTS
   _real _u;
   _real _w;
   //OUTPUTS
   _real _y;
   //REGISTERS
   _real M12;
   _boolean M12_nil;
   _boolean M3;
} output_ctx;
/*--------
Output procedures must be defined,
Input procedures must be used:
--------*/
void output_I_u(output_ctx* ctx, _real V){
   ctx->_u = V;
}
void output_I_w(output_ctx* ctx, _real V){
   ctx->_w = V;
}
extern void output_O_y(void* cdata, _real);
#ifdef CKCHECK
extern void output_BOT_y(void* cdata);
#endif
/*--------
Internal reset input procedure
--------*/
static void output_reset_input(output_ctx* ctx){
   //NOTHING FOR THIS VERSION...
}
/*--------
Reset procedure
--------*/
void output_reset(output_ctx* ctx){
   ctx->M12_nil = _true;
   ctx->M3 = _true;
   output_reset_input(ctx);
}
/*--------
Copy the value of an internal structure
--------*/
void output_copy_ctx(output_ctx* dest, output_ctx* src){
   memcpy((void*)dest, (void*)src, sizeof(output_ctx));
}
/*--------
Dynamic allocation of an internal structure
--------*/
output_ctx* output_new_ctx(void* cdata){
   output_ctx* ctx = (output_ctx*)calloc(1, sizeof(output_ctx));
   ctx->client_data = cdata;
   output_reset(ctx);
   return ctx;
}
/*--------
Step procedure
--------*/
void output_step(output_ctx* ctx){
//LOCAL VARIABLES
   _real L5;
   _real L10;
   _real L13;
   _real L9;
   _real L8;
   _real L2;
   _real T12;
//CODE
   if (ctx->M3) {
      L5 = 20.000000;
   } else {
      L5 = 21.000000;
   }
   L10 = (0.700000 * ctx->M12);
   L13 = (0.500000 * ctx->_u);
   L9 = (L10 + L13);
   L8 = (L9 - ctx->_w);
   if (ctx->M3) {
      L2 = L5;
   } else {
      L2 = L8;
   }
   output_O_y(ctx->client_data, L2);
   T12 = L2;
   ctx->M12 = T12;
   ctx->M12_nil = _false;
   ctx->M3 = ctx->M3 && !(_true);
}
