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

_SIZE M_test::GetWidth(void) const { return M_Width; }

_SIZE M_test::GetHigh(void) const { return M_High; }

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

void M_test::Draw() const {
	setfillcolor(RED);
	solidrectangle(position.x, position.y, position.x + M_Width, position.y + M_High);
}