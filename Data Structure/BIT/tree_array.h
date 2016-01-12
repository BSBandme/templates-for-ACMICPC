const int maxn = 1 << 17;
template <class t> struct tree_array{
	t num[maxn], n, bigwei;
	tree_array(int nn = maxn){
		n = nn;
		while(lowb(nn) != nn) nn -= lowb(nn);
		bigwei = nn;
		n = bigwei * 2;
	}
	void upd(int no, t add){
		while(no <= n){
			num[no] += add;
			no += lowb(no);
		}
	}
	t que(int no){
		t ans = 0;
		while(no){
			ans += num[no];
			no -= lowb(no);
		}
		return ans;
	}
	 int getrank(t x){
		 int ans = 0, ranwei = bigwei; t rank = 0;
		 while(ranwei){
			 if(rank + num[ranwei + ans] < x){
				 ans += ranwei;
				 rank += num[ans];
			 }
			 ranwei >>= 1;
		 }
		 return ans + 1;
	 }
};