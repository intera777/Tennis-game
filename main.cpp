#include "TennisGame.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetWindowText("Tennis game");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);

	enum class GameState { TITLE, PLAY, OVER };

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定

	Racket racket;
	Ball ball;
	User user;
	Background background;

	GameState state = GameState::TITLE;

	const std::string titleStr = "Tennis Game";
	const std::string instrStr = "Press Enter to Start";
	const std::string quitStr = "Press Q to quit";

	Sound::init();

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
				background.init("image/img9.png");
				Sound::playPlayLoop();
				state = GameState::PLAY;
			}
			break;
		}

		case GameState::PLAY: {

			background.draw();

			racket.draw();
			racket.move();

			ball.move(user);

			ball.draw();
			ball.checkRacket(racket, user);

			user.drawScore();
			user.drawHighScore();
			
			// ボールが下端到達でゲームオーバーへ遷移
			if (ball.isOutOfBottom()) {
				Sound::stopPlay();
				state = GameState::OVER;
				// 必要ならハイスコア更新をここで確定（User::setScore 等で既に保存されていれば不要）
				break;
			}
			break;
		}

		case GameState::OVER: {
			// 背景と最終状態を表示
			background.draw();

			// スコア表示等
			user.drawScore();
			user.drawHighScore();

			// Game Over メッセージ
			drawGameOverMassages();

			// 再スタート
			if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
				racket.init();
				ball.init(racket);
				user.init(0);
				state = GameState::PLAY;
			}
			// Q で終了
			if (CheckHitKey(KEY_INPUT_Q) == 1) {
				DxLib_End();
				return 0;
			}

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

void drawGameOverMassages() {
	std::string overStr = "GAME OVER";
	int ow = GetDrawStringWidth(overStr.c_str(), static_cast<int>(overStr.length()));
	DrawString((WIDTH - ow) / 2, HEIGHT / 3, overStr.c_str(), 0xFF0000);

	std::string retryStr = "Press ENTER to Restart or Q to Quit";
	int rw = GetDrawStringWidth(retryStr.c_str(), static_cast<int>(retryStr.length()));
	DrawString((WIDTH - rw) / 2, HEIGHT / 2, retryStr.c_str(), 0xFFFF00);
}