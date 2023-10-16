#include "Boss.h"

Boss::Boss() {
}

void Boss::Init() {
	pos_.x = 0;
	pos_.y = 0;

	radius_ = 50.0f;

	color_ = 0xffffffff;

	hp_ = 50.0f;
}

void Boss::UpDate() {
	if (type_ == wave1) {
		hp_ = 50.0f;
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