#include"TennisGame.hpp"

namespace {
	int g_racketHandle = -1;
	int g_wallHandle = -1;
}

bool Sound::init(const std::string& racketPath, const std::string& wallPath) {
	free();

	g_racketHandle = LoadSoundMem(racketPath.c_str());
	g_wallHandle = LoadSoundMem(wallPath.c_str());

	return (g_racketHandle != -1) && (g_wallHandle != -1);
}

void Sound::playRacket() {
	if (g_racketHandle == -1) return;
	// 再生中なら一度止めて先頭から再生（短い効果音向け）
	StopSoundMem(g_racketHandle);
	PlaySoundMem(g_racketHandle, DX_PLAYTYPE_BACK);
}

void Sound::playWall() {
	if (g_wallHandle == -1) return;
	StopSoundMem(g_wallHandle);
	PlaySoundMem(g_wallHandle, DX_PLAYTYPE_BACK);
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
}

