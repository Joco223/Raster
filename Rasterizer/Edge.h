#pragma once

#include "Color.h"

class Edge {
public:
	int x1, y1, x2, y2;

	Edge(int, int, int, int);
};

Edge::Edge(int _x1, int _y1, int _x2, int _y2) {
	if (_y1 < _y2) {
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}else{
		x1 = _x2;
		y1 = _y2;
		x2 = _x1;
		y2 = _y1;
	}
};