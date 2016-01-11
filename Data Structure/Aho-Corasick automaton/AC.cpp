const int maxn = 101010;
const int maxl = 30;
struct trie {
	int nxt[maxl];
	int val;
	void init() {
		memset(nxt, -1, sizeof(nxt));
		val = 0;
	}
} arr[maxn];
int larr;
map <char, int> mp;
inline void initmp() {
	for(char ch = 'a'; ch <= 'z'; ch++)
		mp[ch] = ch - 'a';
}
// 返回单词最后字母的那个节点的编号，处理val需在外面处理
inline int addword(string str) {
	int l = str.size(), no = 0;
	for(int i = 0; i < l; i++) {
		int nxt = arr[no].nxt[mp[str[i]]];
		if(nxt == -1) {
			arr[larr].init();
			nxt = arr[no].nxt[mp[str[i]]] = larr++;
		}
		no = nxt;
	}
	return no;
}
inline void addval(int no1, int no2) {
	arr[no1].val |= arr[no2].val;
}
inline void acbfs() {
	pii q[maxn];
	int lq = 0, rq = 0;
	for(int i = 0; i < maxl; i++) {
		if(arr[0].nxt[i] == -1) arr[0].nxt[i] = 0;
		else q[rq++] = mpr(arr[0].nxt[i], 0);
	}
	for(; lq != rq; lq++) {
		int now = q[lq].first, fail = q[lq].second;
		for(int i = 0; i < maxl; i++) {
			if(arr[now].nxt[i] == -1) arr[now].nxt[i] = arr[fail].nxt[i];
			else {
				q[rq++] = mpr(arr[now].nxt[i], arr[fail].nxt[i]);
				addval(arr[now].nxt[i], arr[fail].nxt[i]);
			}
		}
	}
}
