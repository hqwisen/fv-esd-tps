#include <stdio.h>
#include "EDGE.c"


int main(){
    EDGE_ctx* ctx = EDGE_new_ctx(NULL);
    _boolean input;
    while(1){
        scanf("%d", &input);
        printf("Your input is %d\n", input);
        EDGE_I_X(ctx, input);
        EDGE_step(ctx);
    }
    return 0;
}

void EDGE_O_state(void * cdata, _boolean b){
    printf("Output: %d\n");
}
