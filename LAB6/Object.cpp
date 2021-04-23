#include "Object.h"
#include "PRG.h"
PRG* Object::programm = nullptr;

void Object::sendEvent(char code0, int x0, int y0, void* p0)
{
	if (programm != nullptr) {
		programm->sendEvent(code0, x0, y0, p0);
	}
}

void Object::handleEvent(MSG* pm)
{
	pm->clear();
}

Object::Object()
{
	sendEvent(MSG::MS_BORN, 0, 0, this);
}

Object::~Object()
{
}
