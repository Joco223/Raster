#pragma once

#include "Color.h"

class Span {
public:
	int x1, x2;

	Span(int, int);
};

Span::Span(int _x1, int _x2) {
	if (_x1 < x2) {
		x1 = _x1;
		x2 = _x2;
	}
	else {
		x1 = _x2;
		x2 = _x1;
	}
};