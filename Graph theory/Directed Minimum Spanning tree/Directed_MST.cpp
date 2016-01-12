//最小树形图。
//此没步骤4，因为res可在找出环后将环中点距离全部加起，之后在加收缩之后更新的边的值
//另外还有Edmonds' algorithm
#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int V = 100;
const int E = 1000;

#define typec int // type of res
const typec inf = 0x3f3f3f3f; // max of res
typec res, dis[V]; // res为结果，dis[i]代表所有到i的边的最短值
int to[V], cp[V], tag[V];
//to[i]代表到dis[i]的发出点，cp[i]为将环收缩后环中的代表点,tag[i]在步骤2时用到，若i为环中某点则tag[i] == -2,其他点tag[i] == i;若还为判断tag[i]则tag[i] == -1

struct Edge { int u, v; typec c; } eg[E];

int iroot(int i){
	if (cp[i] == i) return i;
		return cp[i] = iroot(cp[i]);
}//

int dirtree(int root, int nv, int ne) // root: 树根
{ // vertex: 0 ~ n-1
	int i, j, k, circle = 0;

	memset(tag, -1, sizeof(tag));
	memset(to, -1, sizeof(to));
	//以下为步骤一
	for (i = 0; i < nv; ++i) dis[i] = inf;
	for (j = 0; j < ne; ++j) {
		i = iroot(eg[j].u); k = iroot(eg[j].v);
		if (k != i && dis[k] > eg[j].c) {
			dis[k] = eg[j].c;
			to[k] = i;
		}	
	}
        //以下为步骤二
	to[root] = -1; dis[root] = 0; tag[root] = root;
	for (i = 0; i < nv; ++i) if (cp[i] == i && -1 == tag[i]){
		j = i;
		for ( ; j != -1 && tag[j] == -1; j = to[j])
			tag[j] = i;
		if (j == -1) return 0;    //j== -1则必有一点无入度
		if (tag[j] == i) {
			circle = 1; tag[j] = -2;
			for (k = to[j]; k != j; k = to[k]) tag[k] = -2;
		}
	}
	//以下为步骤三
	if (circle) {
		for (j = 0; j < ne; ++j) {
			i = iroot(eg[j].u); k = iroot(eg[j].v);
			if (k != i && tag[k] == -2) eg[j].c -= dis[k];//更新边权
		}
		for (i = 0; i < nv; ++i) if (tag[i] == -2) {
			res += dis[i]; tag[i] = 0;
			for (j = to[i]; j != i; j = to[j]) {
				res += dis[j]; cp[j] = i; tag[j] = 0;
			}
		}
		if (0 == dirtree(root, nv, ne)) return 0;
	} else {
		for (i = 0; i < nv; ++i) if (cp[i] == i) res += dis[i];
	}
	return 1; // 若返回0代表原图不连通
}
int n, m;

int main()
{
	int i, j, k;
	freopen("input.txt", "r", stdin);
	
	scanf("%d%d", &n, &m);
	for(int i1 = 0; i1 < m; i1++)
	{
		scanf("%d%d%d", &i, &j, &k);
		i--; j--;
		eg[i1].u = i;
		eg[i1].v = j;
		eg[i1].c = k;
	}

	for(i = 0; i < m; i++)
		cp[i] = i;
	printf("%d\n", dirtree(0, n, m));
	cout << res << endl;

	return 0;
}
