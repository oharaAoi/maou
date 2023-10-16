#include "BossBullet.h"

BossBullet::BossBullet() {
}

BossBullet::~BossBullet() {

}

void BossBullet::Init() {

	type_ = TypeRand(0, 3);

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


	length_ = 0.0f;

	isShot_ = false;
	isPushBacked_ = false;

	bullet2pDis_.x = 0.0f;
	bullet2pDis_.y = 0.0f;

}

void BossBullet::IsShot(char* keys, char* preKeys, Vector2<float> playerPos) {
	//íeÇåÇÇ¬(é¿ç€ÇÕÉâÉìÉ_ÉÄÇæÇ¡ÇΩÇËhpÇÃèÛãµÇ≈åÇÇ¬)
	if (keys[DIK_Q] && preKeys[DIK_Q] == false) {
		if (isShot_ == false) {

			Init();

			isShot_ = true;

			bullet2pDis_.x = pos_.x - playerPos.x;
			bullet2pDis_.y = pos_.y - playerPos.y;

			theta_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

			velocity_.x *= cosf(theta_);
			velocity_.y *= sinf(theta_);
		}
	}
}

void BossBullet::Update(Vector2<float> bossPos) {
	//íeÇêiÇﬂÇÈ
	if (isShot_ == true) {
		if (isPushBacked_ == true) {
			if (isRange_) {
				//îÕàÕì‡Ç…Ç†ÇÈéû
				bullet2pDis_.x = pos_.x - bossPos.x;
				bullet2pDis_.y = pos_.y - bossPos.y;

				theta_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

				velocity_.x += accleleration_.x * cosf(theta_);
				velocity_.y += accleleration_.y * sinf(theta_);

			} else {
				if (velocity_.x != 0 && velocity_.y != 0) {
					velocity_.x -= deceleration_.x * cosf(theta_);
					velocity_.y -= deceleration_.y * sinf(theta_);
				}
			}
		}

		pos_.x -= velocity_.x;
		pos_.y -= velocity_.y;

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