#include "IMAGE.h"

CImage IMGfly[14];
CImage IMGparabite[8];
CImage IMGisaac[17];
CImage IMGmom[23];
CImage IMGdeath[12];

void ImageCreate() {
	for (int i = 0; i < 14; i++) {
		TCHAR filePath[50];
		_stprintf_s(filePath, TEXT("Monster_graphics/monster_01_fly_0%d.png"), i);
		IMGfly[i].Load(filePath);
	}
	for (int i = 0; i < 8; i++) {
		TCHAR filePath[50];
		_stprintf_s(filePath, TEXT("Monster_graphics/monster_02_parabite_0%d.png"), i);
		IMGparabite[i].Load(filePath);
	}
	for (int i = 0; i < 5; i++) {
		TCHAR filePath[50];
		_stprintf_s(filePath, TEXT("Monster_graphics/boss_01_isaac_0%d.png"), i);
		IMGisaac[i].Load(filePath);
	}
	for (int i = 0; i < 23; i++) {
		TCHAR filePath[50];
		_stprintf_s(filePath, TEXT("Monster_graphics/boss_02_mom_0%d.png"), i);
		IMGmom[i].Load(filePath);
	}
	for (int i = 0; i < 12; i++) {
		TCHAR filePath[50];
		_stprintf_s(filePath, TEXT("Monster_graphics/effect_01_death_0%d.png"), i);
		IMGdeath[i].Load(filePath);
	}
}

