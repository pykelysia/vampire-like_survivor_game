#include "m_test.h"

const int INTERVAL = 100;

M_test::M_test(int life, int attack) : Monster(life, attack) {
	enum class SpawnEdge
	{
		Up = 0,
		Left,
		Down,
		Right
	};
	SpawnEdge edge = (SpawnEdge)(rand() % 4);
	switch (edge)
	{
	case SpawnEdge::Up:
		position.x = rand() % WIDTH;
		position.y = -M_Width;
		break;
	case SpawnEdge::Left:
		position.x = -M_High;
		position.y = rand() % HIGH;
		break;
	case SpawnEdge::Down:
		position.x = rand() % WIDTH;
		position.y = HIGH + M_Width;
		break;
	case SpawnEdge::Right:
		position.x = WIDTH + M_High;
		position.y = rand() % HIGH;
		break;
	default:
		break;
	}
	printf("生成一只 M_test\n");
}

void M_test::Move(const Player& player) {
	POINT playerPosition = player.GetPosition();
	int x_dir = playerPosition.x - position.x;
	int y_dir = playerPosition.y - position.y;
	double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
	if (vec_dir != 0) {
		double x_real = x_dir / vec_dir;
		double y_real = y_dir / vec_dir;
		position.x += int(x_real * speed);
		position.y += int(y_real * speed);
	}
}

bool M_test::CheckPlayerCollision(const Player& player) {
	POINT playerPosition = player.GetPosition();
	POINT checkPosition = { position.x + M_Width / 2 - playerPosition.x, position.y + M_High / 2 - playerPosition.y };
	int distance = int(sqrt(checkPosition.x * checkPosition.x + checkPosition.y * checkPosition.y));
	if (distance <= PLAYERSIZE) {
		return true;
	}
	return  false;
}

bool M_test::CheckBulletCollision(const Bullet& bullet) {
	POINT bulletPosition = bullet.GetPosition();
	POINT checkPosition = { position.x + M_Width / 2 - bulletPosition.x, position.y + M_High / 2 - bulletPosition.y };
	int distance = int(sqrt(checkPosition.x * checkPosition.x + checkPosition.y * checkPosition.y));
	if (distance <= bullet.GetRedius()) {
		return true;
	}
	return false;
}

void M_test::Drow() const {
	setfillcolor(RED);
	solidrectangle(position.x, position.y, position.x + M_Width, position.y + M_High);
}

void TryGenerateM_test(std::vector<M_test*>& M_test_list) {
	static int counter = 0;
	if ((++counter) % INTERVAL == 0) {
		counter = 0;
		M_test_list.push_back(new M_test(10, 1));
	}
}