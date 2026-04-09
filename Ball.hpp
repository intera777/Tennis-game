#pragma once

const int ballR = 10; //ボールの半径

class Racket;

class Ball {
private:
	float x; //x座標
	float y; //y座標
	float sx; //x方向の速度
	float sy; //y方向の速度
public:
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);

	// 追加: 速度のゲッター・セッター
	float getSx();
	void setSx(float sx);
	float getSy();
	void setSy(float sy);

	void init(Racket racket);
	void move();
	void draw();
	void checkRacket(Racket racket);

};
