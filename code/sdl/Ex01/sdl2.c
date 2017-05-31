#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

#define TRUE 1
#define FALSE 0

#define PI 3.1415926535897932

#define FRAME_MS 16

#define N_RECT 2

int state[N_RECT] = {UP, DOWN};
unsigned long stateTime[N_RECT] = {0, 0};
SDL_Rect r[N_RECT] = {{200, 200, 50, 50}, {250, 250, 100, 100}};
int rectSpeed[N_RECT] = {1, 4};
int rectMoveFrames[N_RECT] = {60, 15};

unsigned long time;
unsigned long long int frameCount = 0;

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

int isInside(SDL_MouseButtonEvent* bt, int x0, int y0, int x1, int y1)
{
	if (x0 > x1) { 
		swap(&x0, &x1);
	}
	if (y0 > y1) { 
		swap(&y0, &y1);
	}

	printf("Testing if (%d,%d) is between (%d, %d) and (%d, %d)\n", bt->x, bt->y, x0, y0, x1, y1);

	return (bt->x >= x0 &&
			bt->x <= x1 &&
			bt->y >= y0 &&
			bt->y <= y1);
}	


void move(SDL_Rect* r, int dx, int dy)
{
	r->x += dx;
	r->y += dy;
}

int main(int argc, char *argv[])
{

	/*              INIT                */
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Errou! (Init): %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_Window* window = SDL_CreateWindow("JooJ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		fprintf(stderr, "Errou de novo! (CreateWindow): %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
	{
		fprintf(stderr, "Errou outra vez! (CreateRenderer): %s\n", SDL_GetError());
		return 1;
	}
	SDL_Event e;

	unsigned long frameBeginTime, frameDelta;
	int i;
	
	while(1)
	{
		frameBeginTime = SDL_GetTicks();
		if(SDL_WaitEventTimeout(&e, FRAME_MS))
		{
			if (e.type == SDL_QUIT) break;
			
			if(e.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_MouseButtonEvent* bt = (SDL_MouseButtonEvent*) &e;
				for(i = 0; i < N_RECT; i++) {	
					if (isInside(bt, r[i].x, r[i].y, r[i].x + r[i].w, r[i].y + r[i].h))
						rectSpeed[i] = 0;
				}
			}

			frameDelta = SDL_GetTicks() - frameBeginTime;
			if (frameDelta < FRAME_MS)
				SDL_Delay(FRAME_MS - frameDelta);
		}
		
		//Background
		SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
		SDL_RenderFillRect(renderer, NULL);
		
		for(i = 0; i < N_RECT; i++)
		{	
			move(&r[i], round(cos(state[i] * PI/2.)) * rectSpeed[i], round(-sin(state[i] * PI/2.)) * rectSpeed[i]);

			SDL_SetRenderDrawColor(renderer, 0xFF * (rectSpeed[i] == 0),0x00,0xFF * (rectSpeed[i] > 0),0x00);
			SDL_RenderFillRect(renderer, &r[i]);
			
			if (frameCount - stateTime[i] > rectMoveFrames[i]) {
				state[i] = (state[i] + 1) % 4;
				stateTime[i] = frameCount; //SDL_GetTicks();
			}
		}
		
		SDL_RenderPresent(renderer);
		
		++frameCount;
	}
	//SDL_Delay(5000);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
