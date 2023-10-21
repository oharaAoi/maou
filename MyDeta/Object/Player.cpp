#include "Player.h"

Player::Player() {
	white1x1GH = Novice::LoadTexture("./NoviceResources/white1x1.png");

	Init();
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

	radianSpeed_ = 0.0f;
	theta_ = 3.0f / 4.0f * (float)M_PI;

	hp_ = 15;
	overHeat_ = 100.0f;

	windVolume_.x = 1.2f;
	windVolume_.y = 1.2f;

	windowStrength_ = WindowStrength::WEAK;
}

void Player::Update(char* keys, char* preKeys, Stage& stage_) { /// 更新処理
	//======================================================
	//playerの移動
	if (keys[DIK_A]) {
		radianSpeed_ += 0.05f;
	}

	if (keys[DIK_D]) {
		radianSpeed_ -= 0.05f;
	}

	if (radianSpeed_ > 1.0f) {
		radianSpeed_ = 1.0f;

	} else if (radianSpeed_ < -1.0f) {
		radianSpeed_ = -1.0f;
	}

	if (!keys[DIK_A] && !keys[DIK_D]) {
		radianSpeed_ *= 0.92f;
	}

	if (!keys[DIK_A] && !keys[DIK_D]) {
		radianSpeed_ *= 0.92f;
	}

	theta_ += radianSpeed_ / 100.0f * (float)M_PI;

	pos_.x = stage_.GetPos().x + (stage_.GetRadius() * cosf(theta_));
	pos_.y = stage_.GetPos().y + (stage_.GetRadius() * sinf(theta_));
	  
	rangePos_.x = stage_.GetPos().x + (stage_.GetRangeRadius() * cosf(theta_));
	rangePos_.y = stage_.GetPos().y + (stage_.GetRangeRadius() * sinf(theta_));

	//======================================================
	//風の切り替え(OFF→弱→強 OFF)
	switch (windowStrength_) {
		case WindowStrength::OFF:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				windowStrength_ = WEAK;
				windVolume_.x = 1.2f;
				windVolume_.y = 1.2f;
				stage_.SetRangeRadius(150.0f);
			}

			if (overHeat_ < 100.0f) { overHeat_ += 0.5f; }

			break;

		case WindowStrength::WEAK:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				windowStrength_ = STRONG;
				windVolume_.x = 1.5f;
				windVolume_.y = 1.5f;
				stage_.SetRangeRadius(100.0f);
			}

			if (overHeat_ > 0.0f) { overHeat_-= 0.1f; }

			break;

		case WindowStrength::STRONG:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				windowStrength_ = OFF;
				windVolume_.x = 0.0f;
				windVolume_.y = 0.0f;
				stage_.SetRangeRadius(300.0f);
			}

			if (overHeat_ > 0.0f) { overHeat_ -= 0.4f; }

			break;
	}

	if (overHeat_ < 0.0f) {
		windowStrength_ = OFF;
		windVolume_.x = 0.0f;
		windVolume_.y = 0.0f;
		stage_.SetRangeRadius(300.0f);
	}
}

void Player::Draw() { /// 描画処理

	// HP
	DrawRhombus(
		{ pos_.x + cie_->GetOrigine().x, pos_.y + cie_->GetOrigine().y },
		rangeRadius_,
		20.0f,
		0x505050FF,
		white1x1GH
	);

	DrawRhombusAnimation(
		hp_ / 15.0f,
		{ pos_.x + cie_->GetOrigine().x, pos_.y + cie_->GetOrigine().y },
		rangeRadius_,
		20.0f,
		ShiftColor(hp_ / 15.0f, 0xFA0000FF, 0x00FA00FF),
		white1x1GH
	);

	Novice::DrawEllipse(
		static_cast<int>(pos_.x + cie_->GetOrigine().x),
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

	/// test guage
	// over
	switch (windowStrength_) {
		case WindowStrength::OFF:

			DrawRhombusAnimation(
				overHeat_ / 100.0f,
				{ rangePos_.x + cie_->GetOrigine().x, rangePos_.y + cie_->GetOrigine().y },
				rangeRadius_ - 10.0f,
				10.0f,
				0x707070ff,
				white1x1GH
			);

			break;
		
		default:

			DrawRhombusAnimation(
				overHeat_ / 100.0f,
				{ rangePos_.x + cie_->GetOrigine().x, rangePos_.y + cie_->GetOrigine().y },
				rangeRadius_ - 10.0f,
				10.0f,
				ShiftColor(overHeat_ / 100.0f, 0xFA0000FF, 0x00FA00FF),
				white1x1GH
			);

			break;
	}
	
	
}
