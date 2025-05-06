#include "bullet.h"

const int fullAngle = 360;

Bullet::Bullet() {}

POINT Bullet::GetPosition(void) const { return position; }
void Bullet::SetPosition(POINT newPosition) { position = newPosition; }

DISTANCE Bullet::GetRepell(void) const { return repell; }//击退距离
_SIZE Bullet::GetRedius(void) const { return redius; }//子弹半径
DISTANCE Bullet::GetOrbitalRedius() const { return orbitalRedius; }//运行轨道半径
ATTACK Bullet::GatAttack(void) const { return attack; }

void Bullet::Draw() const { circle(position.x, position.y, redius); }
//更新子弹位置