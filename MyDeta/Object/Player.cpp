#include "Player.h"

Player::Player() {
	
}

Player::~Player() {
}

void Player::Init() { // 変数の初期化

	pos_ = {
		0.0f, // x
		0.0f, // y
	};

	rangePos_ = {
		0.0f,
		0.0f,
	};

	size_.radius = 20.0f;

	radius_ = 20.0f;
	rangeRadius_ = 35.0f;

	theta_ = 3.0f / 4.0f * (float)M_PI;

	hp_ = 15;

	windowStrength_ = WindowStrength::WEAK;

	shotDirection_ = ShotDirection::TO_CENTER;

	velocity_;
	acceleration_;

}

void Player::Update(char* keys, char* preKeys, Stage& stage_) { /// 更新処理
	//======================================================
	//playerの移動
	if (keys[DIK_A]) {
		theta_ += 1.0f / 64.0f * (float)M_PI;
	}

	if (keys[DIK_D]) {
		theta_ -= 1.0f / 64.0f * (float)M_PI;
	}

	if (!keys[DIK_A] && !keys[DIK_D]) {
		radianSpeed_ *= 0.92f;
	}

	theta_ += radianSpeed_ / 64.0f * (float)M_PI;

	pos_.x = stage_.GetPos().x + (stage_.GetRadius() * cosf(theta_));
	pos_.y = stage_.GetPos().y + (stage_.GetRadius() * sinf(theta_));

	rangePos_.x = stage_.GetPos().x + (stage_.GetRangeRadius() * cosf(theta_));
	rangePos_.y = stage_.GetPos().y + (stage_.GetRangeRadius() * sinf(theta_));

	//======================================================
	//風の切り替え(OFF→弱→強OFF)
 	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {
		if (windowStrength_ == OFF) {
			windowStrength_ = WEAK;
			stage_.SetRangeRadius(150.0f);
		} else if (windowStrength_ == WEAK) {
			windowStrength_ = STRONG;
			stage_.SetRangeRadius(100.0f);
		} else {
			windowStrength_ = OFF;
			stage_.SetRangeRadius(300.0f);
		}
	}
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
