/*
 * temp.cpp
 *
 *  Created on: 2012-7-18
 *      Author: BSBandme
 */
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cassert>
#include <iomanip>
#include <math.h>
#include <deque>
#include <utility>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <climits>
#include <cctype>
#include <cmath>
#include <cstdlib>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pll;
const double pi = acos(0) * 2;
template <class T> inline T abs1(T a) {return a < 0 ? -a : a;}
template <class T> inline T max1(T a, T b) {return a > b ? a : b;}
template <class T> inline T min1(T a, T b) {return a < b ? a : b;}
template <class T> inline T gcd1(T a, T b) {
	if(a < b) swap(a, b);
	if(a % b == 0) return b;
	return gcd1(b, a % b);
}
template <class T> inline T lb(T num) {return num & (-num); }
template <class T> inline int bitnum(T num){
	int ans = 0;
	while(num){
		num -= lb(num);
		ans++;
	}
	return ans;
}
long long pow(long long n, long long m, long long mod = 0){
	long long ans = 1;
	long long k = n;
	while(m){
		if(m & 1) {
			ans *= k;
			if(mod) ans %= mod;
		}
		k *= k;
		if(mod) k %= mod;
		m >>= 1;
	}
	return ans;
}

const int maxn = 1000;

struct tree{
	int n; // 节点个数
	int root; // 根节点
	int fa[maxn]; // fa为父节点
	int son_head[maxn], son_nxt[maxn]; // 此为儿子节点，用链表存储
	int size[maxn], hv[maxn]; // size为每个节点的大小， hv为每个节点的重儿子
	int level[maxn]; // level为每个节点的深度

	inline tree(){
		n = 0;
		memset(fa, -1, sizeof(fa));
		memset(son_head, -1, sizeof(son_head));
		memset(hv, -1, sizeof(hv));
		memset(level, -1, sizeof(level));
		memset(size, 0, sizeof(size));
	}
	inline tree operator = (const tree *a){
		tree a1;
		a1.n = a->n;
		a1.root = a->root;
		memcpy(a1.fa, a->fa, sizeof(a->fa));
		memcpy(a1.son_head, a->son_head, sizeof(a->son_head));
		memcpy(a1.son_nxt, a->son_nxt, sizeof(a->son_nxt));
		memcpy(a1.size, a->size, sizeof(a->size));
		memcpy(a1.hv, a->hv, sizeof(a->hv));
		memcpy(a1.level, a->level, sizeof(a->level));
		return a1;
	}
	//tree_init_edge为将fa数组转化为链表
	void tree_init_edge(){
		for(int i = 0; i < n; i++){
			if(fa[i] == -1) continue;
			son_nxt[i] = son_head[fa[i]];
			son_head[fa[i]] = i;
		}
	}
	//dfs主要是为了算出hv, size, level
	void dfs(int no, int ranlevel = 0){
		int rans = 0;
		level[no] = ranlevel;
		size[no] = 1;
		for(int i = son_head[no]; i != -1; i = son_nxt[i]){
			dfs(i, ranlevel + 1);
			if(size[i] > rans) { hv[no] = i; rans = size[i]; }
			size[no] += size[i];
		}
	}
};

struct LCA{
	tree t;
	//a，a1为lca转化为rmq的数组，la为a的长度，
	//st、st1为rmq-st中的st数组，wh[i]代表节点i在a或a1中最后一次出现的位置
	int a[maxn], st[maxn][25], d[30], la, wh[maxn], a1[maxn], st1[maxn][25];

	//dfs为算出a,a1,wh
	void dfs(int no){
		a[la] = t.level[no];
		a1[la++] = no;
		for(int i = t.son_head[no]; i != -1; i = t.son_nxt[i]){
			dfs(i);
			a[la] = t.level[no];
			a1[la++] = no;
		}
		wh[no] = la - 1;
	}
	void InitRMQ(const int &n){
		int i, j;
		for( d[0]=1, i=1; i < 25; ++i ) d[i] = 2*d[i - 1];
		for( i=0; i < n; ++i ){
			st[i][0] = a[i];
			st1[i][0] = a1[i];
		}
		int k = int( log(double(n))/log(2) ) + 1;
		for( j=1; j < k; ++j )
			for( i=0; i < n; ++i ){
				if( i+d[j-1]-1 < n ){
					st1[i][j] = t.level[st1[i][j-1]] < t.level[st1[i + d[j-1]][j-1]] ? st1[i][j-1] : st1[i + d[j-1]][j-1];
					st[i][j] = t.level[st1[i][j]];
				}
				else break; // st[i][j] = st[i][j-1];
		}
	}
	inline LCA(tree *t1 = NULL){
		if(t1 != NULL){
			t = *t1;
			dfs(t.root);
			InitRMQ(la);
		}
	}
	//que_val为询问两点之间最小值, que_no为询问两点之间最小值的节点号
	inline int que_val(int x, int y){
		if(x > y) swap(x, y);
		int k = int(log(double(y - x + 1)) / log(2.0) );
		return max1(st[x][k], st[y - d[k] + 1][k]);
	}
	inline int que_no(int x, int y){
		if(x > y) swap(x, y);
		int k = int(log(double(y - x + 1)) / log(2.0) );
		return t.level[st1[x][k]] < t.level[st1[y - d[k] + 1][k]] ? st1[x][k] : st1[y - d[k] + 1][k];
	}
	inline int lcaque(int x, int y){
		return que_no(wh[x], wh[y]);
	}
};

