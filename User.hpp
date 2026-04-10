#pragma once

#include <string>

class User {
private:
	int score;
	int highScore;

public:
	User();

	// 初期化（起動時や再初期化）
	void init(int initialScore = 0);

	// ゲッター
	int getScore() const;
	int getHighScore() const;

	// セッター（highScore は自動更新して保存される）
	void setScore(int s);
	void setHighScore(int hs);

	// ヘルパー
	void addScore(int delta);
	void resetScore();

	// ファイル入出力（パスは省略時 "highScore.txt"）
	bool loadHighScore(const std::string& path = "highScore.txt");
	bool saveHighScore(const std::string& path = "highScore.txt") const;
};