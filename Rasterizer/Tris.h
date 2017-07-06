#pragma once

#include "Vect3D.h"
#include "Color.h"

class Tris {
public:
	Vect3D v1, v2, v3;

	Tris();
	Tris(Vect3D, Vect3D, Vect3D);

	Vect3D getCenter() {
		Vect3D sum = v1.Add(v2.Add(v3));
		return sum.Div(3);
	};

	Vect3D getNormal() {
		Vect3D a = v1.Sub(v2);
		Vect3D b = v1.Sub(v3);
		Vect3D result = a.crossProduct(b);
		result = result.Normal();
		return result;
	};
};

Tris::Tris() {
	v1 = Vect3D(0, 0, 0);
	v2 = Vect3D(0, 0, 0);
	v3 = Vect3D(0, 0, 0);
};

Tris::Tris(Vect3D _v1, Vect3D _v2, Vect3D _v3) {
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
};