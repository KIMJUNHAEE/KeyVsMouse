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

void MONSTER::SetMonster(int ntype)
{
	switch (ntype)
	{
	case 1:
		type = 1;
		Xsize = 19, Ysize = 15;
		hp = 200, power = 10, Mspeed = 20, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		break;
	default:
		break;
	}
}

void MONSTER::MoveToPlayer(POINT player1, float DeltaTime) // �÷��̾��� ��ǥ�� �޾� �̵��ϴ� �Լ�
{
	if (hp > 0) {
		float dx, dy;
		float distance;
		float step;
		float MoveX, MoveY;

		dx = player1.x - x;
		dy = player1.y - y;
		distance = sqrt(dx * dx + dy * dy); // �÷��̾���� �Ÿ�

		// �÷��̾ ����� �ָ� ���� �� �̵�
		if (distance >= 5.0f) { // 5�Ÿ� �̻��϶�
			step = Mspeed * DeltaTime;
			MoveX = (dx / distance) * step;
			MoveY = (dy / distance) * step;
			x += MoveX;
			y += MoveY;
		}
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
}

void MONSTER::Update(float DeltaTime) // ����Ÿ�̸� �Լ�
{
	if (Animation <= 2 && hp <= 0) {
		Death();
	}
}

void MONSTER::Draw(HDC hDC) // �׸��� �Լ�
{
	CImage img;
	if (type == 1) {
		if (hp > 0) {
			if (Animation == 1) {
				img.Load(TEXT("Monster_graphics/monster_01_fly_01.png"));
				HDC hSrcDC = img.GetDC();
				img.Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				Animation++;
			}
			else if (Animation == 2) {
				img.Load(TEXT("Monster_graphics/monster_01_fly_02.png"));
				HDC hSrcDC = img.GetDC();
				img.Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				Animation--;
			}
		}
		else {
			TCHAR filePath[64];
			_stprintf_s(filePath, TEXT("Monster_graphics/monster_01_fly_%d.png"), Animation);
			img.Load(filePath);
			HDC hSrcDC = img.GetDC();
			img.Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			Animation++;
			if (Animation > 13) {
				Animation = 0;
			}
		}
	}
	img.ReleaseDC();
	img.Destroy();
}
