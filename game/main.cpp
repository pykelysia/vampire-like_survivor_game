#include<iostream>
#include<graphics.h>
#include<string>
#include<math.h>
#include<vector>

#include "common_def.h"

class Player {
public:
	Player(POINT t_position, int t_life, int t_attack, string t_name) :
		position(t_position),
		life(t_life),
		attack(t_attack),
		name(t_name)
		{};
	virtual ~Player() {}

	POINT GetPosition() const { return position; }
	//

	string GetName() const { return name; }
	void SetName(string t_name) { name = t_name; }
	//

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
	//

	void Move() {

		int x_dir = is_move_right - is_move_left, y_dir = is_move_down - is_move_up;

		double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
		if (vec_dir != 0) {
			double x_real = x_dir / vec_dir;
			double y_real = y_dir / vec_dir;
			position.x += x_real * speed;
			position.y += y_real * speed;
		}
		//

		if (position.x + 50 >= WIDTH) position.x = WIDTH - 51;
		if (position.y + 50 >= HIGH) position.y = HIGH - 51;
		if (position.x - 50 <= 0) position.x = 50;
		if (position.y - 50 <= 0) position.y = 50;
		//

	}

	void Drow() const {
		circle(position.x, position.y, PLAYERSIZE);
	}
	//

private:
	POINT position = { 0, 0 };
	SPEED speed = 5;
	LIFE life;
	ATTACK attack;
	bool is_move_up = false,
		is_move_left = false,
		is_move_down = false,
		is_move_right = false;
	//
	string name;
};

class Bullet {
public:
	Bullet(){}
	~Bullet(){}

	_SIZE GetRedius(void) const { return redius; }
	DISTANCE GetOrbitalRedius() const { return orbitalRedius; }
	//

	POINT GetPosition(void) const { return position; }
	void SetPosition(POINT newPosition) { position = newPosition; }
	//

	void Draw() const {
		circle(position.x, position.y, redius);
	}
	//

private:
	POINT position = { 0, 0 };
	_SIZE redius = 40;
	DISTANCE orbitalRedius = 100;
	//
};

class Monster {
public:
	Monster(int t_life, int t_attack) : life(t_life), attack(t_attack) {}
	virtual ~Monster() {}

	bool CheckPlayerCollision(){return false;}
	//

	bool CheckBulletCollision() {return false;}
	//
	
	void Move(const Player& player){}
	//

	void Drow() {}
	//

protected:
	LIFE life;
	ATTACK attack;
	POINT position = { 0,0 };
	//
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
		//

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
		//
	}
	//

	void Move(const Player& player) {
		Player t_player = player;
		POINT playerPosition = t_player.GetPosition();
		int x_dir = playerPosition.x - position.x;
		int y_dir = playerPosition.y - position.y;
		double vec_dir = sqrt(x_dir * x_dir + y_dir * y_dir);
		if (vec_dir != 0) {
			double x_real = x_dir / vec_dir;
			double y_real = y_dir / vec_dir;
			position.x += x_real * speed;
			position.y += y_real * speed;
		}
		//s
	}
	//

	bool CheckPlayerCollision(const Player& player) {
		POINT playerPosition = player.GetPosition();
		POINT checkPosition = { position.x + M_Width / 2 - playerPosition.x, position.y + M_High / 2 - playerPosition.y };
		int distance = sqrt(checkPosition.x * checkPosition.x + checkPosition.y * checkPosition.y);
		if (distance <= PLAYERSIZE) {
			return true;
		}
		return  false;
	}
	//

	bool CheckBulletCollision(const Bullet& bullet) {
		POINT bulletPosition = bullet.GetPosition();
		POINT checkPosition = { position.x + M_Width / 2 - bulletPosition.x, position.y + M_High / 2 - bulletPosition.y };
		int distance = sqrt(checkPosition.x * checkPosition.x + checkPosition.y * checkPosition.y);
		if (distance <= bullet.GetRedius()) {
			return true;
		}
		return false;
	}
	//

	void Hurt(void) {
		life = 0;
	}

	bool CheckAlive(void) const {
		return life > 0;
	}

	void Drow() const {
		setfillcolor(RED);
		solidrectangle(position.x, position.y, position.x + M_Width, position.y + M_High);
	}
	//

private:
	_SIZE M_Width = 40;
	_SIZE M_High = 50;
	SPEED speed = 3;
	LIFE life = 1;
	POINT position = { 0,0 };
	//
};

static void TryGenerateM_test(std::vector<M_test*>& M_test_list) {
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0) {
		counter = 0;
		M_test_list.push_back(new M_test(1, 1));
	}
}
/*
* 判断并生成怪物
*/

static void UpdataBulletPosition(std::vector<Bullet*> bulletList, const Player& player) {
	const int fullAngle = 360;
	static int angle = 0;
	int deltaAngle = 360 / (1.0 * bulletList.size());
	POINT playerPosition = player.GetPosition();
	//
	angle = (angle + 2) % fullAngle;
	int counter = 0;
	for (auto bullet : bulletList) {
		double positionAngle = (1.0 * angle + counter * deltaAngle) / fullAngle ;
		//printf("%lf\n", positionAngle);
		positionAngle = positionAngle * (2 * pi);
		DISTANCE distance = bullet->GetOrbitalRedius();
		POINT position = {
			int(playerPosition.x + distance * cos(positionAngle)),
			int(playerPosition.y + distance * sin(positionAngle))
		};
		bullet->SetPosition(position);
		counter++;
	}
}
/*
* 更新子弹位置
*/

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