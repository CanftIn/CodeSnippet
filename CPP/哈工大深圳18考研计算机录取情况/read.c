#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *f = fopen("s", "r");
    char a[4];
    int sum = 0;
    int n380 = 0;
    int n390 = 0;
    int n400 = 0;
    while(fgets(a, 4, f))
    {
        if(atoi(a) > 380)
        {
            n380 = n380 + 1;
        }
        if(atoi(a) > 390)
        {
            n390 = n390 + 1;
        }
        if(atoi(a) > 400)
        {
            n400 = n400 + 1;
        }
        sum += atoi(a);
    }
    fclose(f);
    printf("哈工大深圳初试录取分数总和 : %d\n", sum);
    int res = sum / 39;
    printf("平均分 : %d\n", res);
    printf("录取总人数 : 39 人\n");
    printf("初试分数>380有 %d 人\n", n380);
    printf("初试分数>390有 %d 人\n", n390);
    printf("初试分数>400有 %d 人\n", n400);
    return 0;
}