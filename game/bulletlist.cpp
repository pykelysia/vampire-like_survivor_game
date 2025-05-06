#include "bulletlist.h"

const int fullAngle = 360;

BulletList::BulletList() {
	for (int i = 0;i < 3;i++) {
		list.push_back(new Bullet());
	}
}

void BulletList::UpdataBulletPosition(const Player& player){
	static int angle = 0;
	int deltaAngle = int(360 / (1.0 * list.size()));
	POINT playerPosition = player.GetPosition();
	//
	angle = (angle + 5) % fullAngle;
	int counter = 0;
	for (auto bullet : list) {
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

void BulletList::CheckCollision(BulletCollision collision, M_test* m_test, Player& player){
	for (auto bullet : list) {
		if (collision.CheckCollision(bullet, m_test)) {
			m_test->Hurt(player, *bullet);
		}
	}
}

void BulletList::Draw() {
	for (auto bullet : list) {
		bullet->Draw();
	}
}