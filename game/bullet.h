#ifndef _BULLET_H_
#define _BULLET_H_

#include "common_def.h"
#include "player.h"

class Bullet {
public:
	Bullet();
	virtual ~Bullet() {}

	POINT GetPosition(void) const;
	void SetPosition(POINT newPosition);

	DISTANCE GetRepell(void) const;
	_SIZE GetRedius(void) const;
	DISTANCE GetOrbitalRedius() const;

	void Draw() const;

private:
	POINT position = { 0, 0 };
	DISTANCE repell = 100;
	_SIZE redius = 30;
	DISTANCE orbitalRedius = 100;
	//
};

void UpdataBulletPosition(std::vector<Bullet*> bulletList, const Player& player);

#endif // !_BULLET_H_
