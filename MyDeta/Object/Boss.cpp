﻿#include "Boss.h"

Boss::Boss() {
	white1x1GH = Novice::LoadTexture("./NoviceResources/white1x1.png");

	Init();
}

void Boss::Init() {
	pos_.x = 0;
	pos_.y = 0;

	radius_ = 64.0f;

	color_ = 0xffffffff;

	hp_ = 40.0f;

	isAlive_ = true;

	deathCount_ = 0;

	frameCount_ = 0;

	type_ = WAVE1;

	barrageChange_ = false;

	//==============================
	//描画に使う
	gh_ = Novice::LoadTexture("./images/Resource/Boss/boss.png");

	drawWidth_ = 128.0f;
	drawHeight_ = 128.0f;

	drawLt_.x = 0.0f;
	drawLt_.y = 0.0f;

	spriteSize_.x = 640.0f;
	spriteSize_.y = 128.0f;

	drawCount_ = 0;
	drawCountLimit_ = 10;

}

void Boss::BulletSpeedChange(BossBullet& bossBullet_) {
	if (type_ == WAVE2) {
		bossBullet_.SetSlowSpeed(2.5f);
		bossBullet_.SetFastSpeed(3.5f);
		bossBullet_.SetExplodeSpeed(3.0f);
		bossBullet_.SetVanishSpeed(3.0f);

	} else if (type_ == WAVE3) {
		bossBullet_.SetSlowSpeed(3.5f);
		bossBullet_.SetFastSpeed(4.5f);
		bossBullet_.SetExplodeSpeed(4.0f);
		bossBullet_.SetVanishSpeed(4.0f);
	}

}

void Boss::BossHpDecrece(char* keys, char* preKeys) {
	if (keys[DIK_K] && !preKeys[DIK_K]) {
		hp_ -= 10;
	}
}

void Boss::UpDate(BossBullet& bossBullet_) {
	//ボスのhpが一定量減った時
	if (type_ == WAVE1) {
		if (barrageChange_) {
			if (hp_ <= 20) {
				bossBullet_.BulletShotChange(FOURS);
				barrageChange_ = false;
			}
		}

	} else if (type_ == WAVE2) {
		if (barrageChange_) {
			if (hp_ <= 20) {
				bossBullet_.BulletShotChange(ALL);
				bossBullet_.BarrageInit();
				barrageChange_ = false;

			} else if (hp_ <= 40) {
				bossBullet_.BulletShotChange(ROTATE);
				bossBullet_.BarrageInit();
				barrageChange_ = false;
			}
		}

	} else if (type_ == WAVE3) {
		frameCount_++;

		if (frameCount_ >= 400) {
			bossBullet_.BulletShotChange(static_cast<Barrage>(Rand(1, 5)));
			bossBullet_.BarrageInit();
			frameCount_ = 0;
		}
	}

	//ボスが倒された時の処理
	if (!isAlive_) {
		if (type_ == WAVE1) {
			//==============================
			//ボスのステータスを変える
			hp_ = 60.0f;
			color_ += 0x888888ff;
			isAlive_ = true;
			type_ = WAVE2;

			//==============================
			//バレットの状態を変える
			bossBullet_.SetRandTypeMax(3);
			bossBullet_.SetRandamCoolTimeLimit(20);
			bossBullet_.SetChaseCoolTimeLimit(20);
			BulletSpeedChange(bossBullet_);

		} else if (type_ == WAVE2) {
			//==============================
			//ボスのステータスを変える
			hp_ = 80.0f;
			color_ += 0x888888ff;
			isAlive_ = true;
			type_ = WAVE3;

			//==============================
			//バレットの状態を変える
			bossBullet_.BulletShotChange(RANDAM);
			bossBullet_.SetRandamCoolTimeLimit(15);
			bossBullet_.SetChaseCoolTimeLimit(15);
			BulletSpeedChange(bossBullet_);
		}
	}

	frameCount_++;
	if (frameCount_ > drawCountLimit_) {
		drawLt_.x += 128.0f;
		frameCount_ = 0;

		if (drawLt_.x >= spriteSize_.x) {
			drawLt_.x = 0;
		}
	}
}

void Boss::Draw() {
	DrawRhombus(
		{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
		76.0f, 15.0f,
		0x8a8a8aFF,
		white1x1GH
	);

	switch (type_) {
		case WAVE1:
				DrawRhombus(
					{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
					74.0f + 30.0f, 10.0f,
					0xd8433940,
					white1x1GH
				);

				DrawRhombus(
					{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
					74.0f + 30.0f + 20.0f, 10.0f,
					0xd8433920,
					white1x1GH
				);

			// main HP
			DrawRhombusAnimation(
				hp_ / 40.0f,
				{kWindowWidth / 2.0f, kWindowHeight / 2.0f},
				74.0f, 20.0f,
				0xd84339FF,
				white1x1GH
			);
			break;

		case WAVE2:
			DrawRhombus(
				{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
				74.0f + 30.0f * 1, 10.0f,
				0xd8433940,
				white1x1GH
			);

			// main HP
			DrawRhombusAnimation(
				hp_ / 60.0f,
				{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
				74.0f, 20.0f,
				0xd84339FF,
				white1x1GH
			);
			break;

		case WAVE3:
			DrawRhombusAnimation(
				hp_ / 80.0f,
				{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
				74.0f, 20.0f,
				0xd84339FF,
				white1x1GH
			);
			break;
	}

	if (isAlive_) {
		/*Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
			static_cast<int>(pos_.y + cie_->GetOrigine().y),
			static_cast<int>(radius_),
			static_cast<int>(radius_),
			0.0f,
			color_,
			kFillModeSolid);*/

		Novice::DrawSpriteRect(
			static_cast<int>(pos_.x - radius_ + cie_->GetOrigine().x),
			static_cast<int>(pos_.y - radius_ + cie_->GetOrigine().y),
			static_cast<int>(drawLt_.x),
			static_cast<int>(drawLt_.y),
			static_cast<int>(drawWidth_),
			static_cast<int>(drawHeight_),
			gh_,
			spriteSize_.y / spriteSize_.x,
			1.0f,
			0.0f,
			0xffffffff
		);
	}
}