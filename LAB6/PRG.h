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
	void run(); // ����� ���� �� ����������� � ������������ ������
	virtual void sendEvent(char, int, int, void*);
	//����� ������ - ��������� ������������
	void pushobject(Object* to_push) {
		objects.push_back(to_push);
	}
	std::list<Object*>& getobjects() { return objects; }
protected: 
	void removeObject(Object* to_remove);
	std::list<Object*> objects;
	std::queue<myMSG> messages;
};