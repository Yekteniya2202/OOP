#pragma once
#include "myObjects.h"
#include <queue>
#include <list>
#include <iostream>
class Object;
class PRG {

	unsigned int w, h;
public:
	PRG(unsigned int, unsigned int);
	~PRG();
	void run(); // можно было бы перегрузить у наследуемого класса
	virtual void sendEvent(char, int, int, void*);
	//любой геттер - нарушение инкапсул€ции
	void pushobject(Object* to_push) {
		objects.push_back(to_push);
	}
	std::list<Object*>& getobjects() { return objects; }
protected: 
	void removeObject(Object* to_remove);
	std::list<Object*> objects;
	std::queue<myMSG> messages;
};