#include <stdio.h>
#include "my_mat.h"
#include <math.h>



void floydWarshall(int matrix[10][10]) {

  for (int k = 0; k < 10; k++) {
      for (int i = 0; i < 10; i++) {
          for (int j = 0; j < 10; j++) {
              if(matrix[i][j]!=0 && matrix[i][k]!=0 && matrix[k][j]!=0){
                    matrix[i][j]=fmin(matrix[i][j],matrix[i][k]+matrix[k][j]);
                }
              if(i!=j && matrix[i][j]==0 && matrix[i][k]!=0 && matrix[k][j]!=0){
                        matrix[i][j]=matrix[i][k]+matrix[k][j];
                }    
            }
        }
    }
}

void function_A(int matrix [10][10]){
    for(int i=0;i<10;i++){
        for(int k=0;k<10;k++){
            scanf("%d",&matrix[i][k]);
        }
    }
    floydWarshall(matrix);
    

}

void function_B(int matrix [10][10],int x,int y){
    
    if(matrix[x][y]!=0){
        printf("True");
    }else{
        printf("False");
    }
}
void function_C(int matrix [10][10],int x,int y){
   
    if(matrix[x][y]!=0){
        printf("%d",matrix[x][y]);
    }else{
        printf("-1");
    }
}