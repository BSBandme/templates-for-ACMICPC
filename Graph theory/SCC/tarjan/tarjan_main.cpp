#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 100000;
vector <int> map[maxn];
vector <int> :: iterator itr;
int stack[maxn]; 
//id 为节点的强连通编号(从0开始)，slian为强分个数，pre为搜的顺序
int ls, low[maxn], pre[maxn], slian, id[maxn], count1;
int n, m;

void tarjan(int v, int n)
{
	int i, j, k, ranmin = low[v] = pre[v] = count1++;

	stack[ls++] = v;
	for(i = 0; i < map[v].size(); i++)
	{
		if(pre[map[v][i]] == -1)
			tarjan(map[v][i], n);
		if(low[map[v][i]] < ranmin)
			ranmin = low[map[v][i]];
	}
	if(ranmin < low[v])
	{
		low[v] = ranmin;
		return;
	}
	do
	{
		ls--;
		id[stack[ls]] = slian;
		low[stack[ls]] = n;
	}while(stack[ls] != v);
	slian++;
}

int main()
{
	int i, j, k;
	freopen("2002.in", "r", stdin);

	memset(pre, -1, sizeof(pre));
	memset(id, -1, sizeof(id));
	memset(stack, -1, sizeof(stack));
	scanf("%d%d", &n, &m);
	for(i = 0; i < m; i++)
	{
		scanf("%d%d", &j, &k);
		j--; k--;
		map[j].push_back(k);
	}

	for(i = 0; i < n; i++)
		if(pre[i] == -1)
			tarjan(i, n);

	printf("%d\n", slian);
	for(i = 0; i < n; i++)
		printf("%d ", id[i]);

	return 0;
}