#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class SHOP
{
private:
	int ShopNum[5]; // 상점 번호
	int level; // 상점 레벨
	int exp; // 상점 경험치
	int coin; // 코인 보유
	int x[5]; // 상점 번호별 x좌표
	int y[5]; // 상점 번호별 y좌표
	int type[5]; // 몬스터 시드값

	RECT rect[5]; // 상점 그리기용 좌표 배열
public:
	SHOP(); // 생성자

	~SHOP(); // 소멸자

	void SetLevel(int nlevel); // 레벨 설정
	void SetExp(int nexp); // 경험치 설정
	void SetCoin(int ncoin); // 코인 설정
	void SetType(int n, int ntype); // 상점 별 몬스터 시드값 설정
};

