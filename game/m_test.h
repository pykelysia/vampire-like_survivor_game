#ifndef _M_TEST_H_
#define _M_TEST_H_

#include<graphics.h>
#include<math.h>
#include <vector>

#include "common_def.h"
#include "monster.h"
#include "player.h"
#include "bullet.h"

class M_test :public Monster {
public:
	M_test(int life, int attack) : Monster(life, attack) {
		enum class SpawnEdge
		{
			Up = 0,
			Left,
			Down,
			Right
		};
		//

		SpawnEdge edge = (SpawnEdge)(rand() % 4);

		switch (edge)
		{
		case SpawnEdge::Up:
			position.x = rand() % WIDTH;
			position.y = -M_Width;
			break;
		case SpawnEdge::Left:
			position.x = -M_High;
			position.y = rand() % HIGH;
			break;
		case SpawnEdge::Down:
			position.x = rand() % WIDTH;
			position.y = HIGH + M_Width;
			break;
		case SpawnEdge::Right:
			position.x = WIDTH + M_High;
			position.y = rand() % HIGH;
			break;
		default:
			break;
		}
		//
	}
	//

	void Move(const Player& player) {
		Player t_player = player;
		POINT playerPosition = t_player.GetPosition();
		int x_dir = playerPosition.x - position.x;
		int y_dir = playerPosition.y - position.y;
		double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
		if (vec_dir != 0) {
			double x_real = x_dir / vec_dir;
			double y_real = y_dir / vec_dir;
			position.x += x_real * speed;
			position.y += y_real * speed;
		}
		//s
	}
	//

	bool CheckPlayerCollision(const Player& player) {
		POINT playerPosition = player.GetPosition();
		POINT checkPosition = { position.x + M_Width / 2 - playerPosition.x, position.y + M_High / 2 - playerPosition.y };
		int distance = sqrt(checkPosition.x * checkPosition.x + checkPosition.y * checkPosition.y);
		if (distance <= PLAYERSIZE) {
			return true;
		}
		return  false;
	}
	//

	bool CheckBulletCollision(const Bullet& bullet) {
		POINT bulletPosition = bullet.GetPosition();
		POINT checkPosition = { position.x + M_Width / 2 - bulletPosition.x, position.y + M_High / 2 - bulletPosition.y };
		int distance = sqrt(checkPosition.x * checkPosition.x + checkPosition.y * checkPosition.y);
		if (distance <= bullet.GetRedius()) {
			return true;
		}
		return false;
	}
	//

	void Hurt(void) {
		life = 0;
	}

	bool CheckAlive(void) const {
		return life > 0;
	}

	void Drow() const {
		printf("1");
		setfillcolor(RED);
		solidrectangle(position.x, position.y, position.x + M_Width, position.y + M_High);
	}
	//

private:
	_SIZE M_Width = 40;
	_SIZE M_High = 50;
	SPEED speed = 3;
	LIFE life = 1;
	POINT position = { 0,0 };
	//
};

void TryGenerateM_test(std::vector<M_test*>& M_test_list);

#endif // !_M_TEST_H_
