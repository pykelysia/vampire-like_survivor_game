#ifndef _EXPERIENCE_BALL_H_
#define _EXPERIENCE_BALL_H_

#include "common_def.h"
#include "character.h"


typedef int VALUE;

class ExperienceBall {
public:
	ExperienceBall(int _value, POINT _position);
	virtual ~ExperienceBall(){}

	VALUE GetValue(void) const;
	POINT GetPosition(void) const;

	void Draw(void) const;

private:
	VALUE value;
	POINT position;
};

#endif // !_EXPERIENCE_BALL_H_