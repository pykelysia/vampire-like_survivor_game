#include "scenior.h"

Scenior::Scenior(){}

void Scenior::Draw(const Player& player){
	WIDTH_INT width = int(WIDTH * player.GetLevalPercent());
	setfillcolor(GREEN);
	solidrectangle(0, 0, width, barWidth);
}
