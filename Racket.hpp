#pragma once

const int racketW = 100;
const int racketH = 10;

const int racketSpeed = 10;

class Racket {
private:
	int x; //ラケットの中心のX座標
	int y; //ラケットの中心のY座標

public:
	void init();
	void draw();
	void move();
};