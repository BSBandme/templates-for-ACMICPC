#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

const int inf = 1000000000;
int be, en, kth, n, m;
int edge[1010][1010];
int dist[1010][1010];
int v[1010];

int main()
{
	int i, j, k, l;
	freopen("2449.in", "r", stdin);

	while(scanf("%d%d", &n, &m) == 2)
	{
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				edge[i][j] = inf;
		for(i = 0; i < m; i++)
		{
			scanf("%d%d%d", &i, &j, &l);
			i--; j--;
			edge[i][j] = edge[i][j] < l ? edge[i][j] : l;
		}
		scanf("%d%d%d", &be, &en, &kth);
		be--; en--; kth--;
	}
	return 0;
}
