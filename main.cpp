#include "TennisGame.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetWindowText("Tennis game");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);

	enum class GameState { TITLE, PLAY, OVER };

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK); //描画先を売ら画面に設定

	Racket racket;
	Ball ball;
	User user;

	GameState state = GameState::TITLE;

	const std::string titleStr = "Tennis Game";
	const std::string instrStr = "Press Enter to Start";
	const std::string quitStr = "Press Q to quit";


	while (1) {
		ClearDrawScreen();

		switch (state) {
		case GameState::TITLE: {
			// タイトル表示（中央上部）
			int tw = GetDrawStringWidth(titleStr.c_str(), static_cast<int>(titleStr.length()));
			int ix = (WIDTH - tw) / 2;
			DrawString(ix, HEIGHT / 4, titleStr.c_str(), 0xFFFFFF);

			// 説明（中央）
			int iw = GetDrawStringWidth(instrStr.c_str(), static_cast<int>(instrStr.length()));
			int ix2 = (WIDTH - iw) / 2;
			DrawString(ix2, HEIGHT / 2, instrStr.c_str(), 0xFFFF00);

			// 終了案内（下部）
			int qw = GetDrawStringWidth(quitStr.c_str(), static_cast<int>(quitStr.length()));
			int qx = (WIDTH - qw) / 2;
			DrawString(qx, HEIGHT - 40, quitStr.c_str(), 0xAAAAAA);

			// ハイスコアを右上に表示
			user.drawHighScore();

			if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
				racket.init();
				ball.init(racket);
				user.init(0);
				state = GameState::PLAY;
			}
			break;
		}

		case GameState::PLAY: {

			racket.draw();
			racket.move();

			ball.move(user);
			ball.draw();

			ball.checkRacket(racket);

			user.drawScore();
			user.drawHighScore();
			break;
		}

		case GameState::OVER: {
			racket.draw();
			ball.draw();
			user.drawScore();



			break;
		}

		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		Sleep(33);

		ScreenFlip();
	}


	DxLib_End();
	return 0;
}