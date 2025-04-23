#include<graphics.h>
#include<math.h>
#include<vector>

#include "common_def.h"
#include "monster.h"
#include "m_test.h"
#include "player.h"
#include "bullet.h"

int main() {

	//initgraph(WIDTH, HIGH, EX_SHOWCONSOLE);
	initgraph(WIDTH, HIGH);

	Player player = Player({ 640, 360 }, 100, 10, "tester");
	std::vector<M_test*> M_test_list;
	std::vector<Bullet*> bulletList;

	for (int i = 0; i < 3;i++) {
		bulletList.push_back(new Bullet());
	}

	ExMessage msg;

	BeginBatchDraw();

	while (true) {
		DWORD start_time = GetTickCount();

		//按键输入
		while (peekmessage(&msg)) {
			player.ProcessEvent(msg);
		}

		//数据处理
		//Player处理
		player.Move();
		UpdataBulletPosition(bulletList, player);

		//Monster处理
		TryGenerateM_test(M_test_list);
		for (auto monster : M_test_list) {
			monster->Move(player);
		}

		//绘图
		setbkcolor(BLACK);
		cleardevice();
		player.Drow();
		int counter = 0;
		for (auto bullet : bulletList) {
			bullet->Draw();
		}
		for (auto monster : M_test_list) {
			monster->Drow();
		}
		for (auto monster : M_test_list) {
			if (monster->CheckPlayerCollision(player)) {
				Sleep(1000);
				return 0;
			}
		}
		for (auto monster : M_test_list) {
			for (auto bullet : bulletList) {
				if (monster->CheckBulletCollision(*bullet)) {
					monster->Hurt();
				}
			}
		}
		for (int i = 0;i < M_test_list.size();i++) {
			M_test* monster = M_test_list[i];
			if (!monster->CheckAlive()) {
				std::swap(M_test_list[i], M_test_list.back());
				M_test_list.pop_back();
				delete monster;
			}
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 144) {
			Sleep(1000 / 144 - delta_time);
		}
	}

	EndBatchDraw();

	return 0;
}