#include <stdio.h>
#include <stdlib.h>

long long fast_pow(long long x, long long n)
{
    long long result;
    if(n == 0)
        return 1;
    else
    {
        while((n & 1) == 0)
        {
            n >>= 1;
            x *= x;
        }
    }
    result = x;
    n >>= 1;
    while(n != 0)
    {
        x *= x;
        if((n & 1) == 0)
            result *= x;
        n >>= 1;
    }
    return result;
}

int main()
{
    printf("%d\n", fast_pow(100, 5));
    return 0;
}