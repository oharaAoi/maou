﻿#include "Player.h"

Player::Player() {
	white1x1GH = Novice::LoadTexture("./NoviceResources/white1x1.png");

	weakWindHandle_ = -1;
	strongWindHandle_ = -1;
	overHeatRecoverHandle_ = -1;
	overHeatWarningHandle_ = -1;
	recoverSEHandle_ = -1;
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

	/*radianSpeed_ = 0.0f;*/

	radianPlusSpeed_ = 0.0f;
	radianMinusSpeed_ = 0.0f;

	theta_ = 3.0f / 4.0f * (float)M_PI;
	//==========================================
	frameCount_ = 0;
	frameCountLimit_ = 10;

	gh_ = Novice::LoadTexture("./images/Resource/Player/fun.png");

	drawTheta_ = 0.0f;

	drawWidth_ = 64.0f;
	drawHeight_ = 64.0f;

	drawLt_.x = 0.0f;
	drawLt_.y = 0.0f;

	spriteSize.x = 320.0f;
	spriteSize.y = 64.0f;

	p2bDis_.x = 0.0f;
	p2bDis_.y = 0.0f;

	p2bVertical_.x = 0.0f;
	p2bVertical_.y = 0.0f;

	originLt_.x = -radius_;
	originLt_.y = -radius_;
	originRt_.x = radius_;
	originRt_.y = -radius_;
	originLb_.x = -radius_;
	originLb_.y = radius_;
	originRb_.x = radius_;
	originRb_.y = radius_;

	lt_.x = 0.0f;
	lt_.y = 0.0f;
	rt_.x = 0.0f;
	rt_.y = 0.0f;
	lb_.x = 0.0f;
	lb_.y = 0.0f;
	rb_.x = 0.0f;
	rb_.y = 0.0f;

	//==========================================
	hp_ = 15;
	overHeat_ = 100.0f;
	isAlive_ = true;

	windVolume_.x = 0.0f;
	windVolume_.y = 0.0f;

	windowStrength_ = WindowStrength::OFF;

	//==========================================
	//リソース
	weakWindSe_ = Novice::LoadAudio("./images/Sounds/PlayerSe/weakFan.mp3");
	strongWindSe_ = Novice::LoadAudio("./images/Sounds/PlayerSe/strongFan.mp3");
	hitSe_ = Novice::LoadAudio("./images/Sounds/PlayerSe/playerHited.mp3");
	playerDeathSe_ = Novice::LoadAudio("./images/Sounds/PlayerSe/playerDeath.mp3");
	recoverSE_ = Novice::LoadAudio("./images/Sounds/PlayerSe/recoverSE.mp3");
	overHeatRecoverSE_ = Novice::LoadAudio("./images/Sounds/PlayerSe/overHeatRecoverSE.mp3");
	overHeatWarnigSE_ = Novice::LoadAudio("./images/Sounds/PlayerSe/overHeatWarningSE.mp3");

	//フラグ
	isWindSeStop_ = false;
	deathSeHandle_ = false;
	isOverHeatRecover_ = false;

	//音量
	windSoundVolume_ = 0.2f;
	hitSeVolume_ = 0.02f;
	playerDeathSeVolume_ = 0.2f;
	overHeatRecoverVolume_ = 0.1f;
	overHeatWarningVolume_ = 0.1f;
	recoverSEVolume_ = 0.2f;
}

