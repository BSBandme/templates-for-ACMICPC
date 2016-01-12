const int maxn1 = 100;
int pri[maxn1], lpri, n, nxt[maxn1], to[maxn1];
int q[maxn1], l;

void primesieve(){
//     solve prime in o(n)
	for(int i = 3; i < maxn1 - 2; i += 2) nxt[i] = i + 2;
	for(int i = maxn1 - 1; i > 3; i -= 2) to[i] = i - 2;
	to[3] = 2; nxt[2] = 3;
	for(int i = 3; i * i < maxn1; i = nxt[i]){
		l = 0;
		for(int k = i; k * i < maxn1 ; k = nxt[k]) q[l++] = k * i;
		for(int k = 0; k < l; k++){
			to[nxt[q[k]]] = to[q[k]];
			nxt[to[q[k]]] = nxt[q[k]];	  
		}
	}
	for(int i = 2; i; i = nxt[i]) pri[lpri++] = i;
}
