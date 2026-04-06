#include "TennisGame.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	SetWindowText("Tennis game");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK); //描画先を売ら画面に設定

	Racket racket;
	Ball ball;

	racket.init();
	ball.init(racket);

	
	while (1) {
		ClearDrawScreen();

		racket.draw();
		racket.move();

		ball.move();
		ball.draw();

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		Sleep(33);

		ScreenFlip();
	}




	DxLib_End();
	return 0;
}