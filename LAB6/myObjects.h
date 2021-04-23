#pragma once
#include "myWindow.h"
#include "Object.h"
#include "myMSG.h"
#include <vector>
#include <iostream>
class Shape2D : public Object {
public:
	enum class movedir {
		UP, DOWN, LEFT, RIGHT
	};
protected:
	SDL_Rect rect;
	SDL_Color c{ 0,255,0,254 }; // изначально фигура синяя
	std::vector<SDL_Point> points;
	enum activate_stage {
		NOT_ACTIVATED, // неактивирован 
		FIRST_ACTIVATED, // впервые активирован
		NOT_FIRST_ACTIVATED, // невпервые активирован
	} activated = NOT_ACTIVATED; // изначально все неактивированы
	virtual void refresh() = 0;
public:
	Shape2D(SDL_Rect rect) : rect(rect) { }
	activate_stage getact() { return activated; }
	virtual ~Shape2D() {}
	virtual void handleEvent(MSG*) = 0;
	virtual void show(myWindow* w) = 0;
	virtual void move(movedir direction, myWindow*) = 0;
	virtual void makebigger(myWindow*) = 0;
	virtual void makesmaller() = 0;
	virtual void destroy() = 0;
	void print() {};
};

class Triangle : public Shape2D {
	void refresh() override; 
	void print() override;
	void handleEvent(MSG* msg) override;
	void makebigger(myWindow* w) override;
	void makesmaller() override;
public:
	Triangle(SDL_Rect rect);
	void show(myWindow* w) override;
	void move(movedir direction, myWindow* w) override;
	void destroy() override {}
};

class Rect : public Shape2D {
	void refresh() {}
	void handleEvent(MSG* msg) override;
	void makebigger(myWindow* w) override;
	void makesmaller() override;
public:
	Rect(SDL_Rect rect) : Shape2D(rect) {}

	void show(myWindow* w) override;
	void move(movedir direction, myWindow* w) override;
	void print() override; 
	void destroy() override {}
};

class Circle : public Shape2D {
	void refresh(); 
	void handleEvent(MSG* msg) override;
	void makebigger(myWindow* w) override;
	void makesmaller() override;
	double r;
public:
	Circle(SDL_Rect rect);
	void show(myWindow* w) override;
	void move(movedir direction, myWindow* w) override;
	void print() override; 
	void destroy() override {}
};

