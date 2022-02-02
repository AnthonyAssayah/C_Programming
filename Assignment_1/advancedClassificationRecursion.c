#include <stdio.h>
#include <math.h>
#include"NumClass.h"

int reverse(int x)
{

    int digit = (int)log10(x);

    if (x == 0)
        return 0;

    return ((x % 10 * pow(10, digit)) + reverse(x / 10));
}

int isPalindrome(int x)
{

    if (x == reverse(x))
    {
        return 1;
    }

    return 0;
}


int isHelper(int x, int k)
{

    if (x <= 0)
    {
        return 0;
    }

    return (pow((x % 10), k)) + isHelper(x / 10, k);
}

int isArmstrong(int x)
{
    int k = log10(x) + 1;

    if (x == isHelper(x,k))
    {
        return 1;
    }

    return 0;
}
