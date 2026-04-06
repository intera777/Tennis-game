#include "TennisGame.hpp"

float Racket::getX() {
	return x;
}

void Racket::setX(float x) {
	this->x = x;
}

float Racket::getY() {
	return y;
}

void Racket::setY(float y) {
	this->y = y;
}
void Racket::init() {
	x = 960 / 2;
	y = 540 - 30;
}
void Racket::draw() {
	int halfW = racketW / 2;
	int halfH = racketH / 2;
	DrawBox(x - halfW, y - halfH, x + halfW, y + halfH, 0xffffff, TRUE);
}

void Racket::move() {
	if (CheckHitKey(KEY_INPUT_LEFT)) x -= racketSpeed;
	if (CheckHitKey(KEY_INPUT_RIGHT)) x += racketSpeed;
}

