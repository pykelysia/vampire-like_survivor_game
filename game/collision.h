#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "player.h"
#include "bullet.h"
#include "m_test.h"

class Collision
{
public:
	Collision(){}
	bool CheckCollision(Character characterBeCollision, Character characterCollision){}
};

class MonsterCollision :public Collision {
public:
	bool CheckCollision(Monster monster, Character character){}
};

class M_testCollision :public MonsterCollision {
public:
	bool CheckCollision(M_test* m_test, Player& player);
};

class BulletCollision :public Collision {
public:
	bool CheckCollision(Bullet* bullet, M_test* m_test);
};

class ExballCollision :public Collision {
public:
	bool CheckCollision(ExperienceBall* exball, const Player& player);
};

#endif