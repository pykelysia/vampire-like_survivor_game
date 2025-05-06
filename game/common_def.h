#ifndef _COMMON_DEF_H_
#define _COMMON_DEF_H_

#include<string>
#include<graphics.h>
#include<math.h>
#include<time.h>
#include<vector>

typedef std::string string;

typedef int WIDTH_INT;
typedef int HIGH_INT;

typedef int _SIZE;
typedef int SPEED;
typedef int LIFE;
typedef int ATTACK;
typedef DWORD TIME;
typedef int DISTANCE;
typedef int LEVAL;

constexpr HIGH_INT HIGH = 720;
constexpr WIDTH_INT WIDTH = 1280;
constexpr double pi = 3.1415926;

constexpr _SIZE PLAYERSIZE = 50;
constexpr TIME ATTACK_CD_TIME = 100;

static TIME allStartTime = GetTickCount();

void InitAll(void);

#endif // !_COMMON_DEF_H_