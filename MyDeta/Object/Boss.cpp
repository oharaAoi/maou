#include "Boss.h"

Boss::Boss() {
}

void Boss::Init() {
	pos_.x = 0;
	pos_.y = 0;

	radius_ = 50.0f;

	color_ = 0xffffffff;

	hp_ = 60.0f;

	type_ = wave1;
}

void Boss::UpDate() {
	if (hp_ == 60.0f) {
		type_ = wave1;
	} else if (hp_ == 40.0f) {
		type_ = wave2;
	} else if (hp_ == 20.0f) {
		type_ = wave3;
	}
}

void Boss::Draw() {
	Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
		static_cast<int>(pos_.y + cie_->GetOrigine().y),
		static_cast<int>(radius_),
		static_cast<int>(radius_),
		0.0f,
		color_,
		kFillModeSolid);

	Novice::ScreenPrintf(600, 10, "Boss.hp:%f", hp_);
}