#pragma once
class point {
private:
	float x;
	float y;
public:
	point() : x(0), y(0) {}
	point(float a_x, float a_y) {
		x = a_x;
		y = a_y;
	}
	point operator=(point &p2) {
		x = p2.x;
		y = p2.y;
		return point(x, y);
	}
	point operator*(double &s) {
		x *= s;
		y *= s;
		return point(x, y);
	}
	point operator/(float &s) {
		x /= s;
		y /= s;
		return point(x, y);
	}
	point operator+=(point &p2) {
		x += p2.x;
		y += p2.y;
		return point(x, y);
	}
	
};