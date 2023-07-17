// 抛硬币测试

#include <stdlib.h>
#include <stdio.h>

int head()
{
	return rand() < RAND_MAX / 2;
}

void main()
{
	int N = 20;
	int M = 1000;
	int cnt, j;

	int *f = (int*)malloc((N + 1) * sizeof(int));

	for (int i = 0; i <= N; ++i) f[i] = 0;
	for (int i = 0; i < M; ++i, f[cnt]++)
		for(cnt = 0, j = 0; j <= N; ++j)
			if (head())
				cnt++;

	for (int j = 0; j <= N; ++j)
	{
		printf("%2d ", j);
		for (int i = 0; i < f[j]; i += 10)
			printf("*");
		printf("\n");
	}
}