#pragma once

#define MESSAGECODE_TO_START_WITH 9
class MSG {
protected:
	friend class PRG;
	char code;
	int x, y;
	void* p;
public:

	enum message{ 
		MS_BORN, MS_KILL, MS_NULL,
		MS_EXIT, MS_ECHO, MS_CLICK,
		MS_MOVE, MS_TICK, MS_KEYB
	};
	MSG(char code, int x, int y, void* p);
	~MSG();
	void setcode(char msg) { code = msg; }
	virtual void setcode2(char code) {}
	virtual char getcode2() { return -1; }
	char getcode() { return code; }
	void* getdata() { return p; }
	void clear();
};