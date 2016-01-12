int fa[maxn][22], deep[maxn];

inline void initfa() {
	for(int i = 1; i <= 20; i++) {
		for(int j = 0; j < n; j++) {
			if(fa[j][i - 1] == -1) fa[j][i] = -1;
			else fa[j][i] = fa[fa[j][i - 1]][i - 1];
		}
	}
}
inline int getfa(int no, int l) {
	for(int i = 0; l; l >>= 1, i++)
		if(l & 1) no = fa[no][i];
	return no;
}
inline int getlca(int a, int b) {
	if(deep[a] > deep[b]) swap(a, b);
	b = getfa(b, deep[b] - deep[a]);
	if(b == a) return a;
	for(int i = 20; i >= 0; i--)
		if(fa[a][i] != fa[b][i]){
			a = fa[a][i];
			b = fa[b][i];
		}
	return fa[a][0];
}
inline int getl(int a, int b) {
	int faa = getlca(a, b);
	return deep[a] + deep[b] - deep[faa] * 2;
}

