#include "experience_ball.h"
constexpr TIME valueClassGap = 60000;//1 min = 60 sec
enum class Value {
	class_1 = 1,
	class_2,
	class_3,
};
const int valueClassNum = 3;

static VALUE UseValue(VALUE value) {
	return 1 << (value);
}
VALUE useValueClass[valueClassNum] = {
	UseValue(VALUE(Value::class_1) - 1),
	UseValue(VALUE(Value::class_2) - 1),
	UseValue(VALUE(Value::class_3) - 1),
};

void TryGenerateExperienceBall(std::vector<ExperienceBall*>& experienceBallList, TIME nowTime, POINT position) {
	VALUE realValue = useValueClass[nowTime / valueClassGap];
	experienceBallList.push_back(new ExperienceBall(realValue, position));
}

ExperienceBall::ExperienceBall(int _value, POINT _position) : value(_value), position(_position) {}
VALUE ExperienceBall::GetValue(void) const { return value; }

bool ExperienceBall::CheckPlayerCollision(const Player& player) const {
	POINT playerPosition = player.GetPosition();
	DISTANCE distance = PLAYERSIZE;
	int deltaX = position.x - playerPosition.x;
	int deltaY = position.y - playerPosition.y;
	int delta = int(sqrt(deltaX * deltaX + deltaY * deltaY));
	if (delta < distance) {
		return true;
	}
	return false;
}

void ExperienceBall::Draw(void) const {
	setfillcolor(GREEN);
	solidcircle(position.x, position.y, 5);
}