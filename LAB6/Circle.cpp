#include "myObjects.h"
void Circle::refresh()
{
	points[0] = { rect.x + rect.w / 2, rect.y + rect.h / 2 };
}

void Circle::handleEvent(MSG* msg)
{

	switch (msg->getcode()) {

	case myMSG::MS_ACTIVATE:
	{
		if (activated == NOT_ACTIVATED) { // если не активирован
			activated = FIRST_ACTIVATED;
			msg->clear();
			break;
		}
		if (activated == NOT_FIRST_ACTIVATED) {
			msg->setcode2(myMSG::MS_LAST_IS_NOT_ACTIVATED);
			break;
		}
		// пусть делается опрос об активности фигур
		if (activated == FIRST_ACTIVATED) { // если в опросе не будет активных впервые фигур - деактивируем все
			activated = NOT_FIRST_ACTIVATED;
			msg->setcode2(myMSG::MS_NULL);
			msg->setcode(myMSG::MS_ACTIVATEONCE);
			sendEvent(myMSG::MS_ASKACTIVATED, 0, 0, (void*)this); // отправляем опрос с указателем на себя 
			// если отправить опрос с конца и не найти впервые активированого
			break;
		}
	}
	case myMSG::MS_ACTIVATEONCE: {
		activated = FIRST_ACTIVATED;
		msg->clear();
		break;
	}
	case myMSG::MS_ASKACTIVATED: // обрабатываем опрос
		if (activated == NOT_FIRST_ACTIVATED) { // если ранее был активирован
			msg->setcode2(myMSG::MS_LAST_IS_NOT_ACTIVATED);
		}
		else  if (activated == FIRST_ACTIVATED) {
			msg->setcode2(myMSG::MS_NULL);
		}
		else {
			if (msg->getcode2() != myMSG::MS_NULL)
				sendEvent(myMSG::MS_DEACTIVATE, 0, 0, nullptr);
		}
		break;
	case myMSG::MS_DEACTIVATE:
		activated = NOT_ACTIVATED;
		break;

	case myMSG::MS_SHOW:
		show((myWindow*)msg->getdata());
		break;

	case myMSG::MS_UP:
		if (activated == FIRST_ACTIVATED) {
			move(movedir::UP, (myWindow*)msg->getdata());
		}
		break;
	case myMSG::MS_DOWN:
		if (activated == FIRST_ACTIVATED) {
			move(movedir::DOWN, (myWindow*)msg->getdata());
		}
		break;
	case myMSG::MS_LEFT:
		if (activated == FIRST_ACTIVATED) {
			move(movedir::LEFT, (myWindow*)msg->getdata());
		}
		break;
	case myMSG::MS_RIGHT:
		if (activated == FIRST_ACTIVATED) {
			move(movedir::RIGHT, (myWindow*)msg->getdata());
		}
		break;
	case myMSG::MS_MAKEBIGGER:
		if (activated == FIRST_ACTIVATED) {
			makebigger((myWindow*)msg->getdata());
			refresh();
		}
		break;
	case myMSG::MS_MAKESMALLER:
		if (activated == FIRST_ACTIVATED) {
			makesmaller();
			refresh();
		}
		break;
	case myMSG::MS_DESTROY:
		if (activated == FIRST_ACTIVATED) {
			sendEvent(myMSG::MS_KILL, 0, 0, this);
			sendEvent(myMSG::MS_DEACTIVATE, 0, 0, nullptr);
		}
		break;
	default:
		break;
	}
}

void Circle::makebigger(myWindow* w)
{
	if (rect.y + rect.h + 2 < w->getHEIGHT() && rect.x + rect.w + 2 < w->getWIDTH()) {
		r += 1;
		rect.w += 2;
		rect.h += 2;
	}
}

void Circle::makesmaller()
{
	if (r > 1) {
		r -= 1;
		rect.w -= 2;
		rect.h -= 2;
	}
}

Circle::Circle(SDL_Rect rect) : Shape2D(rect) {
	points.resize(1);
	//rect.w = rect.x;
	points[0] = { rect.x + rect.w / 2, rect.y + rect.h / 2 };
	r = rect.w / 2.;
}

void Circle::show(myWindow* w)
{
	if (activated == FIRST_ACTIVATED) {
		w->SetRendererColour(255, 0, 0, 0);
	}
	else {
		w->SetRendererColour(0, 255, 0, 0);
	}
	for (double j = 0; j <= 360; j = j + 0.5)
	{
		double rad;
		rad = j * M_PI / 180;
		SDL_Point p1 = { points[0].x + r * sin(rad), points[0].y + r * cos(rad) };
		w->DrawPoint(p1);
		//SDL_Point p2 = { points[0].x + r * sin(2 * M_PI - rad), points[0].y + r * cos(2 * M_PI - rad) };
		//SDL_Point p3 = { points[0].x + r * sin(M_PI - rad), points[0].y + r * cos(M_PI - rad) };
		//w->DrawLine(p1, p2);
		//w->DrawLine(p1, p3);
	}

}

void Circle::move(movedir direction, myWindow* w)
{
	switch (direction) {
	case movedir::UP:
		if (rect.y > 0) {
			rect.y--;
			refresh();
		}
		break;
	case movedir::DOWN:
		if (rect.y + rect.h < w->getHEIGHT()) {
			rect.y++;
			refresh();
		}
		break;
	case movedir::LEFT:
		if (rect.x > 0) {
			rect.x--;
			refresh();
		}
		break;
	case movedir::RIGHT:
		if (rect.x + rect.w < w->getWIDTH()) {
			rect.x++;
			refresh();
			break;
		}
	}
}

void Circle::print()
{
	std::cout << "This is circle: active = " << activated;
}