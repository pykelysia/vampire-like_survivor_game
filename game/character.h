#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "common_def.h"
#include "bullet.h"
#include "player.h"
#include "experience_ball.h"

class Character
{
public:
	POINT GetPosition(void);
	void Draw(void);
	
private:
	POINT position;
};

#endif // !_CHARACTER_H_
