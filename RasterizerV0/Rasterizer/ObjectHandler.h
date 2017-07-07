#pragma once

#include "Vect2D.h"
#include "Vect3D.h"
#include "Color.h"
#include "ObjEdge.h"
#include "Tris.h"
#include "Object.h"
#include <math.h>
#include <vector>

using namespace std;

class ObjectHandler {
public:
	vector<Object> objects;

	ObjectHandler();

	vector<Vect3D> convert2D(vector<Vect3D> verts, double focalL, Vect2D offset, double scale) {
		vector<Vect3D> verts2D;
		verts2D.clear();
		for (size_t i = 0; i < verts.size(); i++) {
			Vect3D cV = verts.at(i);
			float ratio = focalL / (focalL + cV.getZ());
			double x = (cV.x * ratio * scale) + offset.getX();
			double y = (cV.y * ratio * scale) + offset.getY();
			verts2D.push_back(Vect3D(x, y, 0));
		}
		return verts2D;
	}
};

ObjectHandler::ObjectHandler() {};