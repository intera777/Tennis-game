#pragma once
#include<string>

namespace Sound {
	bool init(const std::string& racketPath = "sound/racket.mp3", const std::string& wallPath = "sound/wall.mp3");

	// 再生
	void playRacket();
	void playWall();

	// 解放
	void free();
}