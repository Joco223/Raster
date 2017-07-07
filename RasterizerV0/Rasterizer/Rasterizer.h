#pragma once

#include <math.h>
#include "SDL.h"
#include "Color.h"
#include "Vect2D.h"
#include "Edge.h"
#include "Span.h"

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

	Uint32* PutSpan(Span s, float y, SDL_Surface *pixelSurface) {
		for (int x = s.x1; x < s.x2; x++) {
			PutPixel(x, y, White, pixelSurface);
		}
		return pixels;
	}

	Uint32* DSBE(Edge e1, Edge e2, SDL_Surface *pixelSurface) {
		float e1ydiff = (float)(e1.y2 - e1.y1);
		if (e1ydiff == 0) { return pixels; };

		float e2ydiff = (float)(e2.y2 - e2.y1);
		if (e2ydiff == 0) { return pixels; };

		float e1xdiff = (float)(e1.x2 - e1.x1);
		float e2xdiff = (float)(e2.x2 - e2.x1);

		float factor1 = (float)(e2.y1 - e1.y1) / e1ydiff;
		float factorStep1 = 1.0f / e1ydiff;
		float factor2 = 0.0f;
		float factorStep2 = 1.0f / e2ydiff;

		for (int y = e2.y1; y < e2.y2; ++y) {
			Span span(e1.x1 + (int)(e1xdiff * factor1), e2.x1 + (int)(e2xdiff * factor2));
			PutSpan(span, y, pixelSurface);

			factor1 += factorStep1;
			factor2 += factorStep2;
		}

		return pixels;
	}

	Uint32* PutTris(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Surface *pixelSurface) {
		Edge edges[3] = {
			Edge((int)x1, (int)y1, (int)x2, (int)y2),
			Edge((int)x2, (int)y2, (int)x3, (int)y3),
			Edge((int)x3, (int)y3, (int)x1, (int)y1)
		};

		int maxLength = 0;
		int longEdge = 0;

		for (int i = 0; i < 3; i++) {
			int length = edges[i].y2 - edges[i].y1;
			if (length > maxLength) {
				maxLength = length;
				longEdge = i;
			}
		}

		int shortEdge1 = (longEdge + 1) % 3;
		int shortEdge2 = (longEdge + 2) % 3;

		DSBE(edges[longEdge], edges[shortEdge1], pixelSurface);
		DSBE(edges[longEdge], edges[shortEdge2], pixelSurface);

		return pixels;
	}
};

Rasterizer::Rasterizer() {}

Rasterizer::Rasterizer(Uint32* _pixels, int _w, int _h) {
	pixels = _pixels;
	w = _w;
	h = _h;
}
