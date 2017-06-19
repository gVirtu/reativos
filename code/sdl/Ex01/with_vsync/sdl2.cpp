#include <cstdio>
#include <cmath>
#include <algorithm>
#include <SDL2/SDL.h>
#include "Rectangle.h"

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

#define PI 3.1415926535897932

#define DESIRED_FPS 60

#define N_RECT 2

const double DesiredDelta = ((double) 1000) / DESIRED_FPS;
double frameDelta;

unsigned long time;
unsigned long long int frameCount = 0;

Rectangle r[N_RECT];

int isInside(SDL_MouseButtonEvent* bt, SDL_Rect* r) {
	return (bt->x >= r->x &&
			bt->x <= r->x + r->w &&
			bt->y >= r->y &&
			bt->y <= r->y + r->h);
}	

void initRectangles() {
	r[0] = Rectangle(200, 200, 50, 50, 1, 1000, UP);
	r[1] = Rectangle(250, 250, 100, 100, 4, 250, DOWN);
}

int main(int argc, char *argv[]) {

	/*              INIT                */
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Errou! (Init): %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_Window* window = SDL_CreateWindow("JooJ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);

	if(window == NULL) {
		fprintf(stderr, "Errou de novo! (CreateWindow): %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL) {
		fprintf(stderr, "Errou outra vez! (CreateRenderer): %s\n", SDL_GetError());
		return 1;
	}
	SDL_Event e;

	initRectangles();

	Uint64 currentFrameTime = SDL_GetPerformanceCounter();
	Uint64 lastFrameTime = 0;
	double deltaTime;
	
	/*           GAME LOOP               */
	while(1) {
		lastFrameTime = currentFrameTime;
		currentFrameTime = SDL_GetPerformanceCounter();
		deltaTime = std::min((double) ((currentFrameTime - lastFrameTime)*1000 / SDL_GetPerformanceFrequency()), 32.0);
		frameDelta = deltaTime / DesiredDelta;

		if(SDL_WaitEventTimeout(&e, 0)) {
			if (e.type == SDL_QUIT) break;
			
			if(e.type == SDL_MOUSEBUTTONDOWN) {
				SDL_MouseButtonEvent* bt = (SDL_MouseButtonEvent*) &e;
				for(int i = 0; i < N_RECT; ++i) {	
					if (isInside(bt, r[i].getSDLRect()))
						r[i].setSpeed(0);
				}
			}
		}
		
		//Background
		SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
		SDL_RenderFillRect(renderer, NULL);
		
		for(int i = 0; i < N_RECT; ++i) {	
			r[i].move(cos(r[i].getState() * PI/2.) * r[i].getSpeed(), -sin(r[i].getState() * PI/2.) * r[i].getSpeed(), frameDelta);

			SDL_SetRenderDrawColor(renderer, 0xFF * (r[i].getSpeed() == 0),0x00,0xFF * (r[i].getSpeed() > 0),0x00);
			SDL_RenderFillRect(renderer, r[i].getSDLRect());
			
			r[i].decrementMoveTime((Uint64) deltaTime);

			if (r[i].getMoveTime() == 0) {
				r[i].setState((r[i].getState() + 1) % 4);
				r[i].resetMoveTime();
			}
		}
		
		SDL_RenderPresent(renderer);
		
		++frameCount;
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