void Player::Update(char* keys, char* preKeys, Stage& stage_) { /// 更新処理
	if (isAlive_) {
		//======================================================
		//playerの移動
		/// Plus
		if (keys[DIK_A]) {
			radianPlusSpeed_ += 0.05f;

		} else {
			radianPlusSpeed_ *= 0.92f;
		}

		// Clamp
		if (radianPlusSpeed_ > 1.0f) {
			radianPlusSpeed_ = 1.0f;
		}

		/// Minus
		if (keys[DIK_D]) {
			radianMinusSpeed_ += 0.05f;

		} else {
			radianMinusSpeed_ *= 0.92f;
		}

		// Clamp
		if (radianMinusSpeed_ > 1.0f) {
			radianMinusSpeed_ = 1.0f;
		}

		

		theta_ += (radianPlusSpeed_ - radianMinusSpeed_) / 100.0f * (float)M_PI;

		pos_.x = stage_.GetPos().x + (stage_.GetRadius() * cosf(theta_));
		pos_.y = stage_.GetPos().y + (stage_.GetRadius() * sinf(theta_));

		rangePos_.x = stage_.GetPos().x + (stage_.GetRangeRadius() * cosf(theta_));
		rangePos_.y = stage_.GetPos().y + (stage_.GetRangeRadius() * sinf(theta_));

		//======================================================
		//描画のための処理
		p2bDis_ = ConversionNormalizeVector(pos_, stage_.GetPos());

		p2bVertical_.x = -p2bDis_.y;
		p2bVertical_.y = p2bDis_.x;

		drawTheta_ = atan2f(p2bVertical_.y, p2bVertical_.x);

		//回転行列
		rotateMatrix = MakeRotateMatrix(drawTheta_);

		//平行移動
		translateMatrix = MakeTranslateMatrix(pos_);

		//行列の積
		worldMatrix = Multiply(rotateMatrix, translateMatrix);

		lt_ = Transform(originLt_, worldMatrix);
		rt_ = Transform(originRt_, worldMatrix);
		lb_ = Transform(originLb_, worldMatrix);
		rb_ = Transform(originRb_, worldMatrix);


		//画像の切り替え
		if (windowStrength_ != OFF) {
			frameCount_++;
			if (frameCount_ > frameCountLimit_) {
				drawLt_.x += 64.0f;
				frameCount_ = 0;

				if (drawLt_.x >= spriteSize.x) {
					drawLt_.x = 0;
				}
			}
		}

		//======================================================
		//風の切り替え(OFF→弱→強 OFF)
		switch (windowStrength_) {
		case WindowStrength::OFF:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				windowStrength_ = WEAK;
				windVolume_.x = 1.3f;
				windVolume_.y = 1.3f;
				stage_.SetRangeRadius(150.0f);
				frameCountLimit_ = 10;
			}

			if (overHeat_ < 100.0f) {
				overHeat_ += 0.5f;

				isOverHeatRecover_ = true;
			} else {
				isOverHeatRecover_ = false;
			}

			break;

		case WindowStrength::WEAK:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				windowStrength_ = STRONG;
				windVolume_.x = 1.5f;
				windVolume_.y = 1.5f;
				stage_.SetRangeRadius(100.0f);
				frameCountLimit_ = 5;
			}

			if (overHeat_ > 0.0f) { overHeat_ -= 0.1f; }

			isOverHeatRecover_ = false;

			break;

		case WindowStrength::STRONG:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				windowStrength_ = OFF;
				windVolume_.x = 0.0f;
				windVolume_.y = 0.0f;
				stage_.SetRangeRadius(300.0f);
				drawLt_.x = 0.0f;
			}

			if (overHeat_ > 0.0f) { overHeat_ -= 0.4f; }

			isOverHeatRecover_ = false;

			break;
		}

		if (overHeat_ < 0.0f) {
			windowStrength_ = OFF;
			windVolume_.x = 0.0f;
			windVolume_.y = 0.0f;
			stage_.SetRangeRadius(300.0f);
		}
	}

	//playerの生存確認
	if (hp_ <= 0) {
		stage_.SetIsBlackOut(true);
		stage_.SetIsStopSound(true);
		isWindSeStop_ = true;

		if (stage_.GetIsBlackOutFinish() == true) {
			isAlive_ = false;
		}
	}

	//soundを消す処理
	if (isRecover_) {
		isRecover_ = false;
	}
}

void Player::AllSoundStop() {
	isRecover_ = false;
	Novice::StopAudio(strongWindHandle_);
	Novice::StopAudio(weakWindHandle_);
	Novice::StopAudio(overHeatRecoverHandle_);
	Novice::StopAudio(overHeatWarningHandle_);
	isOverHeatRecover_ = false;
}

