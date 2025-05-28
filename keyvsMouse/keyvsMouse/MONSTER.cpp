#include "MONSTER.h"

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

MONSTER::MONSTER() // 디폴트 몬스터 생성자
{
	type = 0;
	x = 0, y = 0;
	hp = 100, power = 10, Mspeed = 10, Aspeed = 1.0f, range = 50;
	size = 10, DropItem = 0;
	view = down;
	//DeltaTime = 0.0f;
	rect = { 0,0,0,0 };
}

MONSTER::MONSTER(int ntype, int nx, int ny) // 몬스터 생성자 (시드, 좌표)
{
	type = ntype;
	x = nx, y = ny;
	view = down;
	//DeltaTime = 0;

	switch (type) {
	case 1:
		hp = 200, power = 10, Mspeed = 10, Aspeed = 1.0f, range = 50;
		size = 20, DropItem = 1;
		break;
	default:
		hp = 100, power = 10, Mspeed = 10, Aspeed = 1.0f, range = 50;
		size = 10, DropItem = 0;
		break;
	}

	rect.left = x - size;
	rect.top = y - size;
	rect.right = x + size;
	rect.bottom = y + size;
}

MONSTER::~MONSTER() // 몬스터 소멸자
{

}

void MONSTER::SetSpot(int nx, int ny) // 좌표 설정
{
	x = nx;
	y = ny;
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

void MONSTER::SetSize(int nsize) // 크기 설정
{
	size = nsize;
}

void MONSTER::SetDropItem(int nDropItem) // 드랍 아이템 시드값 설정
{
	DropItem = nDropItem;
}

void MONSTER::SetView(int nview) // 시점 설정
{
	view = nview;
}

void MONSTER::SetRect(int x1, int y1, int x2, int y2) // 그리기 및 충돌처리 좌표 설정 (int)
{
	rect.left = x1 - size;
	rect.top = y1 - size;
	rect.right = x1 + size;
	rect.bottom = y1 + size;
}

void MONSTER::SetRect(RECT nrect) // 그리기 및 충돌처리 좌표 설정 (rect)
{
	rect.left = nrect.left;
	rect.top = nrect.top;
	rect.right = nrect.right;
	rect.bottom = nrect.bottom;
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
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
}
