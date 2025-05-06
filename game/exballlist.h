#ifndef _EXBALLLIST_H_
#define _EXBALLLIST_H_

#include "character.h"
#include "experience_ball.h"
#include "collision.h"

class ExballList
{
public:
	ExballList();
	virtual ~ExballList(){}

	void TryGenerateExball(const M_test* m_test);
	void CheckAlive(Player& player);

	void Draw(void);

private:
	std::vector<ExperienceBall*> list;
};

#endif // !_EXBALLLIST_H_