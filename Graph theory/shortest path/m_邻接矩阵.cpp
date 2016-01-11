#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

const int inf = 1000000000;
int map[1000][2];
int np, ne;

int main()
{
	int i, j, k;
	freopen("min.in", "r", stdin);

	scanf("%d%d", &np, &ne);
	memset(map, inf, sizeof(map));
	for(i = 0; i < ne; i++)
	{
		scanf("%d%d%d", &i, &j, &k);
		i--; j--;
		map[i][j] = k;
	}

	return 0;
}