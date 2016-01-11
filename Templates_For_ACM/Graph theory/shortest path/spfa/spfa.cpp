#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

const int inf = 1000000000;
const int maxn = 1000;

int map[maxn][maxn];
int np, ne;

void spfa(int map[][maxn], int np, int be, int fa[maxn] = NULL)
{
	queue <int> q;
	bool f[maxn];
	int i, j, k, ranno;

	memset(f, 0, sizeof(f));
	for(i = 0; i < np; i++)
		if(map[be][i] != inf)
		{
			q.push(i);
			f[i] = 1;
		}
	map[be][be] = 0;
	while(q.size())
	{
		ranno = q.front();
		q.pop();
		f[ranno] = 0;
		for(i = 0; i < np; i++)
		{
			if(i == ranno)
				continue;
			if(map[be][i] > map[be][ranno] + map[ranno][i])
			{
				map[be][i] = map[be][ranno] + map[ranno][i];
				map[i][be] = map[be][i];
				if(!f[i])
				{
					f[i] = 1;
					q.push(i);
				}
				if(fa)
					fa[i] = ranno;
			}
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

	spfa(map, np, 0);

	cout << map[0][np - 1] << endl;

	return 0;
}