template <class t> struct segment_node{
	int be, en;
	t maxv, add, sum;
};
template <class t> struct segment_tree{
	int l;
	segment_node <t> tree[maxn * 4];

	inline int gleft(int no) {return no << 1;}
	inline int gright(int no) {return (no << 1) + 1;}
	inline int gfa(int no) {return no >> 1;}
	inline segment_tree(){ l = 0; }

	void build(int no, int l, int r, t orig = 0, t *a = NULL){
		if(l > r) r = l;
		if(l == r){
			tree[no].be = tree[no].en = l;
			tree[no].add = 0;
			if(a == NULL) tree[no].maxv = orig;
			else tree[no].maxv = a[l];
			tree[no].add = 0;
			tree[no].sum = tree[no].maxv;
			return;
		}
		tree[no].be = l; tree[no].en = r;
		int mid = (l + r) / 2;
		build(gleft(no), l, mid, orig, a);
		build(gright(no), mid + 1, r, orig, a);
		tree[no].sum = tree[gleft(no)].sum + tree[gright(no)].sum;
		tree[no].add = 0;
		tree[no].maxv = max1(tree[gleft(no)].maxv, tree[gright(no)].maxv);
	}
	inline void relax(int no) {
		tree[gleft(no)].add += tree[no].add;
		tree[gleft(no)].sum += tree[no].add * (tree[gleft(no)].en - tree[gleft(no)].be + 1);
		tree[gleft(no)].maxv += tree[no].add;
		tree[gright(no)].add += tree[no].add;
		tree[gright(no)].sum += tree[no].add * (tree[gright(no)].en - tree[gright(no)].be + 1);
		tree[gright(no)].maxv += tree[no].add;
		tree[no].add = 0;
	}
	void down(int l, int r, int no, t ranadd){
		if(l <= tree[no].be && r >= tree[no].en){
			tree[no].add += ranadd;
			tree[no].sum += ranadd * (tree[no].en - tree[no].be + 1);
			tree[no].maxv += ranadd;
			return;
		}
		if(tree[no].add && tree[no].be != tree[no].en) relax(no);
		int mid = (tree[no].be + tree[no].en) / 2;
		if(r >= tree[no].be && l <= mid) down(l, r, gleft(no), ranadd);
		if(r >= mid + 1 && l <= tree[no].en) down(l, r, gright(no), ranadd);
		tree[no].sum = tree[gleft(no)].sum + tree[gright(no)].sum;
		tree[no].maxv = max1(tree[gleft(no)].maxv, tree[gright(no)].maxv);
	}
	t getsum(int l, int r, int no){
		if(l > r) return 0;
		if(l <= tree[no].be && r >= tree[no].en)
			return tree[no].sum;
		if(tree[no].add && tree[no].be != tree[no].en) relax(no);
		t ans = 0;
		int mid = (tree[no].be + tree[no].en) / 2;
		if(r >= tree[no].be && l <= mid) ans += getsum(max1(l, tree[no].be), min1(r, mid), gleft(no));
		if(r >= mid + 1 && l <= tree[no].en) ans += getsum(max1(l, mid + 1), min1(r, tree[no].en), gright(no));
		return ans;
	}
	int getrank(int rank, int no){
		if(rank > tree[no].sum) return -1;
		if(tree[no].be == tree[no].en) return tree[no].be;
		if(tree[no].add && tree[no].be != tree[no].en) relax(no);
		int mid = (tree[no].be + tree[no].en) / 2;
		if(rank <= tree[gleft(no)].sum) return getrank(rank, gleft(no));
		return getrank(rank - tree[gleft(no)].sum, gright(no));
	}
	inline int section_getrank(int l, int r, int rank){
		return getrank(rank + getsum(0, l - 1, 1), 1);
	}
};

