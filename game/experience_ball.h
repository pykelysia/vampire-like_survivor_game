#ifndef _EXPERIENCE_BALL_H_
#define _EXPERIENCE_BALL_H_

#include "common_def.h"
#include "player.h"

typedef int VALUE;
constexpr TIME valueClassGap = 60000;//1 min = 60 sec
enum class Value {
	class_1 = 1,
	class_2,
	class_3,
};
const int valueClassNum = 3;
VALUE useValueClass[valueClassNum] = {
	UseValue(VALUE(Value::class_1) - 1),
	UseValue(VALUE(Value::class_2) - 1),
	UseValue(VALUE(Value::class_3) - 1),
};

class ExperienceBall {
public:
	ExperienceBall(int _value, POINT _position): value(_value), position(_position){}
	virtual ~ExperienceBall(){}

	bool CheckCollision(const Player& player) {
		POINT playerPosition = player.GetPosition();
		DISTANCE takeInRedius = player.GetTakeInRedius();
		int deltaX = position.x - playerPosition.x;
		int deltaY = position.y - playerPosition.y;
		double delta = sqrt(deltaX * deltaX + deltaY * deltaY);
		if (delta < takeInRedius) {
			isBeingTakeIn = true;
		}
		return isBeingTakeIn;
	}

	void Move(const Player& player) {
		POINT playerPosition = player.GetPosition();
		int x_dir = playerPosition.x - position.x;
		int y_dir = playerPosition.y - position.y;
		double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
		if (vec_dir != 0) {
			double x_real = x_dir / vec_dir;
			double y_real = y_dir / vec_dir;
			position.x += x_real * 2;
			position.y += y_real * 2;
		}
	}

	bool CheckPlayerCollision(const Player& player) const {
		POINT playerPosition = player.GetPosition();
		DISTANCE distance = PLAYERSIZE;
		int deltaX = position.x - playerPosition.x;
		int deltaY = position.y - playerPosition.y;
		double delta = sqrt(deltaX * deltaX + deltaY * deltaY);
		if (delta < distance) {
			return true;
		}
		return false;
	}

	void Draw(void) const {
		setfillcolor(GREEN);
		solidcircle(position.x, position.y, 5);
	}

	bool isBeingTakeIn = false;

private:
	VALUE value;
	POINT position;
};

VALUE UseValue(VALUE value) {}
void TryGenerateExperienceBall(std::vector<ExperienceBall*>& experienceBallList, TIME nowTime, POINT position) {}

#endif // !_EXPERIENCE_BALL_H_