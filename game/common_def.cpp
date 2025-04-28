#include "common_def.h"

void InitAll(void) {
	srand(time(NULL));

	initgraph(WIDTH, HIGH, EX_SHOWCONSOLE);
	//initgraph(WIDTH, HIGH);
	
}