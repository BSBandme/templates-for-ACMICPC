const int maxn = 100100;
struct edge {
	int to, nxt;
} e[maxn * 2];
int le, head[maxn];
inline void addedge(int a, int b) {
	e[le].to = b;
	e[le].nxt = head[a];
	head[a] = le++;
}
int cant[maxn], sz[maxn], deep[maxn];
int arr[maxn], larr = 0;
int n;

// other
// end

void dfssz(int no, int fa = -1) {
	sz[no] = 1;
	for(int i = head[no]; i != -1; i = e[i].nxt) if(e[i].to != fa && !cant[e[i].to]) {
		dfssz(e[i].to, no);
		sz[no] += sz[e[i].to];
	}
}
void dfsinit(int no, int fa, int *arr, int &larr) {
	arr[larr++] = no;
	if(fa == -1) deep[no] = 0;
	else deep[no] = deep[fa] + 1;
	sz[no] = 1;
	for(int i = head[no]; i != -1; i = e[i].nxt) if(e[i].to != fa && !cant[e[i].to]) {
		dfsinit(e[i].to, no, arr, larr);
		sz[no] += sz[e[i].to];
	}
}
pii dfscore(int no, int fa, int root) {
	pii ans = mpr(n, -1);
	int maxsz = sz[root] - sz[no];
	for(int i = head[no]; i != -1; i = e[i].nxt) if(e[i].to != fa && !cant[e[i].to]) {
		ans = min(ans, dfscore(e[i].to, no, root));
		maxsz = max(maxsz, sz[e[i].to]);
	}
	if(maxsz < ans.first) ans = mpr(maxsz, no);
	return ans;
}

void justdoit(int no) {
	dfssz(no);
	int core = dfscore(no, -1, no).second;
	cant[core] = 1;

	//todo

	//end
	for(int i = head[core]; i != -1; i = e[i].nxt) if(!cant[e[i].to]) {
		justdoit(e[i].to);
		// todo

		// end
	}
	cant[core] = 0;
	larr = 0;
	dfsinit(core, -1, arr, larr);
	//todo
	larr = 0;
	dfsinit(no, -1, arr, larr);

	//end
}
