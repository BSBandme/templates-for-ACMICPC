#ifndef N
#define N 200100
#endif
template <class t> struct segment_node{
	int be, en;
	t maxv, add, sum;
};
template <class t> struct segment_tree{
	int l;
	segment_node <t> tree[N * 4];

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
		int le = gleft(no), ri = gright(no);
		tree[le].add += tree[no].add;
		tree[le].sum += tree[no].add * (tree[le].en - tree[le].be + 1);
		tree[le].maxv += tree[no].add;
		tree[ri].add += tree[no].add;
		tree[ri].sum += tree[no].add * (tree[ri].en - tree[ri].be + 1);
		tree[ri].maxv += tree[no].add;
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
		int mid = (tree[no].be + tree[no].en) >> 1;
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
		int mid = (tree[no].be + tree[no].en) >> 1;
		if(r >= tree[no].be && l <= mid) ans += getsum(l, r, gleft(no));
		if(r >= mid + 1 && l <= tree[no].en) ans += getsum(l, r, gright(no));
		return ans;
	}
	int getrank(int rank, int no){
		if(rank > tree[no].sum) return -1;
		if(tree[no].be == tree[no].en) return tree[no].be;
		if(tree[no].add && tree[no].be != tree[no].en) relax(no);
		int mid = (tree[no].be + tree[no].en) >> 1;
		if(rank <= tree[gleft(no)].sum) return getrank(rank, gleft(no));
		return getrank(rank - tree[gleft(no)].sum, gright(no));
	}
	inline int section_getrank(int l, int r, int rank){
		return getrank(rank + getsum(0, l - 1, 1), 1);
	}
};

