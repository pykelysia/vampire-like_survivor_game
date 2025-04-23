#ifndef _BULLET_H_
#define _BULLET_H_

#include<graphics.h>
#include<vector>

#include "common_def.h"
#include "player.h"

class Bullet {
public:
	Bullet() {}
	~Bullet() {}

	_SIZE GetRedius(void) const { return redius; }
	DISTANCE GetOrbitalRedius() const { return orbitalRedius; }
	//

	POINT GetPosition(void) const { return position; }
	void SetPosition(POINT newPosition) { position = newPosition; }
	//

	void Draw() const {
		circle(position.x, position.y, redius);
	}
	//

private:
	POINT position = { 0, 0 };
	_SIZE redius = 40;
	DISTANCE orbitalRedius = 100;
	//
};

void UpdataBulletPosition(std::vector<Bullet*> bulletList, const Player& player);

#endif // !_BULLET_H_
