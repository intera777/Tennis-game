#include"TennisGame.hpp"

float Ball::getX() {
	return x;
}

void Ball::setX(float x) {
	this->x = x;
}

float Ball::getY() {
	return y;
}

void Ball::setY(float y) {
	this->y = y;
}

void Ball::init(Racket racket) {
	x = racket.getX();
	y = racket.getY() - racketH / 2 - ballR;
	sx =5.0;
	sy = -5.0;
}

void Ball::move() {
	x += sx;
	y += sy;
	if (x <= ballR || WIDTH - ballR <= x) {
		sx *= -1;
	}
	if (y <= ballR || HEIGHT - ballR <= y) {
		sy *= -1;
	}
}

void Ball::draw() {
	DrawCircle(x, y, ballR, 0xffffff, TRUE);
}