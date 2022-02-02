#include<stdio.h>
#include"NumClass.h"

int isPrime(int x) {

    int i;
    if ( x < 1) return 0;
    if ( x == 1) return 1;
    for ( i = 2; i <= x/2; i++)
    {
        if( x%i == 0) 
            return 0;
        
    }
    return 1;
}

int factorial(int x) {

    int m = 1;
    for(int i=1; i <= x; i++) {
        m = m*i;
        }
        return m;
}

int isStrong(int n) {

    int sum =0;
    int x = n;
    int y;

    while( x!= 0) {
        y = x%10;
        int f = factorial(y);
        x = x/10;
        sum = sum +f;
    }
    if(sum == n) return 1;
         return 0;
}


