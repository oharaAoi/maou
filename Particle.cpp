#include "Particle.h"
#include <Novice.h>

Particle::Particle(Vector2<float> pos,int maxTime)
{
	pos_ = pos;
	velocity_ = { 0,8.f };
	maxTime_ = maxTime;
}

Particle::~Particle()
{
}

void Particle::Update()
{
	pos_.x += velocity_.x;
	pos_.y += velocity_.y;
	timer_++;
	if (timer_ > maxTime_) {
		del_ = true;
	}
}

void Particle::Draw()
{
	Novice::DrawEllipse(
		static_cast<int>(pos_.x), static_cast<int>(pos_.y),
		8, 8,
		0.0f,
		WHITE, kFillModeSolid
	);
}

bool Particle::GetDelFlag()
{
	return del_;
}
