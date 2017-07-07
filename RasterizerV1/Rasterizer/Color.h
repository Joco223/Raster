#pragma once

class Color {
private:
	int r, g, b;

public:
	Color();
	Color(int, int, int);

	int getR() { return r; };
	int getG() { return g; };
	int getB() { return b; };

	void setR(int amount) { r = amount; };
	void setG(int amount) { g = amount; };
	void setB(int amount) { b = amount; };

	Color Mlt(float amount) { return Color(this->r * amount, this->g * amount, this->b * amount); };
	Color Div(float amount) { return Color(this->r / amount, this->g / amount, this->b / amount); };
	Color Add(int amount) { return Color(this->r + amount, this->g + amount, this->b + amount); };
	Color Sub(int amount) { return Color(this->r - amount, this->g - amount, this->b - amount); };

	Color Add(Color c) { return Color(this->r + c.getR(), this->g + c.getG(), this->b + c.getB()); };
	Color Sub(Color c) { return Color(this->r - c.getR(), this->g - c.getG(), this->b - c.getB()); };

	bool operator==(Color other) {
		bool same = false;
		if (this->r == other.getR()) { same = true; };
		if (this->g == other.getG()) { same = true; };
		if (this->b == other.getB()) { same = true; };
		return same;
	}

	void Clamp() {
		if (r > 255) r = 255;
		if (r < 0) r = 0;
		if (g > 255) g = 255;
		if (g < 0) g = 0;
		if (b > 255) b = 255;
		if (b < 0) b = 0;
	}
};

Color::Color() {
	r = 200;
	g = 200;
	b = 200;
}

Color::Color(int _r, int _g, int _b) {
	r = _r;
	g = _g;
	b = _b;
};
