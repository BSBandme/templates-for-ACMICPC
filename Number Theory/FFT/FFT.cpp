#include <complex>

namespace FFT2 {

	const int maxn = 1 << 15;
	int L1, L2;
	int n, id;
	int A[maxn];
	complex <double> tmp[maxn], P[maxn], PB[maxn];

	int lowbit(int n) {
		return (n ^ (n - 1)) & n;
	}
	int getnumber(int s[], int L, int id) {
		if (id > L)
			return 0;
		return s[L - id] - 48;
	}
	void Fill(int s[], int L, int m, int d, complex <double> *P) {
		if (m == n)
			P[d] = complex <double> (s[id++], 0);
		else {
			Fill(s, L, m * 2, d, P);
			Fill(s, L, m * 2, d + m, P);
		}
	}
	void Fill2(int m, int d) {
		if (m == n)
			P[d] = tmp[id++];
		else {
			Fill2(m * 2, d);
			Fill2(m * 2, d + m);
		}
	}
	void FFT(int oper, complex <double> *P) {
		for (int d = 0; (1 << d) < n; d++) {
			int i, m = (1 << d);
			double p0 = 2 * pi / double(m * 2) * double(oper);
			double sinp0 = sin(p0);
			double cosp0 = cos(p0);
			for (i = 0; i < n; i += (m * 2)) {
				double sinp = 0;
				double cosp = 1;
				for (int j = 0; j < m; j++) {
					double ta = cosp * P[i + j + m].real() - sinp * P[i + j + m].imag();
					double tb = cosp * P[i + j + m].imag() + sinp * P[i + j + m].real();
					P[i + j + m] =  complex <double> (P[i + j].real() - ta, P[i + j].imag() - tb);
					P[i + j] += complex <double> (ta, tb);
					//P[i + j].im += tb;
					double tsinp = sinp;
					sinp = sinp * cosp0 + cosp * sinp0;
					cosp = cosp * cosp0 - tsinp * sinp0;
				}
			}
		}
	}

	void multiply(int a[], int b[], int ret[], int n1) {                       // n1为a, b更长者的长度
		int L = 1;
		while(L < n1) L <<= 1;
		for(int i = n1; i < L; i++) a[i] = b[i] = 0;
		n = L << 1;
		id = 0;
		Fill(a, L, 1, 0, P);
		id = 0;
		Fill(b, L, 1, 0, PB);
		FFT(1, P);
		FFT(1, PB);
		for (int i = 0; i < n; i++) {
			tmp[i] = complex <double> (P[i].real() * PB[i].real() - P[i].imag() * PB[i].imag(), PB[i].real() * P[i].imag() + PB[i].imag() * P[i].real());
		}
		id = 0;
		Fill2(1, 0);
		FFT(-1, P);
		for (int i = 0; i < n; ++i) {
			ret[i] = int(P[i].real() / n + 0.1);
		}
	}
}