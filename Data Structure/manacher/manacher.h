void manacher(char *str, int l, int *mana) {
	mana[0] = 1;
	int maxl = 0, rno = 0;
	for(int i = 1; i <= (l - 1) * 2; i++) {
		int rl = 0;
		if(maxl * 2 >= i) rl = mana[rno - (i - rno)];
		int en = ((i + 1) / 2), be = i / 2;
		en += rl, be -= rl;
		if(en > maxl + 1) {
			int delta = en - maxl - 1;
			en -= delta;
			be += delta;
		}
		while(en < l && be >= 0) {
			if(str[en] == str[be]) {
				en++;
				be--;
			} else break;
		}
		if(en - 1 > maxl) {
			maxl = en - 1;
			rno = i;
		}
		mana[i] = en - (i + 1) / 2;
	}
}
