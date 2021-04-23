#include "PRG.h"
#include <ctime>
PRG::PRG(unsigned int w, unsigned int h) : w(w), h(h)
{
	Object::programm = this;
}

PRG::~PRG()
{
	for (auto& obj : objects) {
		delete obj;
	}
}
void PRG::run() {
	myWindow win(w, h);
	myMSG msg(MSG::MS_NULL, 0, 0, nullptr);
	clock_t t = clock();
	uint8_t x = 0;
	while (true) { // 
		messages.push(myMSG(myMSG::MS_SHOW, 0, 0, (void*)&win));
		SDL_PollEvent(&win.event);
		switch (win.event.type) {
		case SDL_KEYDOWN:
			switch (win.event.key.keysym.sym) {
			case SDLK_UP:
				if (clock() - t > 5) {
					t = clock();
					messages.push(myMSG(myMSG::MS_UP, 0, 0, (void*)&win)); break;
				}
				break;
			case SDLK_DOWN:
				if (clock() - t > 5) {
					t = clock();
					messages.push(myMSG(myMSG::MS_DOWN, 0, 0, (void*)&win)); break;
				}
				break;
			case SDLK_LEFT:
				if (clock() - t > 5) {
					t = clock();
					messages.push(myMSG(myMSG::MS_LEFT, 0, 0, (void*)&win)); break;
				}
				break;
			case SDLK_RIGHT:
				if (clock() - t > 5) {
					t = clock();
					messages.push(myMSG(myMSG::MS_RIGHT, 0, 0, (void*)&win)); break;
				}
				break;
			case SDLK_LSHIFT:
				if (clock() - t > 5) {
					t = clock();
					messages.push(myMSG(myMSG::MS_MAKESMALLER, 0, 0, (void*)&win)); break;
				}
				break;
			case SDLK_RSHIFT:
				if (clock() - t > 5) {
					t = clock();
					messages.push(myMSG(myMSG::MS_MAKEBIGGER, 0, 0, (void*)&win)); break;
				}
				break;
			case SDLK_0: {SDL_Rect rect = { 0,0,40,40 }; new Triangle(rect); break; }
			case SDLK_1: {SDL_Rect rect = { 0,0,40,40 }; new Rect(rect); break; }
			case SDLK_2: {SDL_Rect rect = { 0,0,40,40 }; new Circle(rect); break; }
			case SDLK_DELETE: {messages.push(myMSG(myMSG::MS_DESTROY, 0, 0, nullptr)); break; }
			case SDLK_TAB: if (clock() - t > 200) {
				t = clock();
				messages.push(myMSG(myMSG::MS_ACTIVATE, 0, 0, nullptr)); break;
			}
			default: break;
			}
		}

		win.RenderClear();
		for (int n = 0; !messages.empty(); n++) {
			msg = messages.front(); messages.pop();
			switch (msg.getcode()) {
			case MSG::MS_BORN:
				objects.push_back((Object*)msg.getdata());
				break;
			case MSG::MS_NULL:
				break;
			case MSG::MS_EXIT:
				return;
			case MSG::MS_KILL:
				removeObject((Object*)msg.getdata());
				break;
			default:
				for (auto obj : objects) {
					obj->handleEvent(&msg);
					if (msg.getcode() == MSG::MS_NULL)
						break;
				}
				if (msg.getcode2() == myMSG::MS_LAST_IS_NOT_ACTIVATED) { // если последний оказался ранее активированным
					sendEvent(myMSG::MS_DEACTIVATE, 0, 0, nullptr); //сбрасываем активность всех
				}
			}
		}
		win.SetRendererColour(255, 255, 255, 0);
		win.RenderPresent();
	}
}

void PRG::sendEvent(char code0, int x0, int y0, void* p0)
{
	messages.push(myMSG(code0, x0, y0, p0));
}

void PRG::removeObject(Object* to_remove)
{
	auto it_founded = std::find(objects.begin(), objects.end(), to_remove);
	if (it_founded == objects.end()) {
		return;
	}
	delete* it_founded;
	objects.erase(it_founded);
}
