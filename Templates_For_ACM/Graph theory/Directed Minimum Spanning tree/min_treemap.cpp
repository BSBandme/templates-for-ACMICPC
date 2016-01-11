//��С����ͼ��
//��û����4����Ϊres�����ҳ����󽫻��е����ȫ������֮���ڼ�����֮����µıߵ�ֵ
//���⻹��Edmonds' algorithm
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
typec res, dis[V]; // resΪ�����dis[i]�������е�i�ıߵ����ֵ
int to[V], cp[V], tag[V];
//to[i]����dis[i]�ķ����㣬cp[i]Ϊ�����������еĴ����,tag[i]�ڲ���2ʱ�õ�����iΪ����ĳ����tag[i] == -2,������tag[i] == i;����Ϊ�ж�tag[i]��tag[i] == -1

struct Edge { int u, v; typec c; } eg[E];

int iroot(int i){
	if (cp[i] == i) return i;
		return cp[i] = iroot(cp[i]);
}//

int dirtree(int root, int nv, int ne) // root: ����
{ // vertex: 0 ~ n-1
	int i, j, k, circle = 0;

	memset(tag, -1, sizeof(tag));
	memset(to, -1, sizeof(to));
	//����Ϊ����һ
	for (i = 0; i < nv; ++i) dis[i] = inf;
	for (j = 0; j < ne; ++j) {
		i = iroot(eg[j].u); k = iroot(eg[j].v);
		if (k != i && dis[k] > eg[j].c) {
			dis[k] = eg[j].c;
			to[k] = i;
		}	
	}
        //����Ϊ�����
	to[root] = -1; dis[root] = 0; tag[root] = root;
	for (i = 0; i < nv; ++i) if (cp[i] == i && -1 == tag[i]){
		j = i;
		for ( ; j != -1 && tag[j] == -1; j = to[j])
			tag[j] = i;
		if (j == -1) return 0;    //j== -1�����һ�������
		if (tag[j] == i) {
			circle = 1; tag[j] = -2;
			for (k = to[j]; k != j; k = to[k]) tag[k] = -2;
		}
	}
	//����Ϊ������
	if (circle) {
		for (j = 0; j < ne; ++j) {
			i = iroot(eg[j].u); k = iroot(eg[j].v);
			if (k != i && tag[k] == -2) eg[j].c -= dis[k];//���±�Ȩ
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
	return 1; // ������0����ԭͼ����ͨ
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
