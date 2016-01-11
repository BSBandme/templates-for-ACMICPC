#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 1010;
const int inf = 1000000000;
struct node
{
	int v, next, dist, pre_dist;
	bool separate;
	inline bool operator < (const node &a) const
	{
		return dist + pre_dist > a.dist + a.pre_dist;
	}
}ve[maxn];
int be, en, kth, n, m;
vector <int> edge[maxn][maxn];
vector <int> :: iterator itr;
int min_edge[maxn][maxn];

void init_dij(int en)
{
	int i, j, k, no;
	bool f[maxn];

	memset(f, 0, sizeof(f));
	for(i = 0; i < n; i++)
		ve[i].dist = inf;
	ve[en].dist = 0;
	ve[en].v = en;
	ve[en].next = en;
	for(i = 0; i < n; i++)
	{
		k = inf;
		no = 0;
		for(j = 0; j < n; j++)
			if(!f[j] && ve[j].dist < k)
			{
				k = ve[j].dist;
				no = j;
			}
		f[no] = 1;
		ve[no].v = no;
		for(j = 0; j < n; j++)
			if(min_edge[j][no] != inf && ve[j].dist > ve[no].dist + min_edge[j][no])	
			{
				ve[j].dist = ve[no].dist + min_edge[j][no];
				ve[j].next = no;
			}
	}
}

int dij_k(int be, int en, int kth, int n)
{
	int i, j, k;
	node ranno, ranno1;
	int nk, pre;
	priority_queue <node> pq;
	bool f;

	init_dij(en);
	if(ve[be].dist == inf)
		return -1;

	ranno = ve[be];
//	ranno.separate = 0;
	pq.push(ranno);
	nk = 0;
	while(pq.size() && nk < kth - 1)
	{
		ranno = pq.top();
		pq.pop();
		nk++;
		pre = -1;
		while(pre != en)
		{
			f = 0;
			for(i = 0; i < n; i++)
				for(j = 0; j < edge[ranno.v][i].size(); j++)
				{
					ranno1 = ve[i];
					ranno1.pre_dist = ranno.pre_dist + edge[ranno.v][i][j];
					if(!f && i == ranno.next && edge[ranno.v][i][j] + ranno1.dist == ranno.dist)
					{
						f = 1;
						continue;
					}
					if(ranno1.dist != inf)
						pq.push(ranno1);
				}
			pre = ranno.v;
			j = ranno.pre_dist + ranno.dist - ve[ranno.next].dist;
			ranno = ve[ranno.next];
			ranno.pre_dist = j;
		}
	}
	if(nk == kth - 1 && pq.size())
		return pq.top().pre_dist + pq.top().dist;
	return -1;
}

int main()
{
	int i1, j, k, l, i;
//	freopen("2449.in", "r", stdin);

	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(edge, 0, sizeof(edge));
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				min_edge[i][j] = inf;
		for(i1 = 0; i1 < m; i1++)
		{
			scanf("%d%d%d", &i, &j, &l);
			i--; j--;
			edge[i][j].push_back(l);
			if(l < min_edge[i][j])
				min_edge[i][j] = l;
		}
		itr = edge[619][593].begin();
		scanf("%d%d%d", &be, &en, &kth);
		be--; en--;
		if(be == en)
			kth++;

		printf("%d\n", dij_k(be, en, kth, n));
	}

	return 0;
}
