#include "MONSTER.h"

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

MONSTER::MONSTER() // 디폴트 몬스터 생성자
{
	x = 0, y = 0;
	type = 0;
	Xsize = 0, Ysize = 0;
	hp = 0, power = 0, Mspeed = 0, Aspeed = 0.0f, range = 0;
	DropItem = 0;

	view = down;
	InTimer = 0.0f;

	rect = { 0,0,0,0 };

	Animation = 0;
}

MONSTER::~MONSTER() // 몬스터 소멸자
{

}

void MONSTER::SetSpot(int nx, int ny) // 좌표 설정
{
	x = nx; y = ny;
}

void MONSTER::SetHp(int nhp) // 체력 설정
{
	hp = nhp;
}

void MONSTER::SetPower(int npower) // 공격력 설정
{
	power = npower;
}

void MONSTER::SetMspeed(int nMspeed) // 이동속도 설정
{
	Mspeed = nMspeed;
}

void MONSTER::SetAspeed(int nAspeed) // 공격속도 설정
{
	Aspeed = nAspeed;
}

void MONSTER::SetSize(int n1size, int n2size) // 크기 설정
{
	Xsize = n1size; Ysize = n2size;
}

void MONSTER::SetDropItem(int nDropItem) // 드랍 아이템 시드값 설정
{
	DropItem = nDropItem;
}

void MONSTER::SetView(int nview) // 시점 설정
{
	view = nview;
}

void MONSTER::SetRect()
{
	rect.left = x;
	rect.top = y;
	rect.right = x + Xsize;
	rect.bottom = y + Ysize;
}

void MONSTER::SetMonster(int ntype)
{
	switch (ntype)
	{
	case 1:
		type = 1;
		Xsize = 19, Ysize = 15;
		hp = 200, power = 10, Mspeed = 10, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 0;
		break;
	default:
		break;
	}
}

void MONSTER::MoveToPlayer(POINT player1, float DeltaTime) // 플레이어의 좌표를 받아 이동하는 함수
{
	int dx, dy;
	float distance;
	float step;
	float MoveX, MoveY;

	dx = player1.x - x;
	dy = player1.y - y;
	distance = sqrt(dx * dx + dy * dy); // 플레이어와의 거리

	// 플레이어가 충분히 멀리 있을 때 이동
	if (distance >= 5.0f) { // 5거리 이상일때
		step = Mspeed * DeltaTime;
		MoveX = (dx / distance) * step;
		MoveY = (dy / distance) * step;
		x += MoveX;
		y += MoveY;
	}
}

void MONSTER::MoveToMachine(POINT buliding) // 기물의 좌표를 받아 이동하는 함수
{
}

void MONSTER::Hit(int power) // 피격 함수
{
	hp -= power;
}

void MONSTER::Death() // 사망 함수
{
}

void MONSTER::Update() // 내부타이머 함수
{
}

void MONSTER::Draw(HDC hDC) // 그리기 함수
{
	CImage img;
	switch (type)
	{
	case 1:
		img.Load(TEXT("Monster_graphics/monster_01_fly.png"));
		if (Animation == 0) {
			img.Draw(hDC, x, y, Xsize, Ysize, 7, 7, Xsize, Ysize);
			Animation++;
		}
		else if (Animation == 1) {
			img.Draw(hDC, x, y, Xsize, Ysize, 38, 5, Xsize, Ysize);
			Animation--;
		}
		break;
	default:
		break;
	}
	img.Destroy();
}
