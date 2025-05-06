#ifndef _BULLETLIST_H_
#define _BULLETLIST_H_

#include "player.h"
#include "bullet.h"
#include "collision.h"

class BulletList
{
public:
	BulletList();
	virtual ~BulletList(){}

	void UpdataBulletPosition(const Player& player);
	void CheckCollision(BulletCollision collision, M_test* m_test, Player& player);
	void Draw();
private:
	std::vector<Bullet*> list;
};

#endif // !_BULLETLIST_H_