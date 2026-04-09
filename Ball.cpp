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
	sx = 5.0;
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

void Ball::checkRacket(Racket racket) {
	// ラケットの矩形境界
	float rx = racket.getX();
	float ry = racket.getY();
	float left = rx - racketW / 2.0f;
	float right = rx + racketW / 2.0f;
	float top = ry - racketH / 2.0f;
	float bottom = ry + racketH / 2.0f;

	// ボール中心（float を使う）
	float bx = this->x;
	float by = this->y;

	// 円の中心から矩形上の最近接点を求める（clamp）
	float cx = bx;
	if (cx < left) cx = left;
	else if (cx > right) cx = right;

	float cy = by;
	if (cy < top) cy = top;
	else if (cy > bottom) cy = bottom;

	// 最近接点との距離で判定
	float dx = bx - cx;
	float dy = by - cy;
	if (dx * dx + dy * dy <= (float)(ballR * ballR)) {
		// ボールがラケットに向かっている場合のみ反転（はさまり防止）
		if ((sy > 0 && by < top + ballR) || (sy < 0 && by > bottom - ballR)) {
			sy = -sy;
		} else {
			// 場合によっては単純に反転でも良い
			// sy = -sy;
		}
	}
}