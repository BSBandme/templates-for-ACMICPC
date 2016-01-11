// hpfdf
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <iomanip>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<(n);++i)
#define fab(i,a,b) for(int i=(a);i<=(b);++i)
#define fba(i,b,a) for(int i=(b);i>=(a);--i)
#define clr(a) memset(a,0,sizeof(a))
#define fec(i,a) for(__typeof((a).end())i=(a).begin();i!=(a).end();++i)
#define fpc(i,j,v) for(int i=a[v],j;j=to[i],i;i=nx[i])

#define N 1111111

char s[N], t[N];


struct sanode {
	sanode *f, *ch[26];
	int l, nl, ml;
	ll ct;
}pool[N*2 + 18], *init = pool, *tail = pool, *p[N*2 + 18];

int n, tot, l;

void add(int c)
{
	sanode *q = pool + (++tot), *p = tail;
	memset(q, 0, sizeof(sanode));
	q->l = q->ml = p->l + 1; q->nl = 0; q->ct = -1;
	tail = q;
	while (p && !p->ch[c]) p->ch[c] = q, p = p->f;
	if (!p) q->f = init;
	else
		if (p->ch[c]->l == p->l + 1) q->f = p->ch[c];
		else {
			sanode *r = pool + (++tot), *u = p->ch[c];
			memcpy(r->ch, u->ch, sizeof(size_t)*26); r->nl = 0; r->ct = -1;
			r->l = r->ml = p->l + 1, r->f = u->f;
			u->f = q->f = r;
			while (p && p->ch[c] == u) p->ch[c] = r, p = p->f;
		}
}

void dfs(sanode * v)
{
	if (v->ct >= 0) return;
	if (v->ct == -1)
		v->ct = 0;
	else
		v->ct = 1;
	for (int i=0; i < 26; ++i)
		if (v->ch[i])
		{
			dfs(v->ch[i]);
			v->ct += v->ch[i]->ct;
		}
}

int main()
{
	scanf("%s", s);

	l = strlen(s);

	init->ct = -1;

	rep(i,l) add(s[i] - 'a');

	sanode *pp = tail;
	while (pp)
	{
		pp->ct = -2;
		pp = pp->f;
	}

	dfs(init);

	scanf("%d", &n);

	fab(ii,1,n)
	{
		scanf("%s", t);
		int m = strlen(t);

		sanode *a = init;
		int ret = 0;
		for (int i = 0, nl = 0; i < m*2; ++i)
		{
			int c = t[i<m?i:i-m] - 'a';
			if (a->ch[c])
			{
				a = a->ch[c], ++nl;
			}
			else
			{
				while (a && !a->ch[c]) a = a->f;
				if (a)
				{
					nl = a->l + 1, a = a->ch[c];
				}
				else
					a = init, nl = 0;
			}
			if (nl >= m)
			{
				if (a->f)
				while (a->f->l >= m)
					a = a->f, nl = a->l;

				if (a->nl != ii)
				{
					a->nl = ii;
					ret += a->ct;
				}
			}
		}

		printf("%d\n", ret);
	}

	return 0;
}
