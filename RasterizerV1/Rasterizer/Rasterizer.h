#pragma once

#include <math.h>
#include <algorithm>
#include "SDL.h"
#include "Color.h"
#include "Vect2D.h"
#include "Vect3D.h"

Color White = Color(225, 225, 225);

class Rasterizer {
private:
	int w, h;
	Uint32* pixels;

public:
	Rasterizer();
	Rasterizer(Uint32*, int, int);

	Uint32* getPixels() { return pixels; };
	int getWidth() { return w; };
	int getHeight() { return h; }

	void setPixels(Uint32* _pixels) { pixels = _pixels; };
	void setHeight(int _h) { h = _h; };
	void setWidth(int _w) { w = _w; };

	Uint32* PutPixel(int x, int y, Color c, SDL_Surface *pixelSurface) {
		Uint32 * pixels = (Uint32 *)pixelSurface->pixels;
		pixels[y * w + x] = SDL_MapRGB(pixelSurface->format, c.getB(), c.getG(), c.getR());
		return pixels;
	};

	Uint32* PutRect(int x, int y, int sX, int sY, Color c, SDL_Surface *pixelSurface) {
		Uint32 * pixels = (Uint32 *)pixelSurface->pixels;
		for (int i = 0; i < sX; i++) {
			for (int j = 0; j < sY; j++) {
				pixels[(y + j) * w + x + i] = SDL_MapRGB(pixelSurface->format, c.getB(), c.getG(), c.getR());
			}
		}		
		return pixels;
	}

	Uint32* PutLine(int x1, int y1, int x2, int y2, SDL_Surface *pixelSurface) {
		float xdiff = (x2 - x1);
		float ydiff = (y2 - y1);

		if (fabs(xdiff) > fabs(ydiff)) {
			float Xmin, Xmax;

			if (x1 < x2) {
				Xmin = x1;
				Xmax = x2;
			}else{
				Xmin = x2;
				Xmax = x1;
			}

			float slope = ydiff / xdiff;
			for (float x = Xmin; x <= Xmax; x += 1.0f) {
				float y = y1 + ((x - x1) * slope);
				PutPixel((int)x, (int)y, White, pixelSurface);
			}

			return pixels;
		}else{
			float Ymin, Ymax;

			if (y1 < y2) {
				Ymin = y1;
				Ymax = y2;
			}else{
				Ymin = y2;
				Ymax = y1;
			}

			float slope = xdiff / ydiff;
			for (float y = Ymin; y <= Ymax; y += 1.0f) {
				float x = x1 + ((y - y1) * slope);	
				PutPixel((int)x, (int)y, White, pixelSurface);
			}

			return pixels;
		}
	}

	Uint32* PutTris(int x1, int y1, int x2, int y2, int x3, int y3, Color c, SDL_Surface *pixelSurface) {
		int minX = std::min({x1, x2, x3});
		int minY = std::min({y1, y2, y3});
		int maxX = std::max({x1, x2, x3});
		int maxY = std::max({y1, y2, y3});

		static const int subStep = 256;
		static const int subMask = subStep - 1;

		minX = std::max(minX, 0);
		minY = std::max(minY, 0);
		
		maxX = std::min(maxX, 399);
		maxY = std::min(maxY, 399);

		Vect3D v0 = Vect3D(x1, y1, 0);
		Vect3D v1 = Vect3D(x2, y2, 0);
		Vect3D v2 = Vect3D(x3, y3, 0);
		Vect3D p;
		for (p.y = minY; p.y <= maxY; p.y += 1) {
			for (p.x = minX; p.x <= maxX; p.x += 1) {
				int w0 = p.orient2D(v1, v2, p);
				int w1 = p.orient2D(v2, v0, p);
				int w2 = p.orient2D(v0, v1, p);

				if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
					PutPixel(p.x, p.y, c, pixelSurface);
				}
			}
		}
		return pixels;
	}
};

Rasterizer::Rasterizer() {}

Rasterizer::Rasterizer(Uint32* _pixels, int _w, int _h) {
	pixels = _pixels;
	w = _w;
	h = _h;
}
