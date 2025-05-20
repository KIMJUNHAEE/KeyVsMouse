#pragma once
#include <windows.h>
#include <stdlib.h>

enum DIRECTION {
	left = 0, right = 1, up = 2, down = 3
};

class MONSTER
{
private:
	int x, y; // ��ǥ
	int hp; // ü��
	int power; // ���ݷ�
	int Mspeed; // �̵��ӵ�
	int Aspeed; // ���ݼӵ�
	int range; // ���� ��Ÿ�
	int size; // ���� ũ��
	int DropItem; // ����Ǵ� ������ �õ尪
	int view; // �ü�
	int DeltaTime; // ���� Ÿ�̸�

	RECT rect; // �׸���� ��ǥ

public:
	MONSTER(int nhp, int npower, int nx, int ny, int nMspeed, int nAspeed, int nrange, int nsize, int nDropItem); // ������
	
	~MONSTER(); // �Ҹ���

	// �� ���� �Լ�
	void SetSpot(int nx, int ny); // ��ǥ ����
	void SetHp(int nhp); // ü�� ����
	void SetPower(int npower); // ���ݷ� ����
	void SetMspeed(int nMspeed); // �̵��ӵ� ����
	void SetAspeed(int nAspeed); // ���ݼӵ� ����
	void SetSize(int nsize); // ���� ũ�� ����
	void SetDropItem(int nDropItem); // ����Ǵ� ������ �õ尪 ����
	void SetView(int nview); // ���� �ü� ����
	void SetRect(RECT nrect); // �׸���� ��ǥ

	// �̵��Լ�
	void MoveToPlayer(POINT player1); // �÷��̾� ��ġ �̵� �Լ�
	void MoveToMachine(POINT buliding); // �⹰ ��ġ ��ó �̵� �Լ�

	// �ൿ�Լ�
	void Hit(int power); // �ǰ� �Լ�
	void Death(); // ���� �Լ�

	// �ΰ���� �Լ�
	void Update(); // ��ġ ������Ʈ
	void Draw(HDC hDC); // �׸���
};

