#include "IMAGE.h"

CImage IMGfly[14];

void ImageCreate() {
	for (int i = 1; i < 14; i++) {
		TCHAR filePath[50];
		_stprintf_s(filePath, TEXT("Monster_graphics/monster_01_fly_0%d.png"), i);
		IMGfly[i].Load(filePath);
	}
}

