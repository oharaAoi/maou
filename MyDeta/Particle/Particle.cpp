#include "Particle.h"
#include <Novice.h>

Particle::Particle(Vector2<float> pos,Vector2<float> velocity,int maxTime)
{
	pos_ = pos;
	radius_ = 12.0f;
	velocity_ = velocity;
	maxTime_ = maxTime;
}

Particle::~Particle()
{
}

void Particle::Update()
{
	pos_.x += velocity_.x;
	pos_.y += velocity_.y;

	if (radius_ > 0) {
		radius_ -= 0.5f;
	}

	timer_++;
	if (timer_ > maxTime_) {
		del_ = true;
	}
}

void Particle::Draw()
{
	Novice::DrawEllipse(
		static_cast<int>(pos_.x) + static_cast<int>(cie_->GetOrigine().x), 
		static_cast<int>(pos_.y) + static_cast<int>(cie_->GetOrigine().y),
		static_cast<int>(radius_), static_cast<int>(radius_),
		0.0f,
		WHITE, kFillModeSolid
	);
}

bool Particle::GetDelFlag()
{
	return del_;
}
