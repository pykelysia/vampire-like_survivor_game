#ifndef _BULLET_H_
#define _BULLET_H_

#include "common_def.h"
#include "character.h"

class Bullet {
public:
	Bullet();
	virtual ~Bullet() {}

	POINT GetPosition(void) const;
	void SetPosition(POINT newPosition);

	DISTANCE GetRepell(void) const;
	_SIZE GetRedius(void) const;
	DISTANCE GetOrbitalRedius() const;
	ATTACK GatAttack(void) const;

	void Draw() const;

private:
	POINT position = { 0, 0 };
	ATTACK attack = 1;
	DISTANCE repell = 100;
	_SIZE redius = 30;
	DISTANCE orbitalRedius = 100;
	//
};

#endif // !_BULLET_H_
