#pragma once

#include "PRG.h"
#include <conio.h>
//ошибка - желательно сделать приватное наследование
class myPRG : public PRG {
public:
	myPRG(unsigned int w, unsigned int h) : PRG(w,h) {
		SDL_Rect rect1 = {0,0,40,40};
		SDL_Rect rect2 = { 0,60,40,40 };
		SDL_Rect rect3 = { 0,120,100,100 };
		new Triangle(rect1);
		new Rect(rect2);
		new Circle(rect3);
	}
};
