#include<iostream>
#include<graphics.h>
#include<string>
#include<math.h>
#include<vector>

#define HIGH 720
#define WIDTH 1280

#define PLAYERSIZE 50

using namespace std;

class Player {
public:
	Player(int t_x, int t_y, int t_life, int t_attack, string t_name) :x(t_x), y(t_y), life(t_life), attack(t_attack), name(t_name) {};
	virtual ~Player() {}

	int Get_x() { return x; }
	void Set_x(int t_x) { x = t_x; }

	int Get_y() { return y; }
	void Set_y(int t_y) { y = t_y; }

	string Get_name() { return name; }
	void Set_name(string t_name) { name = t_name; }

	void ProcessEvent(ExMessage msg) {

		if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode)
			{
			case VK_UP:
				is_move_up = true;
				break;
			case VK_LEFT:
				is_move_left = true;
				break;
			case VK_DOWN:
				is_move_down = true;
				break;
			case VK_RIGHT:
				is_move_right = true;
				break;
			default:
				break;
			}
		}
		else if (msg.message == WM_KEYUP) {
			switch (msg.vkcode)
			{
			case VK_UP:
				is_move_up = false;
				break;
			case VK_LEFT:
				is_move_left = false;
				break;
			case VK_DOWN:
				is_move_down = false;
				break;
			case VK_RIGHT:
				is_move_right = false;
				break;
			default:
				break;
			}
		}
	}

	void Move() {

		int x_dir = is_move_right - is_move_left, y_dir = is_move_down - is_move_up;

		double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
		if (vec_dir != 0) {
			double x_real = x_dir / vec_dir;
			double y_real = y_dir / vec_dir;
			x += x_real * speed;
			y += y_real * speed;
		}

		if (x + 50 >= WIDTH) x = WIDTH - 51;
		if (y + 50 >= HIGH) y = HIGH - 51;
		if (x - 50 <= 0) x = 50;
		if (y - 50 <= 0) y = 50;

	}

	void Drow() {
		circle(x, y, PLAYERSIZE);
	}

private:
	int x;
	int y;
	int speed = 5;
	int life;
	int attack;
	bool is_move_up = false,
		is_move_left = false,
		is_move_down = false,
		is_move_right = false;
	string name;
};

class Bullet {
public:
	Bullet(){}
	~Bullet(){}

	void Draw(){}

private:

};

class Monster {
public:
	Monster(int t_life, int t_attack) : life(t_life), attack(t_attack) {}

	bool CheckPlayerCollision(const Player& player){
		return false;
	}
	
	void Move(const Player& player){}

	void Drow() {}

	virtual ~Monster() {}

protected:
	int life;
	int attack;
	POINT position = { 0,0 };
};

class M_test :public Monster {
public:
	M_test(int life, int attack): Monster(life,attack){
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
	}
	void Move(const Player& player) {
		Player t_player = player;
		int x_dir = t_player.Get_x() - position.x;
		int y_dir = t_player.Get_y() - position.y;
		double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
		if (vec_dir != 0) {
			double x_real = x_dir / vec_dir;
			double y_real = y_dir / vec_dir;
			position.x += x_real * speed;
			position.y += y_real * speed;
		}
	}
	bool CheckPlayerCollision(const Player& player) {
		Player t_player = player;
		POINT checkPosition = { position.x + M_Width / 2 - t_player.Get_x(),position.y + M_High / 2 - t_player.Get_y() };
		int distance = sqrt(checkPosition.x * checkPosition.x + checkPosition.y * checkPosition.y);
		if (distance <= PLAYERSIZE) {
			return true;
		}
		return  false;
	}
	void Drow() {
		setfillcolor(RED);
		solidrectangle(position.x, position.y, position.x + M_Width, position.y + M_High);
	}

private:
	int M_Width = 40;
	int M_High = 50;
	int speed = 3;
	POINT position = { 0,0 };
};

void TryGenerateM_test(std::vector<M_test*>& M_test_list) {
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0) {
		counter = 0;
		M_test_list.push_back(new M_test(1, 1));
	}
}


int main() {

	initgraph(WIDTH, HIGH);

	Player player = Player(640, 360, 100, 10, "tester");
	std::vector<M_test*> M_test_list;

	ExMessage msg;

	BeginBatchDraw();

	while (true) {
		DWORD start_time = GetTickCount();

		//按键输入
		while (peekmessage(&msg)) {
			player.ProcessEvent(msg);
		}

		//数据处理
		//Monster处理
		TryGenerateM_test(M_test_list);
		for (auto monster : M_test_list) {
			monster->Move(player);
		}

		//Player处理
		player.Move();

		//绘图
		setbkcolor(BLACK);
		cleardevice();
		for (auto monster : M_test_list) {
			monster->Drow();
		}
		player.Drow();
		for (auto monster : M_test_list) {
			if (monster->CheckPlayerCollision(player)) {
				Sleep(1000);
				return 0;
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