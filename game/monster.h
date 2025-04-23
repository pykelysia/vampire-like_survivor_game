#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "common_def.h"
#include "player.h"

class Monster {
public:
	Monster(int t_life, int t_attack) : life(t_life), attack(t_attack) {}
	virtual ~Monster() {}
	bool CheckPlayerCollision() { return false; }
	bool CheckBulletCollision() { return false; }
	void Move(const Player& player) {}
	void Drow() {}

protected:
	LIFE life;
	ATTACK attack;
	POINT position = { 0,0 };
	//
};

#endif // !_MONSTER_H_
