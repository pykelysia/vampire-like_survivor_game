#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "common_def.h"
#include "character.h"
#include "player.h"
#include "bullet.h"

class Player;
class Bullet;

class Monster : public Character {
public:
	Monster(int t_life, int t_attack) : life(t_life), attack(t_attack) {}
	virtual ~Monster() {}
	POINT GetPosition(void) const;
	void Attack(Player* player);
	void SetLastAttackTime(TIME newTime);

	void Hurt(const Player& player, const Bullet& bullet);
	bool CheckAlive(void) const;

protected:
	LIFE life;
	ATTACK attack;
	POINT position = { 0,0 };
	TIME lastAttackTime = 0;
};

#endif // !_MONSTER_H_
