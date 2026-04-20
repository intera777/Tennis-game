#include "TennisGame.hpp"

// Font handles for larger text
static int g_titleFont = -1;
static int g_gameOverFont = -1;
static int g_smallFont = -1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetOutApplicationLogValidFlag(FALSE);

	SetWindowText("Tennis game");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);

	enum class GameState { TITLE, PLAY, OVER };

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定

	// フォント作成（大きめのタイトル・ゲームオーバー用と小さい説明用）
	g_titleFont = CreateFontToHandle("Meiryo", 72, 0, DX_FONTTYPE_ANTIALIASING);
	g_gameOverFont = CreateFontToHandle("Meiryo", 64, 0, DX_FONTTYPE_ANTIALIASING);
	g_smallFont = CreateFontToHandle("Meiryo", 28, 0, DX_FONTTYPE_ANTIALIASING);

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
         int tw = GetDrawStringWidthToHandle(titleStr.c_str(), static_cast<int>(titleStr.length()), g_titleFont);
			int ix = (WIDTH - tw) / 2;
			DrawStringToHandle(ix, HEIGHT / 4, titleStr.c_str(), 0xFFFFFF, g_titleFont);

			// 説明（中央）
         int iw = GetDrawStringWidthToHandle(instrStr.c_str(), static_cast<int>(instrStr.length()), g_smallFont);
			int ix2 = (WIDTH - iw) / 2;
			DrawStringToHandle(ix2, HEIGHT / 2, instrStr.c_str(), 0xFFFF00, g_smallFont);

			// 終了案内（下部）
           int qw = GetDrawStringWidthToHandle(quitStr.c_str(), static_cast<int>(quitStr.length()), g_smallFont);
			int qx = (WIDTH - qw) / 2;
			DrawStringToHandle(qx, HEIGHT - 40, quitStr.c_str(), 0xAAAAAA, g_smallFont);

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
			user.drawCredits();

			// 再スタート
			if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
				racket.init();
				ball.init(racket);
				user.init(0);
				state = GameState::PLAY;
			}
			// Q で終了
            if (CheckHitKey(KEY_INPUT_Q) == 1) {
				if (g_titleFont != -1) DeleteFontToHandle(g_titleFont);
				if (g_gameOverFont != -1) DeleteFontToHandle(g_gameOverFont);
				if (g_smallFont != -1) DeleteFontToHandle(g_smallFont);
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
   int ow = GetDrawStringWidthToHandle(overStr.c_str(), static_cast<int>(overStr.length()), g_gameOverFont);
	DrawStringToHandle((WIDTH - ow) / 2, HEIGHT / 3, overStr.c_str(), 0xFF0000, g_gameOverFont);

	std::string retryStr = "Press ENTER to Restart or Q to Quit";
	int rw = GetDrawStringWidthToHandle(retryStr.c_str(), static_cast<int>(retryStr.length()), g_smallFont);
	DrawStringToHandle((WIDTH - rw) / 2, HEIGHT / 2, retryStr.c_str(), 0xFFFF00, g_smallFont);
}