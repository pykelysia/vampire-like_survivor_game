#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "common_def.h"

class Player {
public:
	Player(POINT t_position, int t_life, int t_attack) :
		position(t_position),
		life(t_life),
		attack(t_attack)
	{
	};
	virtual ~Player() {}

	POINT GetPosition() const { return position; }

	void SetAttack(const ATTACK& newAttack) { attack = newAttack; }
	ATTACK GetAttack(void) const { return attack; }

	void ProcessEvent(const ExMessage& msg) {

		if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode)
			{
			case VK_UP:
				is_move_up = true;
				break;
			case VK_LEFT:
				is_move_left = true;
				break;
			case VK_DOWN:
				is_move_down = true;
				break;
			case VK_RIGHT:
				is_move_right = true;
				break;
			default:
				break;
			}
		}
		else if (msg.message == WM_KEYUP) {
			switch (msg.vkcode)
			{
			case VK_UP:
				is_move_up = false;
				break;
			case VK_LEFT:
				is_move_left = false;
				break;
			case VK_DOWN:
				is_move_down = false;
				break;
			case VK_RIGHT:
				is_move_right = false;
				break;
			default:
				break;
			}
		}
	}
	void Move() {

		int x_dir = is_move_right - is_move_left, y_dir = is_move_down - is_move_up;

		double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
		if (vec_dir != 0) {
			double x_real = x_dir / vec_dir;
			double y_real = y_dir / vec_dir;
			position.x += x_real * speed;
			position.y += y_real * speed;
		}

		if (position.x + 50 >= WIDTH) position.x = WIDTH - 51;
		if (position.y + 50 >= HIGH) position.y = HIGH - 51;
		if (position.x - 50 <= 0) position.x = 50;
		if (position.y - 50 <= 0) position.y = 50;
	}

	void Hurt(const ATTACK& monsterAttack) { 
		SetLife(life - monsterAttack);
		printf("受到一次伤害\n");
	}
	void SetLife(const LIFE& newlife) { life = newlife; }

	bool CheckAlive() const { return life > 0; }

	void Drow() const {
		circle(position.x, position.y, PLAYERSIZE);
	}

private:
	POINT position = { 0, 0 };
	SPEED speed = 5;
	LIFE life;
	ATTACK attack;
	bool is_move_up = false,
		is_move_left = false,
		is_move_down = false,
		is_move_right = false;
};

#endif // !_PLAYER_H_
