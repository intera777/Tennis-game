#pragma once

const int racketW = 100;
const int racketH = 10;

const int racketSpeed = 10;

class Racket {
private:
	float x; //ラケットの中心のX座標
	float y; //ラケットの中心のY座標

public:
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	void init();
	void draw();
	void move();
};