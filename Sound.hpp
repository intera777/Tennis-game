#pragma once
#include<string>

const std::string racketSE= "sound/racket.mp3";
const std::string wallSE= "sound/wall.mp3";
const std::string playBGM="sound/play.mp3";

namespace Sound {
	bool init();

	// 再生
	void playRacket();
	void playWall();
	void playPlayLoop();
	void stopPlay();

	// 解放
	void free();
}