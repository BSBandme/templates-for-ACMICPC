//已知x, y求a,b 使 ax + by = gcd(x, y)
void extend_gcd(long long num1, long long num2, long long &a, long long &b) {
	long long i, j;
 	if(!(num1 % num2)) {
		a = 1;
		b = -num1 / num2 + 1;
		return;
	}
	extend_gcd(num2, num1 % num2, i, j);
	a = j;
	b = i - j * (num1 / num2);
}

//计算从0开始加add, 并模mod, be-en中这些数第一个出现的数是什么
ll getfirst(ll be, ll en, ll mod, ll add) {
	ll rans;
	if(add == 0) return -1;
	if(add > mod / 2) {
		rans = getfirst(mod - en, mod - be, mod, mod - add);
		if(rans == -1) return -1;
		rans = mod - rans;
		return rans;
	}
	if((be - 1) / add != en / add) {
		ll k = (be - 1) / add + 1;
		rans = k * add;
		assert(rans >= be && rans <= en);
		return rans;
	}
	ll radd = add - mod % add;
	ll rbe = be % add, ren = en % add;
	rans = getfirst(rbe, ren, add, radd);
	if(rans == -1) return -1;
	rans += be - rbe;
	return rans;
}

//计算从be开始加add, 并模mod, 最多加left次，最小可得到的数
ll getmin(ll be, ll mod, ll add, ll left) {
	if(left == 0) return be;
	pll radd = mpr(getfirst(mod - be, mod - 1, mod, add), 0);
	if(radd.first == -1) return be;
	ll ra, rb, gg = __gcd(mod, add), xia = add / gg, xib = mod / gg;
	extend_gcd(mod, add, ra, rb);
	if(rb < 0) {
		rb += xib;
		ra -= xia;
	}
	ra = ra * (radd.first / gg % xia) % xia;
	rb = rb * (radd.first / gg % xib) % xib;
	assert(rb * add + mod * ra == radd.first);
	radd.second = rb;
	if(radd.second > left) return be;
	radd.first = be - (mod - radd.first);
	left -= radd.second;

	ll rpadd = (radd.first / (be - radd.first));
	if(1.0 * rpadd * radd.second > left)
		return radd.first - (left / radd.second) * (be - radd.first);
	radd.first -= rpadd * (be - radd.first);
	left -= rpadd * radd.second;
	return getmin(radd.first, mod, add, left);
}

// caculate the number of Non negative Integer solutions that satisfy x / ta + y / tb + z / tc = 1
void getgong2(long long ta, long long tb, long long tc) {
	ll gab = __gcd(ta, tb);
	pll tab = mpr(ta, tb);
	tab.first /= gab;
	ll gctab = getgcd(tc, tab);
	ll ax, by;
	extend_gcd(tb, ta, ax, by);
//	bint btab(tab.first);
//	btab = btab * bint(tab.second);
	pll leftab = tab;
	ll rgg = __gcd(leftab.first, gctab);
	leftab.first /= rgg;
	leftab.second /= __gcd(leftab.second, gctab / rgg);
//	bint bleftab(leftab.first);
//	bleftab = bleftab * bint(leftab.second);
	ll fenmux = ta / gab, fenmuy = tb / gab;
	rgg = getgcd(fenmux, leftab);
	ll dancix = fenmux / rgg;
	rgg = getgcd(fenmuy, leftab);
	ll danciy = fenmuy / rgg;
	ll tans = (gctab + 1) % mod * (tb % mod * (abs(ax) % mod) % mod + 1) % mod;
	if(ax > 0) {
		tans += (gctab / dancix + 1) % mod;
		tans %= mod;
	} else  {
		tans -= (gctab / dancix + 1) % mod;
		if(tans < 0) tans += mod;
	}
	if(tans % 2) tans += mod;
	tans /= 2;
	if(ax <= 0) tans = mod - tans;
	ll rtans = (gctab + 1) % mod * (ta % mod * (abs(by) % mod) % mod + 1) % mod;
	if(by > 0) {
		rtans += (gctab / danciy + 1) % mod;
		rtans %= mod;
	} else  {
		rtans -= (gctab / danciy + 1) % mod;
		if(rtans < 0) rtans += mod;
	}
	if(rtans % 2) rtans += mod;
	rtans /= 2;
	if(by <= 0) rtans = mod - rtans;
	gong = rtans + tans;
	gong %= mod;

//	cerr << 1 << endl;
}



template <class c>
inline c div1(c bei, c chu){
	if(chu == 0) return -1;
	if(bei % chu == 0) return bei / chu;
	if(gcd1(chu, mod) != 1) return -1;
	long long a, b;
	extend_gcd(mod, chu, a, b);
	b *= bei;
	if(b < 0) b = -((-b) % mod) + mod;
	else b = b % mod;
	return b;
}


