#include "SDL.h"
#include <stdio.h>
#include <iostream>
#include "Color.h"
#include "Vect2D.h"
#include "Rasterizer.h"
#include "Vect3D.h"
#include "ObjEdge.h"
#include "Tris.h"
#include "Object.h"
#include "ObjectHandler.h"
#include <math.h>
#include <vector>

SDL_Window* window;
SDL_Surface* surface;
SDL_Surface* pixelSpace;
SDL_Renderer* renderer;
SDL_Texture* texture;
ObjectHandler OH;

Uint32* pixels;

const int WIDTH = 400;
const int HEIGHT = 400;

using namespace std;

int Init() {
	window = NULL;
	surface = NULL;
	renderer = NULL;
	texture = NULL;
	pixelSpace = NULL;

	window = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	pixelSpace = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	pixels = (Uint32 *)pixelSpace->pixels;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);

	return 0;
}

void cleanUp() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Rasterizer raster = Rasterizer(pixels, WIDTH, HEIGHT);

Color gray = Color(100, 100, 100);
Color red = Color(225, 0, 0);
Color green = Color(0, 225, 0);
Color blue = Color(0, 0, 225);
Color black = Color(0, 0, 0);
Color white = Color(225, 225, 225);

vector<Vect3D> vertices = {Vect3D(  0, -7,  0),
						   Vect3D( -2,  1,  5),
						   Vect3D( -5,  -2, -5),
						   Vect3D(7.5,  0,  0) };

vector<Vect3D> vertsScreen;
vector<Edge> edges;
vector<Tris> faces;

Vect2D offset(WIDTH / 2, HEIGHT / 2);

void updateVerts() {
	vertsScreen = OH.convert2D(vertices, 60, offset, 20);
}

//UDVEF -> Update and Draw Vertices, Edges, Faces

void UDVEF() {
	vector<Edge> edges = { Edge(vertsScreen.at(0).getX(), vertsScreen.at(0).getY(), vertsScreen.at(1).getX(), vertsScreen.at(1).getY()),
						   Edge(vertsScreen.at(0).getX(), vertsScreen.at(0).getY(), vertsScreen.at(2).getX(), vertsScreen.at(2).getY()),
						   Edge(vertsScreen.at(0).getX(), vertsScreen.at(0).getY(), vertsScreen.at(3).getX(), vertsScreen.at(3).getY()),
						   Edge(vertsScreen.at(1).getX(), vertsScreen.at(1).getY(), vertsScreen.at(2).getX(), vertsScreen.at(2).getY()),
						   Edge(vertsScreen.at(2).getX(), vertsScreen.at(2).getY(), vertsScreen.at(3).getX(), vertsScreen.at(3).getY()),
						   Edge(vertsScreen.at(3).getX(), vertsScreen.at(3).getY(), vertsScreen.at(1).getX(), vertsScreen.at(1).getY()) };

	vector<Tris> faces = { Tris(vertsScreen.at(0), vertsScreen.at(1), vertsScreen.at(2)) };
						   //Tris(vertsScreen.at(0), vertsScreen.at(1), vertsScreen.at(3)) };
						   //Tris(vertsScreen.at(0), vertsScreen.at(2), vertsScreen.at(3)) };
						   //Tris(vertsScreen.at(1), vertsScreen.at(3), vertsScreen.at(2), red, red, red) };

	for (size_t i = 0; i < faces.size(); i++) {	
		raster.PutTris((int)faces.at(i).v1.getX(), (int)faces.at(i).v1.getY(), (int)faces.at(i).v2.getX(), (int)faces.at(i).v2.getY(), (int)faces.at(i).v3.getX(), (int)faces.at(i).v3.getY(), pixelSpace);
	}
	for (size_t i = 0; i < edges.size(); i++) {
		raster.PutLine((int)edges.at(i).x1, (int)edges.at(i).y1, (int)edges.at(i).x2, (int)edges.at(i).y2, pixelSpace);
	}
	/*for (size_t i = 0; i < vertsScreen.size(); i++) {
		raster.PutPixel((int)vertsScreen.at(i).getX(), (int)vertsScreen.at(i).getY(), white, pixelSpace);
	}	*/
}

void Draw() {
	updateVerts();
	UDVEF();
}

void updateScreen() {
	Draw();

	//SDL Stuff
	SDL_UpdateTexture(texture, NULL, pixelSpace->pixels, pixelSpace->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {

	bool quit = false;

	SDL_Event event;

	Init();

	while (!quit)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		updateScreen();		
	}

	cleanUp();

	return 0;
}