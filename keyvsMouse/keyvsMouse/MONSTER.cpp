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
	Intersect = false;
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

int MONSTER::GetX()
{
	return (x + Xsize) / 2;
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
	case 2:
		type = 2;
		Xsize = 32, Ysize = 32;
		hp = 400, power = 20, Mspeed = 30, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		break;
	case 3:
		type = 3;
		Xsize = 120; Ysize = 49;
		hp = 1000, power = 20, Mspeed = 0, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		InTimer = -1.0f;
		break;
	case 4:
		type = 4;
		Xsize = 32; Ysize = 32;
		hp = 300, power = 20, Mspeed = 100, Aspeed = 1.0f, range = 0;
		DropItem = 1;
		Animation = 1;
		break;
	default:
		break;
	}
}

int MONSTER::MoveToPlayer(POINT player1, RECT head, RECT body, float DeltaTime) // 플레이어의 좌표를 받아 이동하는 함수
{
	if (hp > 0) {
		RECT lprcDest;
		if (IntersectRect(&lprcDest, &rect, &head) || IntersectRect(&lprcDest, &rect, &body)) {
			if (type == 1) { // 파리
				Death();
				return power;
			}
			else if (type == 2) { // 디그다?
				if (Animation == 3 || Animation == 4) {
					Animation = 5;
					InTimer = 0.0f;
				}
			}
			if (Intersect) {
				return 0;
			}
			Intersect = true;
			return power;
		}
		else {
			Intersect = false;
		}

		if (type == 3) {
			if (Animation == 1) {
				x = (head.left + head.right) / 2 - 60;
				y = body.bottom - 20;
				return 0;
			}
			else if (Animation == 2) {
				x = ((head.left + head.right) / 2) - 64;
				y = head.top - 96;
			}
		}

		float dx, dy;
		float distance;
		float step;
		float MoveX, MoveY;

		dx = player1.x - x;
		dy = player1.y - y;
		distance = sqrt(dx * dx + dy * dy); // 플레이어와의 거리

		if (type == 2) {
			if (Animation == 1) {
				if (distance < 200.0f) {
					Animation++;
					InTimer = 0.0f;
				}
			}
			else if (Animation == 2) {
				if (InTimer <= 1000.0f && distance > 200.0f) {
					InTimer = 1000.0f;
				}
			}
			else if (Animation == 3 || Animation == 4) {
				if (distance > 200.0f) {
					Animation = 2;
					InTimer = 1000.0f;
				}
			}
			else if (Animation >= 5 && Animation <= 7) {
				if (InTimer <= 3.0f) {
					return 0;
				}
				else {
					Animation = 2;
					InTimer = 0.0f;
				}
			}
		}
		if (distance > 0.0001f) {
			step = Mspeed * DeltaTime;
			MoveX = (dx / distance) * step;
			MoveY = (dy / distance) * step;
			x += MoveX;
			y += MoveY;
		}
		SetRect();
	}
	return 0;
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
	hp = 0;
	if (type == 1) {
		Animation = 3;
		x = x + (Xsize / 2);
		y = y + (Ysize / 2);
		Xsize = 59, Ysize = 47;
		x = x - (Xsize / 2);
		y = y - (Ysize / 2);
	}
	else { // 파리가 아닐때
		Animation = 101;
		x = x + (Xsize / 2);
		y = y + (Ysize / 2);
		Xsize = 64, Ysize = 64;
		x = x - (Xsize / 2);
		y = y - (Ysize / 2);
	}
}

bool MONSTER::Update(float DeltaTime) // 내부타이머 함수
{
	InTimer += DeltaTime;

	if (Animation == 0 && hp == 0) {
		return true;
	}

	if (type == 1) { // 파리
		if ((Animation == 1 || Animation == 2) && hp <= 0) {
			Death();
		}
	}
	else { // 파리 제외
		if (Animation < 100 && hp <= 0) {
			Death();
		}
		if (type == 3) { // 엄마
			if (Animation == 1) {
				Xsize = 120;
				Ysize = 49;
			}
			if (InTimer >= 2.0f) {
				if (Animation == 2) {
					Xsize = 128;
					Ysize = 16;
				}
				else if (Animation > 2 && Animation < 22) {
					Ysize -= 8;
				}
				else if (Animation == 22) {
					Ysize = 166;
				}
			}
			else {
				if (Animation == 2) {
					Xsize = 128;
					Ysize = 24;
				}
				else if (Animation > 2 && Animation < 22) {
					Ysize += 8;
				}
				else if (Animation == 22) {
					Ysize = 174;
				}
			}
		}
	}
	return false;
}

void MONSTER::Draw(HDC hDC) // 그리기 함수
{
	if (Animation == 0) {
		return;
	}
	if (type == 1) {
		if (hp > 0) {
			// Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom); 디버깅
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
			IMGfly[Animation++].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			if (Animation > 13) {
				Animation = 0;
			}
		}
	}
	else { // 파리가 아닐때
		if (Animation >= 100) {
			int cnt = Animation - 100;
			IMGdeath[cnt].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
			Animation++;
			if (Animation > 111) {
				Animation = 0;
			}
		}
		else {
			if (type == 2) {
				if (hp > 0) {
					if (Animation == 1) {
						IMGparabite[Animation].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
					}
					else if (Animation == 2) {
						IMGparabite[Animation].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
						if (InTimer >= 0.5f && InTimer < 1000.0f) {
							Animation++;
						}
						else if (InTimer >= 1000.5f) {
							Animation--;
						}
					}
					else if (Animation == 3) {
						IMGparabite[Animation++].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
					}
					else if (Animation == 4) {
						IMGparabite[Animation--].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
					}
					else {
						IMGparabite[Animation++].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
						if (Animation > 7) {
							Animation = 5;
						}
					}
				}
			}
			else if (type == 3) {
				if (hp > 0) {
					if (InTimer >= 2.0f) {
						if (Animation == 1) {
							InTimer = -1.0f;
						}
						if (Animation > 1 && Animation <= 22) {
							Animation--;
						}
					}
					else if (InTimer >= 0.0f && InTimer < 2.0f) {
						if (Animation >= 1 && Animation < 22) {
							Animation++;
							InTimer = 0.0f;
						}
					}
					IMGmom[Animation].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
				}
			}
			else if (type == 4) {
				if (hp > 0) {
					if (Animation == 1) {
						IMGboomfly[Animation++].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
					}
					else if (Animation == 2){
						IMGboomfly[Animation--].Draw(hDC, x, y, Xsize, Ysize, 0, 0, Xsize, Ysize);
					}
				}
			}
		}
	}
}
