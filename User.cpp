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