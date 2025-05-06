#include "collision.h"

bool M_testCollision::CheckCollision(M_test* m_test, Player& player) {
	POINT playerPosition = player.GetPosition();
	POINT position = m_test->GetPosition();
	_SIZE M_Width = m_test->GetWidth();
	_SIZE M_High = m_test->GetHigh();
	POINT checkPosition = { position.x + M_Width / 2 - playerPosition.x, position.y + M_High / 2 - playerPosition.y };
	int distance = int(sqrt(checkPosition.x * checkPosition.x + checkPosition.y * checkPosition.y));
	if (distance <= PLAYERSIZE) {
		return true;
	}
	return  false;
}

bool BulletCollision::CheckCollision(Bullet* bullet, M_test* m_test){
	POINT bulletPosition = bullet->GetPosition();
	POINT position = m_test->GetPosition();
	_SIZE M_Width = m_test->GetWidth();
	_SIZE M_High = m_test->GetHigh();
	POINT checkPosition = { position.x + M_Width / 2 - bulletPosition.x, position.y + M_High / 2 - bulletPosition.y };
	int distance = int(sqrt(checkPosition.x * checkPosition.x + checkPosition.y * checkPosition.y));
	if (distance <= bullet->GetRedius()) {
		return true;
	}
	return false;
}

bool ExballCollision::CheckCollision(ExperienceBall* exball, const Player& player){
	POINT playerPosition = player.GetPosition();
	DISTANCE distance = PLAYERSIZE;
	POINT position = exball->GetPosition();
	int deltaX = position.x - playerPosition.x;
	int deltaY = position.y - playerPosition.y;
	int delta = int(sqrt(deltaX * deltaX + deltaY * deltaY));
	if (delta < distance) {
		return true;
	}
	return false;
}
