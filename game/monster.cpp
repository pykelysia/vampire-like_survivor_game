#include "monster.h"

POINT Monster::GetPosition(void) const { return position; };

void Monster::Attack(Player* player) {
	TIME newAttackTime = GetTickCount();
	if (newAttackTime - lastAttackTime > ATTACK_CD_TIME || lastAttackTime == 0) {
		SetLastAttackTime(newAttackTime);
		player->Hurt(attack);
	}
}
void Monster::SetLastAttackTime(TIME newTime) { lastAttackTime = newTime; }

void Monster::Hurt(const Player& player, const Bullet& bullet) {
	life -= player.GetAttack();
	if (!CheckAlive()) {
		return;
	}
	DISTANCE repell = bullet.GetRepell();
	POINT bulletPosition = player.GetPosition();
	int x_dir = position.x - bulletPosition.x;
	int y_dir = position.y - bulletPosition.y;
	double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
	if (vec_dir != 0) {
		double x_real = x_dir / vec_dir;
		double y_real = y_dir / vec_dir;
		position.x += int(x_real * repell);
		position.y += int(y_real * repell);
	}
}
bool Monster::CheckAlive(void) const { return life > 0; }