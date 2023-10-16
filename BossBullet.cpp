#include "BossBullet.h"

BossBullet::BossBullet() {
}

BossBullet::~BossBullet() {
	
}

void BossBullet::Init() {
	pos_.x = 0;
	pos_.y = 0;

	radius_ = 15.0f;

	color_ = 0x0000ffff;

	velocity_.x = 2.0f;
	velocity_.y = 2.0f;

	accleleration_.x = 0.04f;
	accleleration_.y = 0.04f;

	length_ = 0.0f;

	isShot_ = false;

	bullet2pDis_.x = 0.0f;
	bullet2pDis_.y = 0.0f;

}

void BossBullet::IsShot(char* keys, char* preKeys, Vector2<float> playerPos) {
	if (keys[DIK_Q] && preKeys[DIK_Q] == false) {
		if (isShot_ == false) {
			isShot_ = true;

			bullet2pDis_.x = pos_.x - playerPos.x;
			bullet2pDis_.y = pos_.y - playerPos.y;

			theta_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

			velocity_.x *= cosf(theta_);
			velocity_.y *= sinf(theta_);
		}
	}
}

void BossBullet::Update(Vector2<float> playerPos) {
	if (isShot_ == true) {
		//==================================
		//範囲内にある時
		if (color_ == 0xff0000ff) {
			bullet2pDis_.x = pos_.x - playerPos.x;
			bullet2pDis_.y = pos_.y - playerPos.y;

			theta_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

			velocity_.x -= accleleration_.x * cosf(theta_);
			velocity_.y -= accleleration_.y * sinf(theta_);

			//範囲外にいる時
		} else {
			if (velocity_.x < 0.01f && velocity_.y < 0.01f) {
				velocity_.x = 0.0f;
				velocity_.y = 0.0f;
			}
		}

		pos_.x -= velocity_.x;
		pos_.y -= velocity_.y;
	}
}

void BossBullet::Draw() {
	Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
		static_cast<int>(pos_.y + cie_->GetOrigine().y),
		static_cast<int>(radius_),
		static_cast<int>(radius_),
		0.0f,
		color_,
		kFillModeSolid);
}