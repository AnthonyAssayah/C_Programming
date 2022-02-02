#include <stdio.h>
#include <math.h>
#include"NumClass.h"

int isArmstrong(int x) {

    int r;
    int sum=0;  
    int tmp=x;    
    int k = log10(x)+1;

    while(tmp>0) {    

        r= tmp%10;    
        sum += pow(r,k);  
        tmp /= 10;    
    
    }    

    if (x==sum)  return 1;
        
    return 0;
}

int isPalindrome(int x) {

    int reversed = 0;
    int r;
    int tmp = x;

  
    while (tmp != 0) {
        r = tmp % 10;
        reversed = reversed * 10 + r;
        tmp /= 10;
    }

   
    if (x == reversed)
        return 1;
  
    return 0;

}
