#include "myWindow.h"
void myWindow::RenderClear()
{
	SDL_RenderClear(renderer);
}

void myWindow::RenderPresent()
{
	SDL_RenderPresent(renderer);
}

void myWindow::SetRendererColour(uint8_t r, uint8_t g, uint8_t b, uint8_t h)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, h);
}

void myWindow::DrawLine(SDL_Point p1, SDL_Point p2)
{
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

void myWindow::DrawRect(SDL_Rect r)
{
	SDL_RenderFillRect(renderer, &r);
}

void myWindow::DrawPoint(SDL_Point p)
{
	SDL_RenderDrawPoint(renderer, p.x, p.y);
}

myWindow::myWindow(unsigned int w, unsigned int h)
{
	WIDTH = w;
	HEIGHT = h;
	SDL_Init(SDL_INIT_VIDEO);
	window  = SDL_CreateWindow(u8"Lab6_OOP", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // рисуем черным
}

myWindow::~myWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(screensurface);
	SDL_DestroyWindow(window);
	SDL_Quit();
}