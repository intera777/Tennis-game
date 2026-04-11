#pragma once
#include<string>

class Background {
private:
	int handle;
public:
	Background();

	bool init(const std::string& path = "image/img1.png");

	// 描画（画面全体に拡大描画）
	void draw() const;

	void free();
};
