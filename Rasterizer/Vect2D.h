#pragma once

#include <math.h>

class Vect2D{
private:
	double x, y;

public:
	Vect2D(double, double);

	double getX() { return x; };
	double getY() { return y; };

	void setX(double amount) { x = amount; };
	void setY(double amount) { y = amount; };

	double Distance(Vect2D other) { return sqrt(((x - other.x) * (x - other.x)) + ((y - other.y) * (y - other.y))); };
	double Magnitude() { return sqrt(x * x + y * y); };
};

Vect2D::Vect2D(double _x, double _y) {
	x = _x;
	y = _y;
}