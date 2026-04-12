#include "TennisGame.hpp"
#include <random>
#include <cmath>

static std::mt19937& ball_rng() {
	static std::mt19937 rng((unsigned)std::random_device{}());
	return rng;
}

Ball::Ball()
	: x(0.0f), y(0.0f), sx(0.0f), sy(0.0f), outOfBottom(false), imgHandle(-1)
{
}

Ball::~Ball() {
	// 明示的に画像ハンドルを解放
	if (imgHandle != -1) {
		DeleteGraph(imgHandle);
		imgHandle = -1;
	}
}

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

// 追加: 速度のゲッター・セッター
float Ball::getSx() {
	return sx;
}

void Ball::setSx(float sx) {
	this->sx = sx;
}

float Ball::getSy() {
	return sy;
}

void Ball::setSy(float sy) {
	this->sy = sy;
}

void Ball::init(Racket racket) {
	x = racket.getX();
	y = racket.getY() - racketH / 2 - ballR;
	sx = 5.0f;
	sy = -5.0f;
	outOfBottom = false;

	// 画像を遅延ロード（既にロード済みでなければ）
	if (imgHandle == -1) {
		imgHandle = LoadGraph("image/ball.png");
		// 失敗した場合は imgHandle == -1 のままにしておく（フォールバックで円描画）
	}
}

void Ball::move(User& user) {
	// 移動
	x += sx;
	y += sy;

	// 左右の反転（はさまり防止を含む）
	if (x <= ballR) {
		// 左壁に衝突：右向きにする
		sx = std::abs(sx);
		// 壁の内側に押し戻す（はさまり防止）
		x = ballR + 1.0f;
		Sound::playWall();
	}
	else if (WIDTH - ballR <= x) {
		// 右壁に衝突：左向きにする
		sx = -std::abs(sx);
		// 壁の内側に押し戻す（はさまり防止）
		x = WIDTH - ballR - 1.0f;
		Sound::playWall();
	}


	// 上辺は今まで通り反転 + サウンド再生
	if (y <= ballR) {
		sy *= -1;
		Sound::playWall();
	}


	// 下端到達時はゲームオーバーフラグを立て、反転やスコア加算は行わない
	if (HEIGHT - ballR <= y) {
		outOfBottom = true;
		// 必要ならここで他の処理（効果音等）を呼ぶ
	}
}

void Ball::draw() {
	if (imgHandle != -1) {
		// 画像をボール半径に合わせて描画（中心合わせ）
		// DrawExtendGraph は左上・右下座標なので中心位置から拡張して指定
		DrawExtendGraph(static_cast<int>(x - ballR), static_cast<int>(y - ballR),
			static_cast<int>(x + ballR), static_cast<int>(y + ballR),
			imgHandle, TRUE);
	}
	else {
		// フォールバック：円で描画
		DrawCircle(x, y, ballR, 0xffffff, TRUE);
	}
}

void Ball::checkRacket(Racket racket, User& user) {
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
			// 乱数係数（0.8〜1.4）を作成してスケールを掛ける
			std::uniform_real_distribution<float> dist(0.8f, 1.4f);
			float factor = dist(ball_rng());

			// sy を向きに応じて反転かつスケーリングする
			if (sy > 0.0f) {
				// 下向きに進んでいてラケットの上面に当たった → 上向きにする（負）
				sy = -std::abs(sy) * factor;
				// スコアの増加
				user.setScore(user.getScore() + 100);
			}
			else {
				// 上向きに進んでいてラケットの下面に当たった → 下向きにする（正）
				sy = std::abs(sy) * factor;
			}

			// ラケット衝突時の音再生
			Sound::playRacket();

			// ここで x方向速度をランダムに変化させる
			float origSx = sx;
			float range = 1.5f * std::abs(origSx);
			std::uniform_real_distribution<float> distX(-range, range);
			float deltaX = distX(ball_rng());
			sx = origSx + deltaX;

			float minAbsSx = minRatio * std::abs(sy);
			if (std::abs(sx) < minAbsSx) {
				std::uniform_real_distribution<float> distExtra(-randRatio * std::abs(sy), randRatio * std::abs(sy));
				float extra = distExtra(ball_rng());
				extra = std::copysign(extra, sx);
				// 符号を保ちたい場合は std::copysign を使う等の調整をする
				sx += extra;
				//最低絶対値まで足りなければ保存
				if (std::abs(sx) < minAbsSx) {
					sx = (sx >= 0.0f ? 1.0f : -1.0f) * minAbsSx;
				}
			}

			if (std::abs(sx) > maxSx * sy) {
				sx = (sx > 0.0f ? 1.0f : -1.0f) * maxSx;
			}

		}
		else {
			// 必要ならここで単純反転を行う
			// sy = -sy;
		}
	}
}

bool Ball::isOutOfBottom() const {
	return outOfBottom;
}