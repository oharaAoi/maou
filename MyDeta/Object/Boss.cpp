#include "Boss.h"

Boss::Boss() {
}

void Boss::Init() {
	pos_.x = 0;
	pos_.y = 0;

	radius_ = 50.0f;

	color_ = 0xffffffff;

	hp_ = 40.0f;

	isAlive_ = true;

	dethCount_ = 0;

	type_ = wave1;

	barrageChange_ = false;;
}

void Boss::UpDate(BossBullet& bossBullet_) {
	//ボスのhpが一定量減った時
	if (type_ == wave1) {
		if (barrageChange_) {
			if (hp_ <= 20) {
				bossBullet_.BulletShotChange(FOURS);
				barrageChange_ = false;
			}
		}

	} else if (type_ == wave2) {
		if (barrageChange_) {
			if (hp_ <= 20) {
				bossBullet_.BulletShotChange(ALL);
				barrageChange_ = false;
			} else if (hp_ <= 40) {
				bossBullet_.BulletShotChange(ROTATE);
				barrageChange_ = false;
			}
		}

	} else if (type_ == wave3) {

	}

	//ボスを倒した回数によってwaveを決める
	if (dethCount_ == 0) {
		type_ = wave1;

	} else if (dethCount_ == 1) {
		type_ = wave2;
		bossBullet_.SetRandTypeMax(3);

	} else if (dethCount_ == 2) {
		type_ = wave3;
	}

	//ボスが倒された時の処理
	if (!isAlive_) {
		hp_ = 60.0f;
		color_ += 0x888888ff;
		isAlive_ = true;
	}
}

void Boss::Draw() {
	if (isAlive_) {
		Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
			static_cast<int>(pos_.y + cie_->GetOrigine().y),
			static_cast<int>(radius_),
			static_cast<int>(radius_),
			0.0f,
			color_,
			kFillModeSolid);
	}

	Novice::ScreenPrintf(600, 10, "Boss.hp:%f", hp_);
}