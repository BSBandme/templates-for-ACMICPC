struct rdouble {
	double a;
	int b;
	rdouble(double a1 = 0, int b1 = 0) : a(a1), b(b1) {}
	void relax() {
		while(a < 1) {
			a *= 10;
			b--;
		}
		while(a >= 10) {
			a /= 10;
			b++;
		}
	}
	rdouble operator + (const rdouble &temp) const {
		rdouble ans; double r;
		if(b > temp.b) {
			ans.b = b;
			ans.a = a;
			r = temp.a;
			for(int i = temp.b; i < b; i++)
				r /= 10;
			ans.a += r;
		} else {
			ans.b = temp.b;
			ans.a = temp.a;
			r = a;
			for(int i = b; i < temp.b; i++)
				r /= 10;
			ans.a += r;
		}
		ans.relax();
		return ans;
	}
	rdouble operator - (const rdouble &temp) const {
		rdouble ans; double r;
		if(b > temp.b) {
			ans.b = b;
			ans.a = a;
			r = temp.a;
			for(int i = temp.b; i < b; i++)
				r /= 10;
			ans.a -= r;
		} else {
			ans.b = temp.b;
			ans.a = temp.a;
			r = a;
			for(int i = b; i < temp.b; i++)
				r /= 10;
			ans.a -= r;
			ans.a = -ans.a;
		}
		ans.relax();
		return ans;
	}
	rdouble operator * (const rdouble &temp) const {
		rdouble ans;
		ans = temp;
		ans.a *= a;
		ans.b += b;
		ans.relax();
		return ans;
	}
	rdouble operator / (const rdouble &temp) const {
		rdouble ans;
		ans.a = a; ans.b = b;
		ans.a /= temp.a;
		ans.b -= temp.b;
		ans.relax();
		return ans;
	}
};
