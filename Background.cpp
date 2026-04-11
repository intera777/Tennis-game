#include"TennisGame.hpp"

Background::Background()
	: handle(-1)
{
	free();
}

bool Background::init(const std::string& path) {
	if (handle != -1) {
		DeleteGraph(handle);
		handle = -1;
	}
	handle = LoadGraph(path.c_str());
	return handle != -1;
}

void Background::draw() const {
	if (handle == -1) return;
	// 画面サイズに合わせて拡大描画（左上原点）
	DrawExtendGraph(0, 0, WIDTH, HEIGHT, handle, TRUE);
}

void Background::free() {
	if (handle != -1) {
		DeleteGraph(handle);
		handle = -1;
	}
}