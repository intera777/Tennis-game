#include "TennisGame.hpp"

namespace {
	int g_racketHandle = -1;
	int g_wallHandle = -1;
	int g_playHandle = -1;
}

// init で BGM をロードしたら音量を下げる（例: 96 / 255）
bool Sound::init() {
	free();

	g_racketHandle = LoadSoundMem(racketSE.c_str());
	g_wallHandle = LoadSoundMem(wallSE.c_str());
	g_playHandle = LoadSoundMem(playBGM.c_str());

	// BGM の初期音量を設定（0-255）
	if (g_playHandle != -1) {
		const int playVolume = 160; // 調整可能（小さくするほど静か）
		ChangeVolumeSoundMem(playVolume, g_playHandle);
	}

	// 全てロードできていることを返す
	return (g_racketHandle != -1) && (g_wallHandle != -1) && (g_playHandle != -1);
}

void Sound::playRacket() {
	if (g_racketHandle == -1) return;
	StopSoundMem(g_racketHandle);
	PlaySoundMem(g_racketHandle, DX_PLAYTYPE_BACK);
}

void Sound::playWall() {
	if (g_wallHandle == -1) return;
	StopSoundMem(g_wallHandle);
	PlaySoundMem(g_wallHandle, DX_PLAYTYPE_BACK);
}

void Sound::playPlayLoop() {
	if (g_playHandle == -1) return;
	StopSoundMem(g_playHandle);
	PlaySoundMem(g_playHandle, DX_PLAYTYPE_LOOP);
}

void Sound::stopPlay() {
	if (g_playHandle == -1) return;
	StopSoundMem(g_playHandle);
}

void Sound::free() {
	if (g_racketHandle != -1) {
		StopSoundMem(g_racketHandle);
		DeleteSoundMem(g_racketHandle);
		g_racketHandle = -1;
	}
	if (g_wallHandle != -1) {
		StopSoundMem(g_wallHandle);
		DeleteSoundMem(g_wallHandle);
		g_wallHandle = -1;
	}
	if (g_playHandle != -1) {
		StopSoundMem(g_playHandle);
		DeleteSoundMem(g_playHandle);
		g_playHandle = -1;
	}
}

