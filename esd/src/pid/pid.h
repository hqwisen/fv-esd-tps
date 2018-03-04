/********
* ec2c version 0.67
* context   method = HEAP
* ext call  method = PROCEDURES
* c header file generated for node : pid 
* to be used with : pid.c 
********/
#ifndef _pid_EC2C_H_FILE
#define _pid_EC2C_H_FILE
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
//MODULE: pid 1 1
//IN: _integer r
//OUT: _integer v
#ifndef _pid_EC2C_SRC_FILE
/*--------Context type -------------*/
struct pid_ctx;
/*-------- Input procedures -------------*/
extern void pid_I_r(struct pid_ctx* ctx, _integer);
/*-------- Reset procedure -----------*/
extern void pid_reset(struct pid_ctx* ctx);
/*--------Context copy -------------*/
extern void pid_copy_ctx(struct pid_ctx* dest, struct pid_ctx* src);
/*--------Context allocation --------*/
extern struct pid_ctx* pid_new_ctx(void* client_data);
/*-------- Step procedure -----------*/
extern void pid_step(struct pid_ctx* ctx);
#endif
#endif
