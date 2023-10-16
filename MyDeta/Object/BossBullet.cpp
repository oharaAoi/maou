#include "BossBullet.h"

BossBullet::BossBullet() {
}

BossBullet::~BossBullet() {

}

void BossBullet::Init() {
	//==============================
	pos_.x = 0;
	pos_.y = 0;

	radius_ = 15.0f;

	color_ = 0x0000ffff;

	velocity_.x = 2.0f;
	velocity_.y = 2.0f;

	accleleration_.x = 0.04f;
	accleleration_.y = 0.04f;

	deceleration_.x = 0.1f;
	deceleration_.y = 0.1f;

	//==============================
	//当たり判定で使う
	bullet2pRadian_ = 0.0f;
	boss2pRadian_ = 0.0f;

	isShot_ = false;
	isPushBacked_ = false;

	bullet2pDis_.x = 0.0f;
	bullet2pDis_.y = 0.0f;

	boss2pDis_.x = 0.0f;
	boss2pDis_.y = 0.0f;

}

void BossBullet::RandamInit() {
	type_ = TypeRand(0, 3);

	//弾の種類によって初期値を変える
	switch (type_) {
	case SLOW:
		radius_ = 15.0f;

		color_ = 0x0000ffff;

		velocity_.x = 2.0f;
		velocity_.y = 2.0f;

		accleleration_.x = 0.04f;
		accleleration_.y = 0.04f;
		deceleration_.x = 0.1f;
		deceleration_.y = 0.1f;

		break;
	case FAST:
		radius_ = 10.0f;

		color_ = 0x00ff00ff;

		velocity_.x = 3.0f;
		velocity_.y = 3.0f;

		accleleration_.x = 0.04f;
		accleleration_.y = 0.04f;
		deceleration_.x = 0.1f;
		deceleration_.y = 0.1f;

		break;

	case EXPLODE:
		radius_ = 15.0f;

		color_ = 0xFF4500ff;

		velocity_.x = 3.0f;
		velocity_.y = 3.0f;

		accleleration_.x = 0.04f;
		accleleration_.y = 0.04f;
		deceleration_.x = 0.1f;
		deceleration_.y = 0.1f;

		break;

	case VANISH:
		radius_ = 10.0f;

		color_ = 0x7FFFD4ff;

		velocity_.x = 3.0f;
		velocity_.y = 3.0f;

		accleleration_.x = 0.04f;
		accleleration_.y = 0.04f;
		deceleration_.x = 0.1f;
		deceleration_.y = 0.1f;
	}

	pos_.x = 0;
	pos_.y = 0;

	bullet2pRadian_ = 0.0f;
	boss2pRadian_ = 0.0f;

	isShot_ = false;
	isPushBacked_ = false;

	bullet2pDis_.x = 0.0f;
	bullet2pDis_.y = 0.0f;

	boss2pDis_.x = 0.0f;
	boss2pDis_.y = 0.0f;

}

void BossBullet::IsShot(char* keys, char* preKeys, Vector2<float> playerPos) {
	//弾を撃つ(実際はランダムだったりhpの状況で撃つ)
	if (keys[DIK_Q] && preKeys[DIK_Q] == false) {
		if (isShot_ == false) {
			RandamInit();
			isShot_ = true;

			//プレイヤーと弾のと距離から角度を求める
			bullet2pDis_.x = playerPos.x - pos_.x;
			bullet2pDis_.y = playerPos.y - pos_.y;

			bullet2pRadian_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

			//速度に角度をかける
			velocity_.x *= cosf(bullet2pRadian_);
			velocity_.y *= sinf(bullet2pRadian_);
		}
	}
}

void BossBullet::Update(Vector2<float> bossPos) {
	//弾を進める
	if (isShot_ == true) {
		if (isPushBacked_ == true) {
			if (isRange_) {
				//範囲内にある時
				//ボスに向かうようにする
				bullet2pDis_.x = bossPos.x - pos_.x;
				bullet2pDis_.y = bossPos.y - pos_.y;

				boss2pRadian_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

				velocity_.x += accleleration_.x * cosf(boss2pRadian_);
				velocity_.y += accleleration_.y * sinf(boss2pRadian_);

			} else {
				velocity_.x += deceleration_.x * cosf(boss2pRadian_);
				velocity_.y += deceleration_.y * sinf(boss2pRadian_);

				/*if (velocity_.x < -0.002f || velocity_.x > 0.002f) {
					velocity_.x = 0.0f;
				}

				if (velocity_.y < -0.002f || velocity_.y > 0.002f) {
					velocity_.y = 0.0f;
				}*/
			}
		}

		pos_.x += velocity_.x;
		pos_.y += velocity_.y;

	}
}

void BossBullet::Draw() {
	if (isShot_ == true) {
		Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
			static_cast<int>(pos_.y + cie_->GetOrigine().y),
			static_cast<int>(radius_),
			static_cast<int>(radius_),
			0.0f,
			color_,
			kFillModeSolid);
	}
}