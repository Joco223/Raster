#pragma once

#include "Vect3D.h"
#include "Vect2D.h"
#include "ObjEdge.h"
#include "Tris.h"
#include <vector>

using namespace std;

class Object {
public:
	vector<Vect3D> verts;
	vector<ObjEdge> edges;
	vector<Tris> faces;

	Object();
	Object(vector<Vect3D>, vector<ObjEdge>, vector<Tris>);
};

Object::Object() {};

Object::Object(vector<Vect3D> _verts, vector<ObjEdge> _edges, vector<Tris> _faces) {
	verts = _verts;
	edges = _edges;
	faces = _faces;
};