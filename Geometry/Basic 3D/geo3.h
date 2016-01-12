struct point3 {
	union {
		double co[3];
		struct {
			double x, y, z;
		};
	};
	point3(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}

	point3 operator + (const point3 a) {
		point3 ans;
		ans.x = x + a.x;
		ans.y = y + a.y;
		ans.z = z + a.z;
		return ans;
	}
	point3 operator - (const point3 a) {
		point3 ans;
		ans.x = x - a.x;
		ans.y = y - a.y;
		ans.z = z - a.z;
		return ans;
	}
	double operator * (const point3 a) const {
		return x * a.x + y * a.y + z * a.z;
	}
	point3 operator % (const point3 a) {
		point3 ans;
		ans.x = y * a.z - z * a.y;
		ans.y = z * a.x - x * a.z;
		ans.z = x * a.y - y * a.x;
		return ans;
	}
	point3 operator * (double p) {
		point3 ans;
		ans.x = x * p;
		ans.y = y * p;
		ans.z = z * p;
		return ans;
	}
};
double getdis(point3 a, point3 b) {
	a = b - a;
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

double getang(point3 a, point3 b) {
	double p = a * b;
	double p2 = getdis(point3(0, 0, 0), a) * getdis(point3(0, 0, 0), b);
	return acos(p / p2);
}
