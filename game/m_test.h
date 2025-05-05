#ifndef _M_TEST_H_
#define _M_TEST_H_

#include "common_def.h"
#include "monster.h"
#include "player.h"
#include "bullet.h"

class M_test :public Monster {
public:
	M_test(int life, int attack);

	void Move(const Player& player);

	bool CheckPlayerCollision(const Player& player);

	bool CheckBulletCollision(const Bullet& bullet);

	void Drow() const;

private:
	_SIZE M_Width = 40;
	_SIZE M_High = 50;
	SPEED speed = 2;
};

void TryGenerateM_test(std::vector<M_test*>& M_test_list);
#endif // !_M_TEST_H_
