#include "BossDeadParticle.h"

BossDeadParticle::BossDeadParticle()
{

}

BossDeadParticle::~BossDeadParticle()
{
}

void BossDeadParticle::Update()
{
	for (int i = 0; i < 8; i++) {
		if (circle_[i].del_ == false) {
			circle_[i].pos_.x += circle_[i].velocity_.x * speed_;
			circle_[i].pos_.y += circle_[i].velocity_.y * speed_;
			if (circle_[i].alpha_ >= 0) {
				circle_[i].alpha_ -= 5;
			}
			if (circle_[i].radius_ >= 0) {
				circle_[i].radius_--;
			} else {
				circle_[i].del_ = true;
			}
		}
	}
}

void BossDeadParticle::Draw()
{
	for (int i = 0; i < 8; i++) {
		if (circle_[i].del_ == false) {
			Novice::DrawEllipse(
				static_cast<int>(circle_[i].pos_.x), static_cast<int>(circle_[i].pos_.y),
				circle_[i].radius_, circle_[i].radius_,
				0.0f,
				0xFFFFFF00 + circle_[i].alpha_,
				kFillModeSolid
			);
		}
	}
}

void BossDeadParticle::Start(int posX, int posY)
{
	float angle_ = 45.f * (float)M_PI / 180.f;

	// 円の情報を初期化
	for (int i = 0; i < 8; i++) {
		circle_[i].pos_.x = static_cast<float>(posX);
		circle_[i].pos_.y = static_cast<float>(posY);
		circle_[i].velocity_.x = 1 * cosf(i * angle_) - 0 * sinf(i * angle_);
		circle_[i].velocity_.y = 1 * sinf(i * angle_) + 0 * cosf(i * angle_);
		circle_[i].alpha_ = 255;
		circle_[i].radius_ = 50;
		circle_[i].del_ = false;
	}
}
