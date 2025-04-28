#ifndef _BULLET_H_
#define _BULLET_H_

#include "common_def.h"
#include "player.h"

class Bullet {
public:
	Bullet() {}
	~Bullet() {}

	POINT GetPosition(void) const { return position; }
	void SetPosition(POINT newPosition) { position = newPosition; }

	DISTANCE GetRepell(void) const { return repell; }
	_SIZE GetRedius(void) const { return redius; }
	DISTANCE GetOrbitalRedius() const { return orbitalRedius; }

	void Draw() const {
		circle(position.x, position.y, redius);
	}

private:
	POINT position = { 0, 0 };
	DISTANCE repell = 100;
	_SIZE redius = 30;
	DISTANCE orbitalRedius = 100;
	//
};

void UpdataBulletPosition(std::vector<Bullet*> bulletList, const Player& player);

#endif // !_BULLET_H_
