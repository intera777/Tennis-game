#include "DxLib.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	SetWindowText("Tennis game");
	SetGraphMode(960, 540, 32);
	ChangeWindowMode(TRUE);
	
	if (DxLib_Init() == -1) return -1;
	
	while (1) {
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}




	DxLib_End();
	return 0;
}