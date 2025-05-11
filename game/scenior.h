#ifndef _SCENIOR_H_
#define _SCENIOR_H_

#include "common_def.h"
#include "player.h"

class Scenior {
public:
	Scenior();
	~Scenior(){}
	
	void Draw(const Player& player);
private:
	const WIDTH_INT barWidth = 5;
};

#endif