#pragma once
#include <windows.h>
#include <iostream>
#include <cmath>
#include <atlImage.h>
#include "IMAGE.h"

class MONSTER
{
private:
	float x, y; // ���� �»�� ��ǥ
	int type; // ���� �õ尪
	int Xsize; // ���� x ũ��
	int Ysize; // ���� y ũ��
	int power; // ���ݷ�
	int Mspeed; // �̵��ӵ�
	float Aspeed; // ���ݼӵ�
	int range; // ���� ��Ÿ�
	int DropItem; // ����Ǵ� ������ �õ尪
	int view; // �ü�
	float InTimer; // ���� Ÿ�̸�
	int Animation; // �ִϸ��̼� �׸� ��ȣ
	bool Intersect; // ���� ����

public:

	RECT rect; // �׸���� ��ǥ
	int hp; // ü��
	MONSTER(); // ����Ʈ ������
	~MONSTER(); // �Ҹ���

	// �� ���� �Լ�
	void SetSpot(int nx, int ny); // ��ǥ ����
	void SetHp(int nhp); // ü�� ����
	void SetPower(int npower); // ���ݷ� ����
	void SetMspeed(int nMspeed); // �̵��ӵ� ����
	void SetAspeed(int nAspeed); // ���ݼӵ� ����
	void SetSize(int n1size, int n2size); // ���� ũ�� ����
	void SetDropItem(int nDropItem); // ����Ǵ� ������ �õ尪 ����
	void SetView(int nview); // ���� �ü� ����
	void SetRect(); // �׸����

	// �� ���� �Լ�
	int GetX();
	int GetY();

	// ���� Ÿ�� ����
	void SetMonster(int type);

	// �̵��Լ�
	int MoveToPlayer(POINT player1, RECT head, RECT body, float DeltaTime); // �÷��̾� ��ġ �̵� �Լ�
	void MoveToMachine(POINT buliding); // �⹰ ��ġ ��ó �̵� �Լ�

	// �ൿ�Լ�
	void Hit(int power); // �ǰ� �Լ�
	void Death(); // ���� �Լ�

	// �ΰ���� �Լ�
	bool Update(float DeltaTime); // ������Ʈ
	void Draw(HDC hDC); // �׸���


};

