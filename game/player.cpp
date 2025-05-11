#include "player.h"

Player::Player(POINT t_position, int t_life, int t_attack) :position(t_position), life(t_life), attack(t_attack){};

POINT Player::GetPosition() const { return position; }

void Player::SetAttack(const ATTACK& newAttack) { attack = newAttack; }
ATTACK Player::GetAttack(void) const { return attack; }

void Player::ProcessEvent(const ExMessage& msg) {

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
//检测移动方向
void Player::Move() {

	int x_dir = is_move_right - is_move_left, y_dir = is_move_down - is_move_up;

	double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
	if (vec_dir != 0) {
		double x_real = x_dir / vec_dir;
		double y_real = y_dir / vec_dir;
		position.x += int(x_real * speed);
		position.y += int(y_real * speed);
	}

	if (position.x + 50 >= WIDTH) position.x = WIDTH - 51;
	if (position.y + 50 >= HIGH) position.y = HIGH - 51;
	if (position.x - 50 <= 0) position.x = 50;
	if (position.y - 50 <= 0) position.y = 50;
}
//移动

void Player::Hurt(const ATTACK& monsterAttack) {
	SetLife(life - monsterAttack);
	printf("受到一次伤害\n");
}//受伤
void Player::SetLife(const LIFE& newlife) { life = newlife; }//改变生命
bool Player::CheckAlive() const { return life > 0; }
//true->alive;
//false->not alive

void Player::AddExperience(const LEVAL& add) {
	SetExperience(experience + add);
	CheckLeval();
}
void Player::CheckLeval() {
	LEVAL levalGap = BASELEVALGAP * (1 << leval);
	if (experience >= levalGap) {
		LEVAL newExperience = experience - levalGap;
		SetExperience(newExperience);
		LevalUp();
	}
}
void Player::SetExperience(LEVAL newExperience) { experience = newExperience; }
void Player::LevalUp(void) { leval++; }
void Player::SetLeval(LEVAL newLaval) { leval = newLaval; }
double Player::GetLevalPercent(void) const { return (1.0 * experience) / (BASELEVALGAP * (1 << leval)); }
LEVAL Player::GetLeval(void) const { return leval; }

void Player::Drow() const {
	circle(position.x, position.y, PLAYERSIZE);
}
