#include <stdio.h>

#define N 1000

int main()
{
    int a[N];

    for(int i = 2; i < N; ++i) a[i] = 1;

    for(int i = 2; i < N; ++i)
    {
        if(a[i])
        {
            for(int j = i; j < N / i; ++j)
                a[i * j] = 0;
        }
    }
    for(int i = 2; i < N; ++i)
        if(a[i])
            printf("%4d ", i);
    
    return 0;
}