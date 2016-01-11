#include <iostream>
#include <cstdio>
#include <time.h>

using namespace std;

int main()
{
	int i;

	int n = 10, m = 20;
	freopen("output.txt", "w", stdout);
	srand((unsigned)time(NULL));
	printf("%d %d\n", n, m);
	for(i = 0; i < m; i++)
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, (((i % n) *  (i % n)) % 100 + ((i % n) * (i % n) * (i % n)) % 100) + 1);
	printf("1 %d %d\n", n, m);
}