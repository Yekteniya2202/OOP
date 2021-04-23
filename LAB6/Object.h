#pragma once
#include "MSG.h"
#include "myMSG.h"
class PRG;
class Object { 
	friend PRG;
	static PRG* programm;
public:
	virtual void print() = 0;
	void sendEvent(char, int, int, void*);
	virtual void handleEvent(MSG*);
	Object();
	virtual ~Object();
};
