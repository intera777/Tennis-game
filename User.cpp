#include"TennisGame.hpp"
#include<fstream>

User::User()
	: score(0), highScore(0)
{
	loadHighScore("highScore.txt");
}

void User::init(int initialScore) {
	score = initialScore;
	loadHighScore("highScore.txt"); //ファイルからハイスコアを読み込む
}

int User::getScore() const {
	return score;
}

int User::getHighScore() const {
	return highScore;
}

void User::setScore(int s) {
	score = s;
	if (s > highScore) {
		highScore = score;
		//ハイスコア更新時に保存.
		saveHighScore("highScore.txt");
	}
}

void User::setHighScore(int hs) {
	highScore = hs;
	saveHighScore("highScore.txt");
}

void User::resetScore() {
	score = 0;
}

bool User::loadHighScore(const std::string& path) {
	std::ifstream ifs(path);
	if (!ifs.is_open()) {
		highScore = 0;
		return false;
	}
	int value = 0;
	ifs >> value;
	if (ifs.fail()) {
		highScore = 0;
		return false;
	}
	highScore = value;
	return true;
}

bool User::saveHighScore(const std::string& path) const {
	// 後で確認
	std::ofstream ofs(path, std::ios::trunc);
	if (!ofs.is_open()) return false;
	ofs << highScore << '\n';
	return !ofs.fail();
	//後で確認
}

void User::drawScore() {
	int margin = 10;
	int lineSpacing = 22;

	std::string scoreStr = "Score: " + std::to_string(score);
	int w = GetDrawStringWidth(scoreStr.c_str(), static_cast<int>(scoreStr.length()));
	int x = WIDTH - w - margin;
	int y = margin;

	// 背景ボックスのパディング
	int padX = 10;
	int padY = 6;
	int left = x - padX;
	int top = y - padY;
	int right = x + w + padX;
	int bottom = y + lineSpacing + padY;

	// 半透明グレーの背景を描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(left, top, right, bottom, 0x808080, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 影と文字を描画
	DrawString(x + 2, y + 2, scoreStr.c_str(), 0x333333);
	DrawString(x, y, scoreStr.c_str(), 0xFFFFFF);
}

void User::drawHighScore() {
	int margin = 10;
	int lineSpacing = 22;

	std::string highStr = "HighScore: " + std::to_string(highScore);
	int w = GetDrawStringWidth(highStr.c_str(), static_cast<int>(highStr.length()));
	int x = WIDTH - margin - w;
	int y = margin + lineSpacing;

	// 背景ボックスのパディング
	int padX = 10;
	int padY = 6;
	int left = x - padX;
	int top = y - padY;
	int right = x + w + padX;
	int bottom = y + lineSpacing + padY;

	// 半透明グレーの背景を描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(left, top, right, bottom, 0x808080, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 影と文字を描画
	DrawString(x + 2, y + 2, highStr.c_str(), 0x333333);
	DrawString(x, y, highStr.c_str(), 0xFFFF00);
}

void User::drawCredits() {

	std::string str1 = "Music: On-Jin, MaouDamashii";
	int w1, h1, l1;//幅,高さ,行数
	GetDrawStringSize(&w1, &h1, &l1, str1.c_str(), static_cast<int>(str1.length()));
	int x = (WIDTH - w1) / 2;
	int y = 3 * HEIGHT / 4;

	int padX = 15;
	int padY = 8;
	int left = x - padX;
	int right = x + w1 + padX;
	int top = y - padY;
	int bottom = y + h1 + padY;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(left, top, right, bottom, 0x808080, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(x + 2, y + 2, str1.c_str(), 0x333333);
	DrawString(x, y, str1.c_str(), 0xffffff);
}