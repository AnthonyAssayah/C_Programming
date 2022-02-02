#include <stdio.h>
#include "my_mat.h"
#include "my_mat.c"
#include <math.h>


int main() {
    char function;
    int matrix [10][10];
    int x,y;
    scanf("%c",&function);

    while(function!='D'){

        if(function=='A'){
            function_A(matrix);
        }
        else if(function=='B'){
            scanf("%d %d",&x,&y);
            function_B(matrix,x,y);
            printf("\n");
        }
        else if(function=='C'){
            scanf("%d %d",&x,&y);
            function_C(matrix,x,y);
            printf("\n");

        }
        scanf("%c",&function);
    }
}
