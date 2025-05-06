#ifndef _M_TEST_H_
#define _M_TEST_H_

#include "common_def.h"
#include "monster.h"
#include "player.h"

class Player;

class M_test : public Monster {
public:
	M_test(int life, int attack);
	_SIZE GetWidth(void) const;
	_SIZE GetHigh(void) const;

	void Move(const Player& player);

	void Draw() const;

private:
	_SIZE M_Width = 40;
	_SIZE M_High = 50;
	SPEED speed = 3;
};
#endif // !_M_TEST_H_