#ifndef _M_TESTLIST_H_
#define _M_TESTLIST_H_

#include "common_def.h"
#include "character.h"
#include "collision.h"
#include "bulletlist.h"
#include "exballlist.h"

const int INTERVAL = 100;

class M_testList
{
public:
	M_testList();
	virtual ~M_testList(){}

	void TryGenerateM_test();
	void Move(const Player& player);
	void CheckCollision(M_testCollision collision, Player& player);
	void CheckCollision(BulletList& bulletList, Player& player);
	void CheckAlive(ExballList& exballList);

	void Draw();
	
private:
	std::vector<M_test*> list;
	int count;
};

#endif // !_M_TESTLIST_H_