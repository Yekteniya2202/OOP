#include "myObjects.h"
void Rect::handleEvent(MSG* msg)
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
					msg->setcode2(myMSG::MS_LAST_IS_NOT_ACTIVATED);
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
		default:
			break;
	}
}

void Rect::makebigger(myWindow* w)
{
	if (rect.y + rect.h < w->getHEIGHT() && rect.x + rect.w < w->getWIDTH()) {
		rect.w++;
		rect.h++;
	}
}

void Rect::makesmaller()
{
	if (rect.w > 0 && rect.h > 0) {
		rect.w--;
		rect.h--;
	}
}

void Rect::show(myWindow* w)
{
	if (activated == FIRST_ACTIVATED) {
		w->SetRendererColour(255, 0, 0, 0);
	}
	else {
		w->SetRendererColour(0, 255, 0, 0);
	}
	w->DrawRect(rect);
}

void Rect::move(movedir direction, myWindow* w)
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

void Rect::print()
{
	std::cout << "This is rect: active = " << activated;
}
