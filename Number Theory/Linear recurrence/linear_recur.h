const int yu = 350;
template <class t>
struct linear_recur {
	t mod;
	int jie;
	int mat[70][yu * 2];
	//xi[i] is the coefficient of f(n - 1 - i) 
	void init(vector <t> xi, ll maxn = -1, t rmod = -1) {
		memset(mat, 0, sizeof(mat));
		jie = xi.size();
		for(int i = 0; i < jie; i++) mat[0][i] = xi[i];
		if(rmod != -1) mod = rmod;
		else mod = 1000000007;
		int k = 62;
		if(maxn != -1) k = bitmaxl(maxn / jie + 1);
		for(int i = 1; i < k; i++) {
			int temp[yu * 2 + 10] = {0};
			for(int j = 0; j < jie; j++) {
				for(int tt = 0; tt < jie; tt++)
					add(temp[j + tt], 1ll * mat[i - 1][j] * mat[i - 1][tt] % mod, mod);
			}
			for(int j = 0; j < jie - 1; j++)
				for(int tt = 0; tt < jie; tt++)
					add(temp[j + tt + 1], 1ll * temp[j] * mat[0][tt] % mod, mod);
			for(int j = 0; j < jie; j++)
				mat[i][j] = temp[j + jie - 1];
		}
	}
	// 0 base, orig is the original value of the first jie 
	t get(ll n, vi orig) {
		if(n < jie) return orig[n];
		n -= jie;
		ll rn = n / jie, rn1 = n % jie;
		int xi[yu + 10];
		int temp[yu * 2 + 10] = {0};
		for(int i = 0; i < jie; i++) xi[i] = mat[0][i];
		for(int i = 0; rn; rn >>= 1, i++) if(rn & 1) {
			for(int j = 0; j < jie * 2; j++) temp[j] = 0;
			for(int j = 0; j < jie; j++)
				for(int tt = 0; tt < jie; tt++)
					add(temp[j + tt], 1ll * mat[i][tt] * xi[j] % mod, mod);
			for(int j = 0; j < jie - 1; j++)
				for(int tt = 0; tt < jie; tt++)
					add(temp[j + tt + 1], 1ll * temp[j] * mat[0][tt] % mod, mod);
			for(int j = 0; j < jie; j++)
				xi[j] = temp[j + jie - 1];
		}
		for(int i = 0; i < rn1; i++) {
			int temp = xi[0];
			for(int j = 0; j < jie - 1; j++)
				xi[j] = xi[j + 1];
			xi[jie - 1]	 = 0;
			for(int j = 0; j < jie; j++)
				add(xi[j], 1ll * temp * mat[0][j] % mod, mod);
		}
		t ans = 0;
		for(int i = 0; i < jie; i++)
			add(ans, 1ll * xi[i] * orig[i] % mod, mod);
		return ans;
	}
};

