
struct point {
	union {
		double co[2];
		struct {
			double x, y;
		};
	};
	double ang;
	point(double a = 0, double b = 0) : x(a), y(b) {ang = 0;}

	point operator + (const point a) {
		point ans;
		ans.x = x + a.x;
		ans.y = y + a.y;
		return ans;
	}
	point operator - (const point a) {
		point ans;
		ans.x = x - a.x;
		ans.y = y - a.y;
		return ans;
	}
	double operator * (const point a) const {
		return x * a.x + y * a.y;
	}
	double operator % (const point a) {
		return x * a.y - y * a.x;
	}
	point operator * (double p) {
		point ans;
		ans.x = x * p;
		ans.y = y * p;
		return ans;
	}

};
double getang(double x, double y) {
	if(x == 0) {
		if(y > 0) return pi / 2;
		else return pi / 2 * 3;
	}
	if(x > 0) {
		if(y < 0) return atan(y / x) + pi * 2;
		else return atan(y / x);
	} else {
		return atan(y / x) + pi;
	}
}
double getang(point p) {
	return getang(p.x, p.y);
}
bool in(point cen, point a, point b) {
	return jud((a - cen) % (b - cen), 0) >= 0;
}

//判断两线段是否相交
bool inter(point a, point b, point c, point d){
	if ( min(a.x, b.x) > max(c.x, d.x) ||
	min(a.y, b.y) > max(c.y, d.y) ||
	min(c.x, d.x) > max(a.x, b.x) ||
	min(c.y, d.y) > max(a.y, b.y) ) return 0;
	double h, i, j, k;
	h = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	i = (b.x - a.x) * (d.y - a.y) - (b.y - a.y) * (d.x - a.x);
	j = (d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x);
	k = (d.x - c.x) * (b.y - c.y) - (d.y - c.y) * (b.x - c.x);
	return h * i <= eps && j * k <= eps;
}
struct line {
	point a, b;
	double ang;
	line(point a1 = point(0, 0), point b1 = point(1, 0)): a(a1), b(b1) {
		point temp = b1 - a1;
		ang = getang(temp.x, temp.y);
	}
	friend bool contain(line l, point a);
	bool operator == (const line &rline) const {
		return contain(*this, rline.a) && contain(*this, rline.b);
	}
};
inline bool contain(line l, point a) {
	return jud((a - l.a) % (l.b - l.a), 0) == 0;
}
point getinter(line la, line lb) {
	double sa = (lb.a - la.a) % (lb.a - la.b);
	double sb = (lb.b - la.b) % (lb.b - la.a);
	point ans = (lb.a * sb + lb.b * sa) *(1.0 / (sb + sa));
	return ans;
}
