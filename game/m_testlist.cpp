#include "m_testlist.h"
#include "m_test.h"

M_testList::M_testList(){
	count = 0;
}

void M_testList::TryGenerateM_test() {
	count++;
	if (count % INTERVAL == 0) {
		count = 0;
		list.push_back(new M_test(10, 1));
	}
}

void M_testList::Move(const Player& player) {
	for (auto m_test : list) {
		m_test->Move(player);
	}
}

void M_testList::Draw() {
	for (auto m_test : list) {
		m_test->Draw();
	}
}

void M_testList::CheckCollision(M_testCollision collision, Player& player) {
	for (auto m_test : list) {
		if (collision.CheckCollision(m_test, player)) {
			m_test->Attack(&player);
		}
	}
}

void M_testList::CheckCollision(BulletList& bulletList, Player& player) {
	for (auto m_test : list) {
		bulletList.CheckCollision(BulletCollision(), m_test, player);
	}
}

void M_testList::CheckAlive(ExballList& exballList){
	for (int i = 0;i < list.size();i++) {
		M_test* m_test = list[i];
		if (!m_test->CheckAlive()) {
			exballList.TryGenerateExball(m_test);
			std::swap(list[i], list.back());
			list.pop_back();
			delete m_test;
		}
	}
}
