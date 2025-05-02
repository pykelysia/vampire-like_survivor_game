#include "experience_ball.h"

static VALUE UseValue(VALUE value) {
	return 1 << (value);
}

static void TryGenerateExperienceBall(std::vector<ExperienceBall*>& experienceBallList, TIME nowTime, POINT position) {
	VALUE realValue = useValueClass[nowTime % valueClassGap];
	experienceBallList.push_back(new ExperienceBall(realValue, position));
}