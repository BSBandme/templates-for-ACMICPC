const int maxn = 101000;
struct bset {
	ull num[maxn]; int l;
	bset(int a = 100000, ull orig = 0) : l(a) {
		num[0] = orig;
	}
	inline void init(int a) {
		l = a;
		for(int i = 0; i << 6 < l; i++) num[i] = 0;
	}
	inline void operator = (const int &a);
	inline void operator = (const ll &a);
	inline void operator = (const ull &a);
	inline void operator = (const bset &a);
	inline void operator |= (const bset &a);
	inline void operator &= (const bset &a);
	inline void operator ^= (const bset &a);
	inline bset operator | (const bset &a);
	inline bset operator & (const bset &a);
	inline bset operator ^ (const bset &a);
	inline bset operator << (const int &l);
	inline bset operator >> (const int &l);
	inline bool get(int loc);
	inline void set(int loc, int f);
	inline void output();
};

inline void bset :: operator = (const int &a) {
	num[0] = a;
}
inline void bset :: operator = (const ll &a) {
	num[0] = a;
}
inline void bset :: operator = (const ull &a) {
	num[0] = a;
}
inline void bset :: operator = (const bset &a) {
	l = a.l;
	for(int i = 0, link = 0; i < a.l; i += 64, link++)
		num[link] = a.num[link];
}
inline bset bset :: operator << (const int &l1) {
	bset ans(l);
	int have = l1 >> 6, last = l1 ^ (have << 6);
	for(int i = 0; i <= have; i++) ans.num[i] = 0;
	for(int i = have; i << 6 < l; i++) {
		ans.num[i] |= num[i - have] << last;
		ans.num[i + 1] = num[i - have] >> (64 - last);
	}
	return ans;
}
inline bset bset :: operator >> (const int &l1) {
	bset ans(l);
	int have = l1 >> 6, last = l1 ^ (have << 6);
	for(int i = have; i << 6 < l; i++) {
		ans.num[i - have] = num[i] >> last;
		ans.num[i - have] |= num[i + 1] << (64 - last);
	}
	int ff = l - l1;
	for(; ff & 63; ff++) ans.set(ff, 0);
	for(; ff < l; ff += 1 << 6) ans.num[ff >> 6] = 0;
	return ans;
}
// based 0
inline bool bset :: get(int loc) {
	int yu = (loc >> 6 << 6) ^ loc;
	return num[loc >> 6] & (1ull << yu);
}
// based 0
inline void bset :: set(int loc, int f) {
	int yu = (loc >> 6 << 6) ^ loc;
	if(f) {
		if(!(num[loc >> 6] & (1ull << yu)))
			num[loc >> 6] ^= 1ull << yu;
	}else if(num[loc >> 6] & (1ull << yu))
		num[loc >> 6] ^= 1ull << yu;
}
inline void bset :: operator |= (const bset &a) {
	for(int i = 0; i << 6 < l;  i++) num[i] |= a.num[i];
}
inline void bset :: operator &= (const bset &a) {
	for(int i = 0; i << 6 < l;  i++) num[i] &= a.num[i];
}
inline void bset :: operator ^= (const bset &a) {
	for(int i = 0; i << 6 < l;  i++) num[i] ^= a.num[i];
}
inline bset bset :: operator | (const bset &a) {
	bset ans(l);
	for(int i = 0; i << 6 < l;  i++) ans.num[i] = num[i] | a.num[i];
	return ans;
}
inline bset bset :: operator & (const bset &a) {
	bset ans(l);
	for(int i = 0; i << 6 < l;  i++) ans.num[i] = num[i] & a.num[i];
	return ans;
}
inline bset bset :: operator ^ (const bset &a) {
	bset ans(l);
	for(int i = 0; i << 6 < l;  i++) ans.num[i] = num[i] ^ a.num[i];
	return ans;
}
inline void bset :: output() {
	for(int i = 0; i < l; i++) if(get(i)) printf("1");
	else printf("0");
	printf("\n");
}
