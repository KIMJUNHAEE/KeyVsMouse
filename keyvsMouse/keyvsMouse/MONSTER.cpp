#include "MONSTER.h"

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

MONSTER::MONSTER() // ����Ʈ ���� ������
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

MONSTER::~MONSTER() // ���� �Ҹ���
{

}

void MONSTER::SetSpot(int nx, int ny) // ��ǥ ����
{
	x = nx; y = ny;
}

void MONSTER::SetHp(int nhp) // ü�� ����
{
	hp = nhp;
}

void MONSTER::SetPower(int npower) // ���ݷ� ����
{
	power = npower;
}

void MONSTER::SetMspeed(int nMspeed) // �̵��ӵ� ����
{
	Mspeed = nMspeed;
}

void MONSTER::SetAspeed(int nAspeed) // ���ݼӵ� ����
{
	Aspeed = nAspeed;
}

void MONSTER::SetSize(int n1size, int n2size) // ũ�� ����
{
	Xsize = n1size; Ysize = n2size;
}

void MONSTER::SetDropItem(int nDropItem) // ��� ������ �õ尪 ����
{
	DropItem = nDropItem;
}

void MONSTER::SetView(int nview) // ���� ����
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

int MONSTER::GetX()
{
	return (x+Xsize) / 2;
}
int MONSTER::GetY()
{
	return (y + Ysize) / 2;
}

void MONSTER::SetMonster(int ntype)
{
	switch (ntype)
	{
	case 1:
		type = 1;
		Xsize = 19, Ysize = 15;
		hp = 200, power = 10, Mspeed = 50, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		break;
	default:
		break;
	}
}

void MONSTER::MoveToPlayer(POINT player1, RECT head, RECT body, float DeltaTime) // �÷��̾��� ��ǥ�� �޾� �̵��ϴ� �Լ�
{
	if (hp > 0) {
		RECT lprcDest;
		if (IntersectRect(&lprcDest, &rect, &head) || IntersectRect(&lprcDest, &rect, &body)) {
			Death();
			return;
		}

		float dx, dy;
		float distance;
		float step;
		float MoveX, MoveY;

		dx = player1.x - x;
		dy = player1.y - y;
		distance = sqrt(dx * dx + dy * dy); // �÷��̾���� �Ÿ�

		if (distance > 0.0001f) {
			step = Mspeed * DeltaTime;
			MoveX = (dx / distance) * step;
			MoveY = (dy / distance) * step;
			x += MoveX;
			y += MoveY;
		}
		SetRect();
	}
}

void MONSTER::MoveToMachine(POINT buliding) // �⹰�� ��ǥ�� �޾� �̵��ϴ� �Լ�
{
}

void MONSTER::Hit(int power) // �ǰ� �Լ�
{
	hp -= power;
}

void MONSTER::Death() // ��� �Լ�
{
	Animation = 3;
	hp = 0;
	x = x + (Xsize / 2);
	y = y + (Ysize / 2);
	Xsize = 59, Ysize = 47;
	x = x - (Xsize / 2);
	y = y - (Ysize / 2);

}

bool MONSTER::Update(float DeltaTime) // ����Ÿ�̸� �Լ�
{
	if (Animation == 2 && hp <= 0) {
		Death();
	}
	else if (Animation == 0 && hp == 0) {
		return true;
	}
	return false;
}


void MONSTER::Draw(HDC hDC) // �׸��� �Լ�
{
	if (Animation == 0) {
		return;
	}
	if (type == 1) {
		if (hp > 0) {
			// Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom); �����
			if (Animation == 1) {
				IMGfly[1].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				Animation++;
			}
			else if (Animation == 2) {
				IMGfly[2].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				Animation--;
			}
		}
		else {
			IMGfly[Animation].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			Animation++;
			if (Animation > 13) {
				Animation = 0;
			}
		}
	}
}
