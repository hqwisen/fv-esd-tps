/********
* ec2c version 0.67
* context   method = HEAP
* ext call  method = PROCEDURES
* c header file generated for node : EDGE 
* to be used with : EDGE.c 
********/
#ifndef _EDGE_EC2C_H_FILE
#define _EDGE_EC2C_H_FILE
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
//MODULE: EDGE 1 1
//IN: _boolean X
//OUT: _boolean state
#ifndef _EDGE_EC2C_SRC_FILE
/*--------Context type -------------*/
struct EDGE_ctx;
/*-------- Input procedures -------------*/
extern void EDGE_I_X(struct EDGE_ctx* ctx, _boolean);
/*-------- Reset procedure -----------*/
extern void EDGE_reset(struct EDGE_ctx* ctx);
/*--------Context copy -------------*/
extern void EDGE_copy_ctx(struct EDGE_ctx* dest, struct EDGE_ctx* src);
/*--------Context allocation --------*/
extern struct EDGE_ctx* EDGE_new_ctx(void* client_data);
/*-------- Step procedure -----------*/
extern void EDGE_step(struct EDGE_ctx* ctx);
#endif
#endif
