#include<vector>
#include<math.h>

#include "bullet.h"
#include "player.h"

const int fullAngle = 360;

void UpdataBulletPosition(std::vector<Bullet*> bulletList, const Player& player) {
	static int angle = 0;
	int deltaAngle = 360 / (1.0 * bulletList.size());
	POINT playerPosition = player.GetPosition();
	//
	angle = (angle + 5) % fullAngle;
	int counter = 0;
	for (auto bullet : bulletList) {
		double positionAngle = (1.0 * angle + counter * deltaAngle) / fullAngle;
		//printf("%lf\n", positionAngle);
		positionAngle = positionAngle * (2 * pi);
		DISTANCE distance = bullet->GetOrbitalRedius();
		POINT position = {
			int(playerPosition.x + distance * cos(positionAngle)),
			int(playerPosition.y + distance * sin(positionAngle))
		};
		bullet->SetPosition(position);
		counter++;
	}
}
/*
* 更新子弹位置
*/