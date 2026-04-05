#include "TennisGame.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	SetWindowText("Tennis game");
	SetGraphMode(960, 540, 32);
	ChangeWindowMode(TRUE);
	
	if (DxLib_Init() == -1) return -1;

	Racket racket;
	racket.init();

	
	while (1) {
		ClearDrawScreen();

		racket.draw();
		racket.move();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		Sleep(33);

		ScreenFlip();
	}




	DxLib_End();
	return 0;
}