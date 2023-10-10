#include "Boss.h"

Boss::Boss() {
}

void Boss::Init() {
	pos_.x = kWindowWidth / 2.0f;
	pos_.y = kWindowHeight / 2.0f;

	radius_ = 50.0f;

	color_ = 0xffffffff;

	hp_ = 50.0f;
}

void Boss::UpDate() {

}

void Boss::Draw() {
	Novice::DrawEllipse(static_cast<int>(pos_.x),
		static_cast<int>(pos_.y),
		static_cast<int>(radius_),
		static_cast<int>(radius_),
		0.0f,
		color_,
		kFillModeSolid);
}