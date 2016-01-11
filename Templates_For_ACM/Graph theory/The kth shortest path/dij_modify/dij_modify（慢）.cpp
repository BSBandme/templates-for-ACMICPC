#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 1010;
const int inf = 2100000000;
int be, en, kth, n, m;
vector <int> edge[maxn][maxn];
int dist[maxn][maxn];
int v[maxn];

int dij_k(int be, int en, int kth, int n)
{
	int i, j, k, no;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < kth + 2; j++)
			dist[i][j] = inf;
		v[i] = 1;
	}
	v[be] = 0;
	dist[be][0] = 0;
	while(1)
	{
		k = inf;
		no = 0;
		for(i = 0; i < n; i++)
			if(dist[i][v[i]] != inf && dist[i][v[i]] < k && v[i] <= kth)
			{
				no = i;
				k = dist[i][v[i]];
			}
		if(k == inf)
			return -1;
		if(no == en && v[en] == kth)
			break;
		for(i = 0; i < n; i++)
			for(k = 0; k < edge[no][i].size(); k++)
		{
			if(dist[i][kth + 1] > dist[no][v[no]] + edge[no][i][k])
				dist[i][kth + 1] = dist[no][v[no]] + edge[no][i][k];
			j = kth + 1;
			while(dist[i][j] < dist[i][j - 1] && j > v[i])
			{
				swap(dist[i][j], dist[i][j - 1]);
				j--;
			}
		}
		v[no]++;
	}

	return dist[en][kth];
}

int main()
{
	int i1, j, k, l, i;
//	freopen("2449.in", "r", stdin);

	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(edge, 0, sizeof(edge));
		for(i1 = 0; i1 < m; i1++)
		{
			scanf("%d%d%d", &i, &j, &l);
			i--; j--;
			edge[i][j].push_back(l);
		}
		scanf("%d%d%d", &be, &en, &kth);
		be--; en--;

		printf("%d\n", dij_k(be, en, kth, n));
	}

	return 0;
}
