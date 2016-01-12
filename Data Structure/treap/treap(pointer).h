const int maxn = 230100;
#define treap_type int
struct treap_node {
	treap_node *left, *right, *fa;
	int sz, ge;
	int prio;
	treap_type val;
};
treap_node treap_arr[maxn];
int treap_head = 0, maxl = 0;
int nxt[maxn];
struct treap {
	int sz; treap_node *root;

	treap() {
		srand(unsigned (time(NULL)));
		root = NULL;
		sz = 0;
	}
	inline int rannum() {
		return (rand() << 15) + rand();
	}
	// ranrank > sz时返回最大的那个指针
	treap_node * getrank(int ranrank, treap_node *no = NULL) {
		if(no == NULL) no = root;
		treap_node *left = no->left, *right = no->right;
		if(left != NULL && ranrank <= left->sz)
			return getrank(ranrank, left);
		if(left != NULL) ranrank -= left->sz;
		ranrank -= no->ge;
		if(ranrank <= 0 || no->right == NULL) return no;
		return getrank(ranrank, right);
	}
	int getnotbig(treap_type val, treap_node *no = NULL) {
		if(sz == 0) return 0;
		if(no == NULL) no = root;
		treap_node *left = no->left, *right = no->right;
		if(no->val == val) {
			if(left != NULL) return no->ge + left->sz;
			return no->ge;
		}
		if(no->val > val) {
			if(left != NULL) return getnotbig(val, left);
			return 0;
		} else {
			if(right != NULL) return getnotbig(val, right) + no->sz - right->sz;
			return no->sz;
		}
	}
    inline void relaxfa(treap_node *no) {
    	treap_node *fa = no->fa;
        if(no->fa == NULL) return;
        if(fa->val > no->val) fa->left = no;
        else fa->right = no;
    }
	inline void relax(treap_node *no) {
		no->sz = no->ge;
		if(no->left != NULL) no->sz += no->left->sz;
		if(no->right != NULL) no->sz += no->right->sz;
	}
    inline void relaxtofa(treap_node *no) {
        while(no != NULL) {
            relax(no);
            root = no;
            no = no->fa;
        }
    }
    inline void right_rot(treap_node *no) {
    	treap_node *fa = no->fa;
        no->fa = fa->fa;
        fa->left = no->right;
        if(no->right != NULL) no->right->fa = fa;
        no->right = fa;
        fa->fa = no;
        relax(fa);
        relaxfa(no);
        relax(no);
    }
    inline void left_rot(treap_node *no) {
    	treap_node *fa = no->fa;
        no->fa = fa->fa;
        fa->right = no->left;
        if(no->left != NULL) no->left->fa = fa;
        no->left = fa;
        fa->fa = no;
        relax(fa);
        relaxfa(no);
        relax(no);
    }
	void insert(treap_type val) {
    	treap_node *rt = treap_arr + treap_head;

        int ranmaxl = maxl;
        sz++;
        rt->prio = rannum();
        rt->left = rt->right = rt->fa = NULL;
        if(treap_head == maxl) {
            maxl++;
            nxt[treap_head] = maxl;
        }
		rt->val = val;
		if(sz == 1) {
			root = rt;
			rt->sz = 1;
			rt->ge = 1;
			treap_head = nxt[treap_head];
			return;
		}
        treap_node *no = root;
        while(no != NULL) {
            if(no->val == rt->val) break;
            rt->fa = no;
            if(no->val < rt->val) no = no->right;
            else no = no->left;
        }
		if(no != NULL) {
			no->ge++;
			maxl = ranmaxl;
			relaxtofa(no);
			return;
		}
		rt->ge = 1; rt->sz = 1;
        if(rt->val < rt->fa->val) rt->fa->left = rt;
        else rt->fa->right = rt;
        while(rt->fa != NULL && rt->prio > rt->fa->prio) {
            if(rt->val < rt->fa->val) right_rot(rt);
            else left_rot(rt);
        }
        if(rt->fa == NULL) root = rt;
        relaxtofa(rt);
        treap_head = nxt[treap_head];
	}
	void del(treap_type val) {
		if(sz == 0) return;
		treap_node *no = root;
		while(no != NULL) {
			if(no->val == val) break;
			if(no->val > val) no = no->left;
			else no = no->right;
		}
		if(no == NULL) return;
		sz--;
		if(sz == 0) {
			nxt[root - treap_arr] = treap_head;
			treap_head = root - treap_arr;
			root = NULL;
			sz = 0;
			return;
		}
		no->ge--;
		if(no->ge != 0){
			relaxtofa(no);
			return;
		}
		while(no->left != NULL || no->right != NULL) {
			if(no->left == NULL) left_rot(no->right);
			else {
				if(no->right == NULL || no->left->prio > no->right->prio) right_rot(no->left);
				else left_rot(no->right);
			}
		}
		int no1 = no - treap_arr;
		if(no->fa->left == no)
			no->fa->left = NULL;
		else no->fa->right = NULL;
		relaxtofa(no->fa);
		nxt[no1] = treap_head;
		treap_head = no1;
	}
} tp;

