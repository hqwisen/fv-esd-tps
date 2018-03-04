/********
* ec2c version 0.67
* context   method = HEAP
* ext call  method = PROCEDURES
* c header file generated for node : output 
* to be used with : output.c 
********/
#ifndef _output_EC2C_H_FILE
#define _output_EC2C_H_FILE
/*-------- Predefined types ---------*/
#ifndef _EC2C_PREDEF_TYPES
#define _EC2C_PREDEF_TYPES
typedef int _boolean;
typedef int _integer;
typedef char* _string;
typedef double _real;
typedef double _double;
typedef float _float;
#define _false 0
#define _true 1
#endif
/*--------- Pragmas ----------------*/
//MODULE: output 2 1
//IN: _real u
//IN: _real w
//OUT: _real y
#ifndef _output_EC2C_SRC_FILE
/*--------Context type -------------*/
struct output_ctx;
/*-------- Input procedures -------------*/
extern void output_I_u(struct output_ctx* ctx, _real);
extern void output_I_w(struct output_ctx* ctx, _real);
/*-------- Reset procedure -----------*/
extern void output_reset(struct output_ctx* ctx);
/*--------Context copy -------------*/
extern void output_copy_ctx(struct output_ctx* dest, struct output_ctx* src);
/*--------Context allocation --------*/
extern struct output_ctx* output_new_ctx(void* client_data);
/*-------- Step procedure -----------*/
extern void output_step(struct output_ctx* ctx);
#endif
#endif
