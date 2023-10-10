#include "Particle2.h"
#include <Novice.h>

Particle2::Particle2(Vector2<float> pos, Vector2<float> velocity, int maxTime)
{
	pos_ = pos;
	velocity_ = velocity;
	maxTime_ = maxTime;
}

Particle2::~Particle2()
{
}

void Particle2::Update()
{
	pos_.x += velocity_.x;
	pos_.y += velocity_.y;
	timer_++;
	if (timer_ > maxTime_) {
		del_ = true;
	}
}

void Particle2::Draw()
{
	/*Novice::DrawEllipse(
		static_cast<int>(pos_.x), static_cast<int>(pos_.y),
		8, 8,
		0.0f,
		WHITE, kFillModeSolid
	);*/

	Novice::DrawBox(
		static_cast<int>(pos_.x) - 8, static_cast<int>(pos_.y) - 8,
		16, 16,
		0.0f,
		WHITE, kFillModeWireFrame
	);
}

bool Particle2::GetDelFlag()
{
	return del_;
}
