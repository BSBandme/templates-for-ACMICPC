/*==================================================*\
| Tarjan 双联通分支（非双联通分量）
| INIT: stop, cnt, scnt置0; pre[]置-1;
| CALL: tarjan(0);
| thr返回割点，thr[i] == 1则为割点，id返回边的分支号
\*==================================================*/
const int V = 201000;
int id[V], pre[V], low[V], s[V], stop, cnt, scnt, dfsCounter;
int thr[V];

int n, m;
struct edge {
	int to, nxt;
} e[maxn];

void tarjan(int i, int fa = -1) {
	low[i] = pre[i] = dfsCounter ++;
	for(int j = head[i]; j != -1; j = e[j].nxt) if(e[j].to != fa){
		int to = e[j].to, ei = j / 2;
		if(pre[to] == -1) {
			s[stop++] = ei;
			tarjan(to, i);
			low[i] = min(low[i], low[to]);
			if(low[to] >= pre[i]) {
				if(pre[i] != 0 || j >= 1)
					thr[i] = 1;
				while(stop) {
					int fi = s[stop - 1]; stop--;
					id[fi] = scnt;
					if(fi == ei) break;
				}
				++ scnt;
			}
		} else if(pre[to] < pre[i]){
			low[i] = min(low[i], pre[to]);
			s[stop++] = ei;
		}
	}
}

