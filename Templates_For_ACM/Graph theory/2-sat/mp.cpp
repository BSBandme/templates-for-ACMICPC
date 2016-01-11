//注意是编号是1base
namespace twosat {

const int maxm = 1010100;
const int maxn = 4010;
struct edge {
	int to, nxt;
} e[maxm];
int head[maxn], le;
int ans[maxn];
int n;
int st[maxn], lst, id[maxn], scnt, pre[maxn];
vi zu[maxn];

inline int gno(int no) {
	return no + n + 10;
}
inline int rno(int no) {
	return no - 10 - n;
}
void init(int n) {
	twosat::n = n;
	memset(head, -1, sizeof(head));
	le = 0;
	memset(ans, 0, sizeof(ans));
	lst = 0; scnt = 0;
	memset(pre, -1, sizeof(pre));
}
inline void addedge (int a, int b) {
	e[le].to = b;
	e[le].nxt = head[a];
	head[a] = le++;
}
// 反用负数表示
inline void addinvedge(int a, int b) {
	addedge(gno(a), gno(-b));
	addedge(gno(b), gno(-a));
}

void tarjan(int no, int rpre = 0) {
	st[lst++] = no;
	pre[no] = rpre;
	for(int i = head[no]; i != -1; i = e[i].nxt) {
		if(pre[e[i].to] == -1) tarjan(e[i].to, rpre + 1);
		pre[no] = min(pre[e[i].to], pre[no]);
	}
	if(pre[no] == rpre) {
		zu[scnt].clear();
		do {
			id[st[lst - 1]] = scnt;
			pre[st[lst - 1]] = n * 3;
			zu[scnt].push_back(st[lst - 1]);
			lst--;
		} while(lst && st[lst] != no);
		scnt++;
	}
}

bool solve() {
	for(int i = 1; i <= n; i++) {
		if(pre[gno(i)] == -1) tarjan(gno(i));
		if(pre[gno(-i)] == -1) tarjan(gno(-i));
	}
	for(int i = 1; i <= n; i++) if(id[gno(i)] == id[gno(-i)])
		return 0;
	int du[maxn];
	memset(du, 0, sizeof(du));
	vi fa[maxn];
	for(int i = 1; i <= n; i++) {
		for(int j = head[gno(i)]; j != -1; j = e[j].nxt) {
			if(id[gno(i)] != id[e[j].to])  {
				du[id[gno(i)]]++;
				fa[id[e[j].to]].push_back(id[gno(i)]);
			}
		}
		for(int j = head[gno(-i)]; j != -1; j = e[j].nxt) {
			if(id[gno(-i)] != id[e[j].to])  {
				du[id[gno(-i)]]++;
				fa[id[e[j].to]].push_back(id[gno(-i)]);
			}
		}
	}
	int q[maxn], lq = 0, rq = 0;
	for(int i = 0; i < scnt; i++) if(du[i] == 0)
		q[rq++] = i;

	for(; lq != rq; lq++) {
		bool flag = 1;
		for(int j = 0; j < (int)zu[q[lq]].size(); j++)
			if(ans[abs(rno(zu[q[lq]][j]))] != 0) flag = 0;
		if(!flag) continue;
		for(int j = 0; j < (int)zu[q[lq]].size(); j++) {
			int p = rno(zu[q[lq]][j]);
			ans[abs(p)] = p > 0 ? 1 : -1;
		}
		for(int j = 0; j < (int)fa[q[lq]].size(); j++) {
			du[fa[q[lq]][j]]--;
			if(du[fa[q[lq]][j]] == 0)
				q[rq++] = fa[q[lq]][j];
		}
	}

	return 1;
}

};
