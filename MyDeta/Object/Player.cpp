#include "Player.h"

Player::Player() {
	
}

Player::~Player() {
}

void Player::Init() { // 変数の初期化

	mode_ = SEARCH;

	pos_ = {
		0.0f, // x
		0.0f, // y
	};

	rangePos_ = {
		0.0f,
		0.0f,
	};

	size_.radius = 20.0f;

	speed_ = 1.0f;

	/* --- totate --- */
	rotateCenter_ = {
		0.0f, // x
		0.0f, // y
		/* boss.pos_ */
	};

	b2Length_ = 0.0f; // playerとbossの距離

	radius_ = 20.0f;
	rangeRadius_ = 35.0f;

	theta_ = 3.0f / 4.0f * (float)M_PI;

	shotDirection_ = ShotDirection::TO_CENTER;

	velocity_;
	acceleration_;

}

void Player::Update(char* keys, Vector2<float> stagePos, float stageRadius, float rangeRadius) { /// 更新処理
	if (keys[DIK_A]) {
		theta_ += 1.0f / 64.0f * (float)M_PI;
	}

	if (keys[DIK_D]) {
		theta_ -= 1.0f / 64.0f * (float)M_PI;
	}

	pos_.x = stagePos.x + (stageRadius * cosf(theta_));
	pos_.y = stagePos.y + (stageRadius * sinf(theta_));

	rangePos_.x = stagePos.x + (rangeRadius * cosf(theta_));
	rangePos_.y = stagePos.y + (rangeRadius * sinf(theta_));
}

void Player::Draw() { /// 描画処理
	Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
		static_cast<int>(pos_.y + cie_->GetOrigine().y),
		static_cast<int>(radius_),
		static_cast<int>(radius_),
		0.0f,
		0xffffffff,
		kFillModeSolid);

	Novice::DrawEllipse(static_cast<int>(rangePos_.x + cie_->GetOrigine().x),
		static_cast<int>(rangePos_.y + cie_->GetOrigine().y),
		static_cast<int>(rangeRadius_),
		static_cast<int>(rangeRadius_),
		0.0f,
		0xffffffff,
		kFillModeSolid);
}
