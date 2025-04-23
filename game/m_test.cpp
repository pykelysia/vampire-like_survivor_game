#include<vector>

#include "m_test.h"

const int INTERVAL = 100;

void TryGenerateM_test(std::vector<M_test*>& M_test_list) {
	static int counter = 0;
	if ((++counter) % INTERVAL == 0) {
		counter = 0;
		M_test_list.push_back(new M_test(1, 1));
	}
}
/*
* 判断并生成怪物
*/