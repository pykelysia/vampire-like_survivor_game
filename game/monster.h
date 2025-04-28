#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "common_def.h"
#include "player.h"
#include "bullet.h"

class Monster {
public:
	Monster(int t_life, int t_attack) : life(t_life), attack(t_attack) {}
	virtual ~Monster() {}
	bool CheckPlayerCollision() { return false; }
	bool CheckBulletCollision() { return false; }
	void Hurt(){}
	bool CheckAlive() { return false; }
	void Move(const Player& player) {}
	void Attack(Player* player) {
		TIME newAttackTime = GetTickCount();
		if (newAttackTime - lastAttackTime > ATTACK_CD_TIME || lastAttackTime == 0) {
			SetLastAttackTime(newAttackTime);
			player->Hurt(attack);
		}
	}
	void SetLastAttackTime(TIME newTime) { lastAttackTime = newTime; }

	void Hurt(const Player& player, const Bullet& bullet) {
		life -= player.GetAttack();
		DISTANCE repell = bullet.GetRepell();
		POINT bulletPosition = player.GetPosition();
		int x_dir = position.x - bulletPosition.x;
		int y_dir = position.y - bulletPosition.y;
		double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
		if (vec_dir != 0) {
			double x_real = x_dir / vec_dir;
			double y_real = y_dir / vec_dir;
			position.x += x_real * repell;
			position.y += y_real * repell;
		}
	}
	void Drow() {}

protected:
	LIFE life;
	ATTACK attack;
	POINT position = { 0,0 };
	TIME lastAttackTime = 0;
};

#endif // !_MONSTER_H_
