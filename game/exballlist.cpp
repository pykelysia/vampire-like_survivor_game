#include "exballlist.h"

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

ExballList::ExballList(){}

void ExballList::TryGenerateExball(const M_test* m_test){
	TIME nowTime = GetTickCount() - allStartTime;
	VALUE realValue = useValueClass[nowTime / valueClassGap];
	list.push_back(new ExperienceBall(realValue, m_test->GetPosition()));
}

void ExballList::CheckAlive(Player& player){
	ExballCollision exballCollision = ExballCollision();
	for (int i = 0;i < list.size();i++) {
		ExperienceBall* experienceBall = list[i];
		if (exballCollision.CheckCollision(experienceBall, player)) {
			printf("检测到经验球与玩家碰撞");
			std::swap(list[i], list.back());
			list.pop_back();
			player.AddExperience(experienceBall->GetValue());
			delete experienceBall;
		}
	}
}

void ExballList::Draw(void){
	for (auto exball : list) {
		exball->Draw();
	}
}