template <class T> struct tree_chain{
	tree t;
	LCA lca;
	segment_tree <T> tre;
	int loc[maxn], nloc, chain[maxn], nchain, head_chain[maxn], antiloc[maxn];

	//为算出节点在线段树上的位置
	void dfs(int no, int nochain = 0){
		loc[no] = nloc++;
		chain[no] = nochain;
		if(t.hv[no] != -1) dfs(t.hv[no], nochain);
		for(int i = t.son_head[no]; i != -1; i = t.son_nxt[i]){
			if(i == t.hv[no]) continue;
			head_chain[++nchain] = i;
			dfs(i, nchain);
		}
	}
	//给l节点与r节点之间的节点加ranadd
	void upd(int l, int r, T ranadd){
		int anc = lca.lcaque(l, r);
		int f = 0;
		for(int i = l; t.level[i] > t.level[anc];){
			int nxt = head_chain[chain[i]];
			if(t.level[nxt] <= t.level[anc]) nxt = anc;
			tre.down(loc[nxt], loc[i] , 1, ranadd);
			i = t.fa[nxt];
			if(i == t.fa[anc]) f++;
		}
		for(int i = r; t.level[i] > t.level[anc];){
			int nxt = head_chain[chain[i]];
			if(t.level[nxt] <= t.level[anc]) nxt = anc;
			tre.down(loc[nxt], loc[i] , 1, ranadd);
			i = t.fa[nxt];
			if(i == t.fa[anc]) f++;
		}
		if(f == 2) tre.down(loc[anc], loc[anc], 1, -ranadd);
	}
	//求l至r的和
	T getsum(int l, int r){
		int anc = lca.lcaque(l, r);
		int f = 0;
		T ans = 0;
		for(int i = l; t.level[i] > t.level[anc];){
			int nxt = head_chain[chain[i]];
			if(t.level[nxt] <= t.level[anc]) nxt = anc;
			ans += tre.getsum(loc[nxt], loc[i], 1);
			i = t.fa[nxt];
			if(i == t.fa[anc]) f++;
		}
		for(int i = r; t.level[i] > t.level[anc];){
			int nxt = head_chain[chain[i]];
			if(t.level[nxt] <= t.level[anc]) nxt = anc;
			ans += tre.getsum(loc[nxt], loc[i], 1);
			i = t.fa[nxt];
			if(i == t.fa[anc]) f++;
		}
		if(f == 2) ans -= tre.getsum(loc[anc], loc[anc], 1);
		return ans;
	}
	int section_getrank(int l, int r, T rank){
		T all = getsum(l, r);
		if(all < rank) return -1;
		int anc = lca.lcaque(l, r);
		for(int i = l, rrank = 0; t.level[i] > t.level[anc];){
			int nxt = head_chain[chain[i]];
			if(t.level[nxt] <= t.level[anc]) nxt = anc;
			rrank += tre.getsum(loc[nxt], loc[i], 1);
			if(rrank >= rank)
				return antiloc[tre.section_getrank(loc[nxt], loc[i], rrank - rank + 1)];
			i = t.fa[nxt];
		}
		rank = all - rank + 1;
		for(int i = r, rrank = 0; t.level[i] > t.level[anc];){
			int nxt = head_chain[chain[i]];
			if(t.level[nxt] <= t.level[anc]) nxt = anc;
			rrank += tre.getsum(loc[nxt], loc[i], 1);
			if(rrank >= rank)
				return antiloc[tre.section_getrank(loc[nxt], loc[i], rrank - rank + 1)];
			i = t.fa[nxt];
		}
		return 0;
	}
	tree_chain(tree t1, int *a = NULL){
		t = t1;
		lca.t = t;
		lca.dfs(t.root);
		lca.InitRMQ(lca.la);
		head_chain[0] = t.root;
		dfs(t.root);
		nchain++;
		if(a == NULL) tre.build(1, 0, t.n - 1, 1);
		else {
			int a1[maxn];
			for(int i = 0; i < t.n; i++) a1[loc[i]] = a[i];
			tre.build(1, 0, t.n - 1, 1, a1);
		}
		for(int i = 0; i < t.n; i++) antiloc[loc[i]] = i;
	}
};

int main(){
	freopen("input.txt","r", stdin);
	tree tt;
	scanf("%d", &tt.n);
	for(int i = 0; i < tt.n; i++){
		scanf("%d", tt.fa + i);
		tt.fa[i]--;
		if(tt.fa[i] == -1) tt.root = i;
	}
	tt.tree_init_edge();
	tt.dfs(tt.root);
	tree_chain <int> tc(tt);


	return 0;
}



