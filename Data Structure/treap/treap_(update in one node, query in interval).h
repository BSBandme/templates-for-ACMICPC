// key type:　int, value type: pii
// 区间询问最大值getmax(l, r), 最小值getmin(l, r)
const int maxn = 3000100;
int zong = 0;
#define treap_type pair <int, pii>
struct treap_node {
	int left, right, sz, fa, ge;
	double prio;
	treap_type val;
	pii maxv, minv;
	pii range;
};
treap_node treap_arr[maxn];
int treap_head = 0, maxl = 0;
int nxt[maxn];
struct treap {
	int sz, root;
	unsigned int prea, preb;

	treap() {
		srand(unsigned (time(NULL)));
		root = -1;
		sz = 0;
		prea = preb = 1;
	}
	inline double rannum() {
		prea = prea * rand() % 32761 + 1;
		preb = preb * rand() % 32761 + 1;
		return 1.0 * prea / preb;
	}
	// ranrank > sz时返回最大的那个指针
	treap_node * getrank(int ranrank, int no = -1) {
		if(no == -1) no = root;
		if(treap_arr[no].left != -1 && ranrank <= treap_arr[treap_arr[no].left].sz)
			return getrank(ranrank, treap_arr[no].left);
		if(treap_arr[no].left != -1) ranrank -= treap_arr[treap_arr[no].left].sz;
		ranrank -= treap_arr[no].ge;
		if(ranrank <= 0 || treap_arr[no].right == -1) return treap_arr + no;
		return getrank(ranrank, treap_arr[no].right);
	}
	int getnotbig(treap_type val, int no = -1) {
		if(sz == 0) return 0;
		if(no == -1) no = root;
		if(treap_arr[no].val == val) {
			if(treap_arr[no].left != -1) return treap_arr[no].ge + treap_arr[treap_arr[no].left].sz;
			return treap_arr[no].ge;
		}
		if(treap_arr[no].val > val) {
			if(treap_arr[no].left != -1) return getnotbig(val, treap_arr[no].left);
			return 0;
		}else {
			if(treap_arr[no].right != -1) return getnotbig(val, treap_arr[no].right) + treap_arr[no].sz - treap_arr[treap_arr[no].right].sz;
			return treap_arr[no].sz;
		}
	}
	pii getmax(int l, int r, int no = -1) {
		if(no == -1) no = root;
		if(treap_arr[no].range.first >= l && treap_arr[no].range.second <= r)
			return treap_arr[no].maxv;
		pii ans = mpr(-1, -1);
		if(treap_arr[no].val.first >= l && treap_arr[no].val.first <= r)
			ans = max(ans, treap_arr[no].val.second);
		if(treap_arr[no].left != -1) {
			if(treap_arr[treap_arr[no].left].range.first <= r && treap_arr[treap_arr[no].left].range.second >= l)
				ans = max(ans, getmax(l, r, treap_arr[no].left));
		}
		if(treap_arr[no].right != -1) {
			if(treap_arr[treap_arr[no].right].range.first <= r && treap_arr[treap_arr[no].right].range.second >= l)
				ans = max(ans, getmax(l, r, treap_arr[no].right));
		}
		return ans;
	}
	pii getmin(int l, int r, int no = -1) {
		zong++;
		if(no == -1)
			no = root;
		if(treap_arr[no].range.first >= l && treap_arr[no].range.second <= r) {
//			cerr << treap_arr[no].minv.second << ' ' << no << ' ' << root << endl;
			return treap_arr[no].minv;
		}
		pii ans = mpr(MOD, MOD);
		if(treap_arr[no].val.first >= l && treap_arr[no].val.first <= r)
			ans = min(ans, treap_arr[no].val.second);
		if(treap_arr[no].left != -1) {
			if(treap_arr[treap_arr[no].left].range.first <= r && treap_arr[treap_arr[no].left].range.second >= l)
				ans = min(ans, getmin(l, r, treap_arr[no].left));
		}
		if(treap_arr[no].right != -1) {
			if(treap_arr[treap_arr[no].right].range.first <= r && treap_arr[treap_arr[no].right].range.second >= l)
				ans = min(ans, getmin(l, r, treap_arr[no].right));
		}
		return ans;
	}
	inline void relaxfa(int no) {
		if(treap_arr[no].fa == -1) return;
		if(treap_arr[treap_arr[no].fa].val > treap_arr[no].val) treap_arr[treap_arr[no].fa].left = no;
		else treap_arr[treap_arr[no].fa].right = no;
	}
	inline void relax(int no) {
		treap_arr[no].sz = treap_arr[no].ge;
		treap_arr[no].maxv = treap_arr[no].minv = treap_arr[no].val.second;
		treap_arr[no].range = mpr(treap_arr[no].val.first, treap_arr[no].val.first);
		if(treap_arr[no].left != -1) {
			treap_arr[no].sz += treap_arr[treap_arr[no].left].sz;
			treap_arr[no].maxv = max(treap_arr[treap_arr[no].left].maxv, treap_arr[no].maxv);
			treap_arr[no].minv = min(treap_arr[treap_arr[no].left].minv, treap_arr[no].minv);
			treap_arr[no].range.first = treap_arr[treap_arr[no].left].range.first;
		}
		if(treap_arr[no].right != -1) {
			treap_arr[no].sz += treap_arr[treap_arr[no].right].sz;
			treap_arr[no].maxv = max(treap_arr[treap_arr[no].right].maxv, treap_arr[no].maxv);
			treap_arr[no].minv = min(treap_arr[treap_arr[no].right].minv, treap_arr[no].minv);
			treap_arr[no].range.second = treap_arr[treap_arr[no].right].range.second;
		}
	}
	inline void relaxtofa(int no) {
		while(no != -1) {
			relax(no);
			root = no;
			no = treap_arr[no].fa;
		}
	}
	inline void right_rot(int no) {
		int fa = treap_arr[no].fa;
		treap_arr[no].fa = treap_arr[fa].fa;
		treap_arr[fa].left = treap_arr[no].right;
		if(treap_arr[no].right != -1) treap_arr[treap_arr[no].right].fa = fa;
		treap_arr[no].right = fa;
		treap_arr[fa].fa = no;
		relax(fa);
		relaxfa(no);
		relax(no);
	}
	inline void left_rot(int no) {
		int fa = treap_arr[no].fa;
		treap_arr[no].fa = treap_arr[fa].fa;
		treap_arr[fa].right = treap_arr[no].left;
		if(treap_arr[no].left != -1) treap_arr[treap_arr[no].left].fa = fa;
		treap_arr[no].left = fa;
		treap_arr[fa].fa = no;
		relax(fa);
		relaxfa(no);
		relax(no);
	}
	void insert(treap_type val) {
		zong++;
		int ranmaxl = maxl;
		sz++;
		treap_arr[treap_head].prio = rannum();
		treap_arr[treap_head].left = treap_arr[treap_head].right = treap_arr[treap_head].fa = -1;
		if(treap_head == maxl) {
			maxl++;
			nxt[treap_head] = maxl;
		}
		treap_arr[treap_head].val = val;
		treap_arr[treap_head].maxv = val.second;
		treap_arr[treap_head].minv = val.second;
		treap_arr[treap_head].range = mpr(val.first, val.first);
		if(sz == 1) {
			root = treap_head;
			treap_arr[treap_head].sz = 1;
			treap_arr[treap_head].ge = 1;
			treap_head = nxt[treap_head];
			return;
		}
		int no = root;
		while(no != -1) {
			if(treap_arr[no].val == treap_arr[treap_head].val) break;
			treap_arr[treap_head].fa = no;
			if(treap_arr[no].val < treap_arr[treap_head].val) no = treap_arr[no].right;
			else no = treap_arr[no].left;
		}
		if(no != -1) {
			treap_arr[no].ge++;
			maxl = ranmaxl;
			relaxtofa(no);
			return;
		}
		treap_arr[treap_head].ge = 1; treap_arr[treap_head].sz = 1;
		if(treap_arr[treap_head].val < treap_arr[treap_arr[treap_head].fa].val) treap_arr[treap_arr[treap_head].fa].left = treap_head;
		else treap_arr[treap_arr[treap_head].fa].right = treap_head;
		while(treap_arr[treap_head].fa != -1 && treap_arr[treap_head].prio > treap_arr[treap_arr[treap_head].fa].prio) {
			if(treap_arr[treap_head].val < treap_arr[treap_arr[treap_head].fa].val) right_rot(treap_head);
			else left_rot(treap_head);
		}
		if(treap_arr[treap_head].fa == -1) root = treap_head;
		relaxtofa(treap_head);
		treap_head = nxt[treap_head];
	}
	void del(treap_type val) {
		if(sz == 0) return;
		int no = root;
		while(no != -1) {
			if(treap_arr[no].val == val) break;
			if(treap_arr[no].val > val) no = treap_arr[no].left;
			else no = treap_arr[no].right;
		}
		if(no == -1) return;
		sz--;
		if(sz == 0) {
			nxt[root] = treap_head;
			treap_head = root;
			root = -1;
			sz = 0;
			return;
		}
		treap_arr[no].ge--;
		if(treap_arr[no].ge != 0){
			relaxtofa(no);
			return;
		}
		while(treap_arr[no].left != -1 || treap_arr[no].right != -1) {
			if(treap_arr[no].left == -1) left_rot(treap_arr[no].right);
			else {
				if(treap_arr[no].right == -1 || treap_arr[treap_arr[no].left].prio > treap_arr[treap_arr[no].right].prio) right_rot(treap_arr[no].left);
				else left_rot(treap_arr[no].right);
			}
		}
		int no1 = no;
		if(treap_arr[treap_arr[no].fa].left == no) treap_arr[treap_arr[no].fa].left = -1;
		else treap_arr[treap_arr[no].fa].right = -1;
		relaxtofa(treap_arr[no].fa);
		nxt[no1] = treap_head;
		treap_head = no1;
	}
};

