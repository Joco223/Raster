#pragma once

#include <math.h>

class Vect3D {
public:
	double x, y, z;

	Vect3D();
	Vect3D(double, double, double);

	double getX() { return x; };
	double getY() { return y; };
	double getZ() { return z; };

	double Distance(Vect3D other) { return sqrt(((other.x - x) * (other.x - x)) + ((other.y - y) * (other.y - y)) + ((other.z - z) * (other.z - z))); };
	double Magnitude() { return sqrt(x * x + y * y + z * z); };
	double dotProduct(Vect3D other) { return x * other.x + y * other.y + z * other.z; };

	Vect3D crossProduct(Vect3D other) { return Vect3D(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.z); };
	Vect3D Div(double amount) { return Vect3D(x / amount, y / amount, z / amount); };
	Vect3D Normal() {
		double mag = this->Magnitude();
		if (mag > 0) {
			return this->Div(mag);
		}else{
			return Vect3D(0, 0, 0);
		}
	};
	Vect3D Add(Vect3D other) { return Vect3D(x + other.x, y + other.y, z + other.z); };
	Vect3D Sub(Vect3D other) { return Vect3D(x - other.x, y - other.y, z - other.z); };
};

Vect3D::Vect3D() {
	x = 0;
	y = 0;
	z = 0;
};

Vect3D::Vect3D(double _x, double _y, double _z) {
	x = _x;
	y = _y;
	z = _z;
};