#pragma once
#include "MSG.h"
class myMSG : public MSG {
	friend class PRG;
public:

	enum message {
		//костыль :)
		MS_UP = MESSAGECODE_TO_START_WITH, MS_DOWN, MS_LEFT, MS_RIGHT,
		MS_ACTIVATE, MS_ACTIVATEONCE,
		MS_ASKACTIVATED,
		MS_HASFIRSTACTIVATED,
		MS_LAST_IS_NOT_ACTIVATED,
		MS_NOFIRSTACTIVATED,
		MS_DEACTIVATE,
		MS_MAKEBIGGER, MS_MAKESMALLER, 
		MS_DESTROY,
		MS_SHOW
	};
	char code2;
	void setcode2(char code) override { code2 = code; }
	char getcode2() override { return code2; }
	myMSG(char code, int x, int y, void* p) : MSG(code, x, y, p) {  }
	~myMSG();
	void clear();
};