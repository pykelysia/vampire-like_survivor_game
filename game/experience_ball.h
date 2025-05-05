#ifndef _EXPERIENCE_BALL_H_
#define _EXPERIENCE_BALL_H_

#include "common_def.h"
#include "player.h"


typedef int VALUE;

class ExperienceBall {
public:
	ExperienceBall(int _value, POINT _position);
	virtual ~ExperienceBall(){}

	VALUE GetValue(void) const;

	bool CheckPlayerCollision(const Player& player) const;

	void Draw(void) const;

private:
	VALUE value;
	POINT position;
};
void TryGenerateExperienceBall(std::vector<ExperienceBall*>& experienceBallList, TIME nowTime, POINT position);


#endif // !_EXPERIENCE_BALL_H_