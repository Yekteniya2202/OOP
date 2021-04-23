#pragma once
#include <SDL.h>
class myWindow
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screensurface;
	unsigned int WIDTH, HEIGHT;
public:
	SDL_Event event;
	void RenderClear();
	void RenderPresent();
	void SetRendererColour(uint8_t r, uint8_t g, uint8_t b, uint8_t h);
	void DrawLine(SDL_Point p1, SDL_Point p2);
	void DrawRect(SDL_Rect r);
	void DrawPoint(SDL_Point p);
	SDL_Renderer* getrenderer(){ return renderer; }
	unsigned int getWIDTH() { return WIDTH; }
	unsigned int getHEIGHT() { return HEIGHT; }
	myWindow(unsigned int w = 800, unsigned int h = 600);
	~myWindow();

private:

};
