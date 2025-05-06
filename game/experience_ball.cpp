#include "experience_ball.h"

ExperienceBall::ExperienceBall(int _value, POINT _position) : value(_value), position(_position) {}
VALUE ExperienceBall::GetValue(void) const { return value; }

POINT ExperienceBall::GetPosition(void) const{ return position; }

void ExperienceBall::Draw(void) const {
	setfillcolor(GREEN);
	solidcircle(position.x, position.y, 5);
}