void Player::Draw() { /// 描画処理
	// over
	switch (windowStrength_) {
	case WindowStrength::OFF: // koko

		DrawCircleAnimation(
			(overHeat_ / 100.0f),
			{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
			260.0f, 10.0f,
			white1x1GH,
			0x808080D0
		);

		break;

	default:

		if (overHeat_ > 30.0f) {
			DrawCircleAnimation(
				(overHeat_ / 100.0f),
				{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
				260.0f, 10.0f,
				white1x1GH,
				0x0000faD0
			);

		} else {

			DrawCircleAnimation(
				(overHeat_ / 100.0f),
				{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
				260.0f, 10.0f,
				white1x1GH,
				0xfafa00D0
			);
		}

		break;
	}

	if (hp_ > 0) {
		// HP
		DrawRhombus(
			{ pos_.x + cie_->GetOrigine().x, pos_.y + cie_->GetOrigine().y },
			rangeRadius_ - 10.0f,
			10.0f,
			0x505050FF,
			white1x1GH
		);

		DrawRhombusAnimation(
			hp_ / 15.0f,
			{ pos_.x + cie_->GetOrigine().x, pos_.y + cie_->GetOrigine().y },
			rangeRadius_ - 10.0f,
			10.0f,
			ShiftColor(hp_ / 15.0f, 0xFA0000FF, 0x00FA00FF),
			white1x1GH
		);

		Novice::DrawQuad(
			static_cast<int>(lt_.x + cie_->GetOrigine().x),
			static_cast<int>(lt_.y + cie_->GetOrigine().y),
			static_cast<int>(rt_.x + cie_->GetOrigine().x),
			static_cast<int>(rt_.y + cie_->GetOrigine().y),
			static_cast<int>(lb_.x + cie_->GetOrigine().x),
			static_cast<int>(lb_.y + cie_->GetOrigine().y),
			static_cast<int>(rb_.x + cie_->GetOrigine().x),
			static_cast<int>(rb_.y + cie_->GetOrigine().y),
			static_cast<int>(drawLt_.x),
			static_cast<int>(drawLt_.y),
			static_cast<int>(drawWidth_),
			static_cast<int>(drawHeight_),
			gh_,
			0xffffffff
		);
	}


	if (overHeat_ > 30.0f || overHeat_ == 0) {
		Novice::StopAudio(overHeatWarningHandle_);
	} else {
		if (windowStrength_ != OFF) {
			PlayAudio(overHeatWarningHandle_, overHeatWarnigSE_, overHeatWarningVolume_, true);
		} else if (overHeat_ < 30.0f) {
			Novice::StopAudio(overHeatWarningHandle_);
		}
	}

	//sounds
	switch (windowStrength_) {
	case WindowStrength::OFF:
		Novice::StopAudio(strongWindHandle_);
		Novice::StopAudio(weakWindHandle_);
		break;

	case WindowStrength::WEAK:
		PlayAudio(weakWindHandle_, weakWindSe_, windSoundVolume_, true);
		break;

	case WindowStrength::STRONG:
		Novice::StopAudio(weakWindHandle_);
		PlayAudio(strongWindHandle_, strongWindSe_, windSoundVolume_, true);
		break;
	}

	//画面切り変え時に音を消す
	if (isWindSeStop_) {
		Novice::StopAudio(strongWindHandle_);
		Novice::StopAudio(weakWindHandle_);
	}

	if (isOverHeatRecover_) {
		PlayAudio(overHeatRecoverHandle_, overHeatRecoverSE_, overHeatRecoverVolume_, true);
	} else {
		Novice::StopAudio(overHeatRecoverHandle_);
	}

	//playerのhit時の音
	if (isHit_) {
		if (hp_ > 1) {
			Novice::PlayAudio(hitSe_, false, hitSeVolume_);
			isHit_ = false;
		}
	}

	//playerの回復音
	if (isRecover_) {
		Novice::PlayAudio(recoverSE_, false, recoverSEVolume_);
	} else {
		Novice::StopAudio(recoverSE_);
	}

	//playerの死亡時の音
	if (deathSeHandle_) {
		Novice::PlayAudio(playerDeathSe_, false, hitSeVolume_);
		deathSeHandle_ = false;
	}
}

// user method overload
void Player::Update(char* keys, Stage& stage_, Restrictions restriction) {
	switch (restriction) {
	case MOVE_ONLY:

		//playerの移動
		/// Plus
		if (keys[DIK_A]) {
			radianPlusSpeed_ += 0.05f;

		} else {
			radianPlusSpeed_ *= 0.92f;
		}

		// Clamp
		if (radianPlusSpeed_ > 1.0f) {
			radianPlusSpeed_ = 1.0f;
		}

		/// Minus
		if (keys[DIK_D]) {
			radianMinusSpeed_ += 0.05f;

		} else {
			radianMinusSpeed_ *= 0.92f;
		}

		// Clamp
		if (radianMinusSpeed_ > 1.0f) {
			radianMinusSpeed_ = 1.0f;
		}

		theta_ += (radianPlusSpeed_ - radianMinusSpeed_) / 100.0f * (float)M_PI;

		pos_.x = stage_.GetPos().x + (stage_.GetRadius() * cosf(theta_));
		pos_.y = stage_.GetPos().y + (stage_.GetRadius() * sinf(theta_));

		windowStrength_ = OFF;
		windVolume_.x = 0.0f;
		windVolume_.y = 0.0f;
		stage_.SetRangeRadius(300.0f);
		//描画のための処理
		p2bDis_ = ConversionNormalizeVector(pos_, stage_.GetPos());

		p2bVertical_.x = -p2bDis_.y;
		p2bVertical_.y = p2bDis_.x;

		drawTheta_ = atan2f(p2bVertical_.y, p2bVertical_.x);

		//回転行列
		rotateMatrix = MakeRotateMatrix(drawTheta_);

		//平行移動
		translateMatrix = MakeTranslateMatrix(pos_);

		//行列の積
		worldMatrix = Multiply(rotateMatrix, translateMatrix);

		lt_ = Transform(originLt_, worldMatrix);
		rt_ = Transform(originRt_, worldMatrix);
		lb_ = Transform(originLb_, worldMatrix);
		rb_ = Transform(originRb_, worldMatrix);


		//画像の切り替え
		if (windowStrength_ != OFF) {
			frameCount_++;
			if (frameCount_ > frameCountLimit_) {
				drawLt_.x += 64.0f;
				frameCount_ = 0;

				if (drawLt_.x >= spriteSize.x) {
					drawLt_.x = 0;
				}
			}
		}

		break;
	}
}


