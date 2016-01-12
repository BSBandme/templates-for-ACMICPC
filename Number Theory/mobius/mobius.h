int miu[maxn], pri[maxn], lpri, is[maxn];

void mobius() {
	 for(int i = 0; i < maxn; i++) is[i] = 1;
	 for(int i = 2; i < maxn; i++) {
	 	if(is[i]) pri[lpri++] = i, miu[i] = -1;
	     for(int j = 0; j < lpri; j++) {
		    if(pri[j] * i >= maxn) break;
	        is[i * pri[j]] = 0;
		    if(i % pri[j] == 0) {
			 	miu[i * pri[j]] = 0;
                break;
            } else miu[i * pri[j]] = -miu[i]; 
        } 
    }  
}

