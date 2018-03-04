#include <stdio.h>
#include "pid.c"


int main(){
    pid_ctx* ctx = pid_new_ctx(NULL);
    int input;
    while(1){
        scanf("%d", &input);
        printf("Your speed is %d\n", input);
        pid_I_r(ctx, input);
        pid_step(ctx);
    }
    return 0;
}

void pid_O_v(void * cdata, int v){
    printf("New speed: %d\n", v);
}
