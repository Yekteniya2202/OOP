#include "MSG.h"

MSG::MSG(char code0, int x0, int y0, void* p0) {
	code = code0;
	x = x0;
	y = y0;
	p = p0;
}

MSG::~MSG() {}

void MSG::clear()
{
	code = MS_NULL;
}
