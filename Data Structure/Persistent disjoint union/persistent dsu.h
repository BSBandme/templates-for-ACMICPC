// 仅可后退，若后退则后退前的记录均无，类似于栈
// 操作：
//    查询父亲： getfa(no) 
//    查询集合大小： arrfa[head_fa[getfa(no)]].second
//    合并： uni(no1, no2)
//    后退：把larrfa改到之前的时间点的larrfa即可

const int maxn = 200010;
pii arrfa[maxn * 18];
int larrfa;
int nxt[maxn * 18];
int belong[maxn * 18];
int head_fa[maxn];

inline void alloc(int no) {
	int rno = belong[larrfa];
	while(head_fa[rno] >= larrfa)
		head_fa[rno] = nxt[head_fa[rno]];
	nxt[larrfa] = head_fa[no];
	head_fa[no] = larrfa;
	belong[larrfa] = no;
	larrfa++;
}

int getfa(int no) {
	while(head_fa[no] >= larrfa)
		head_fa[no] = nxt[head_fa[no]];
	int rfa = arrfa[head_fa[no]].first;
	if(rfa == no) return no;
	int ans = getfa(rfa);
	if(ans != arrfa[head_fa[no]].first) {
		alloc(no);
		arrfa[head_fa[no]].first = ans;
	}
	return ans;
}

int uni(int a, int b) {
	a = getfa(a), b = getfa(b);
	ll rsz1 = arrfa[head_fa[a]].second, rsz2 = arrfa[head_fa[b]].second;
	if(rsz1 < rsz2) swap(a, b);
	if(a == b) return 0;
	alloc(b);
	arrfa[head_fa[b]].first = a;
	alloc(a);
	arrfa[head_fa[a]] = mpr(a, rsz1 + rsz2);

	return 1;
}
