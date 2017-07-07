#pragma once

#include "Vect3D.h"
#include "Color.h"

class ObjEdge {
public:
	Vect3D v1, v2;
	Color c1, c2;

	ObjEdge();
	ObjEdge(Vect3D, Vect3D, Color, Color);

};

ObjEdge::ObjEdge() {
	v1 = Vect3D(0, 0, 0);
	v2 = Vect3D(0, 0, 0);
	c1 = Color(0, 0, 0);
	c2 = Color(0, 0, 0);
};

ObjEdge::ObjEdge(Vect3D _v1, Vect3D _v2, Color _c1, Color _c2) {
	v1 = _v1;
	v2 = _v2;
	c1 = _c1;
	c2 = _c2;
};