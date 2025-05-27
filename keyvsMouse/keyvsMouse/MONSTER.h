#pragma once
#include <windows.h>
#include <iostream>
#include <cmath>

class MONSTER
{
private:
	int type; // ���� �õ尪
	int x, y; // ��ǥ
	int hp; // ü��
	int power; // ���ݷ�
	int Mspeed; // �̵��ӵ�
	float Aspeed; // ���ݼӵ�
	int range; // ���� ��Ÿ�
	int size; // ���� ũ��
	int DropItem; // ����Ǵ� ������ �õ尪
	int view; // �ü�
	float InTimer; // ���� Ÿ�̸�

	RECT rect; // �׸���� ��ǥ

public:
	MONSTER(); // ����Ʈ ������
	MONSTER(int ntype, int nx, int ny); // (ũ��, ��ǥ) ������
	
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
	void SetRect(int x1, int y1, int x2, int y2); // �׸���� ��ǥ
	void SetRect(RECT nrect); // �׸���� ��ǥ

	// �̵��Լ�
	void MoveToPlayer(POINT player1, float DeltaTime); // �÷��̾� ��ġ �̵� �Լ�
	void MoveToMachine(POINT buliding); // �⹰ ��ġ ��ó �̵� �Լ�

	// �ൿ�Լ�
	void Hit(int power); // �ǰ� �Լ�
	void Death(); // ���� �Լ�

	// �ΰ���� �Լ�
	void Update(); // ��ġ ������Ʈ
	void Draw(HDC hDC); // �׸���
};

