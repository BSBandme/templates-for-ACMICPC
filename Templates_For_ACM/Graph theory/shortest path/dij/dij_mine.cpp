#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

const int inf = 1000000000;
const int maxn = 1001;

int map[maxn][maxn];
int np, ne;

void dij(int be, int en, int map[maxn][maxn], int fa[maxn] = NULL)
{
	int i, j, k;
	int minl, minno;
	int f[maxn];

	memset(f, 0, sizeof(f));
	f[be] = 1;
	for(i = 0; i < np; i++)
	{
		minl = inf;
		for(j = 0; j < np; j++)
			if(map[be][j] < minl && !f[j])
			{
				minl = map[be][j];
				minno = j;
			}
		f[minno] = 1;
		if(minno == en)
			break;
		for(j = 0; j < np; j++)
			if(map[be][j] > map[be][minno] + map[minno][j])
			{
				map[be][j] = map[be][minno] + map[minno][j];
				map[j][be] = map[be][j];
				if(fa)
					fa[j] = minno;
			}
	}
}

int main()
{
	int i, j, k, i1;
	freopen("min.in", "r", stdin);

	scanf("%d%d", &ne, &np);
	for(i = 0; i < np; i++)
		for(j = 0; j < np; j++)
			map[i][j] = inf;
	for(i1 = 0; i1 < ne; i1++)
	{
		scanf("%d%d%d", &i, &j, &k);
		i--; j--;
		if(k < map[i][j])
		{
			map[i][j] = k;
			map[j][i] = k;
		}
	}

	dij(0, np - 1, map);

	cout << map[0][np - 1] << endl;
	
	return 0;
}