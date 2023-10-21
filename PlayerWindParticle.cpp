#include "PlayerWindParticle.h"
#include <Novice.h>
#include <math.h>
#include <MyDeta/Source/Easing.h>

PlayerWindParticle::PlayerWindParticle(Vector2<float> startPos, Vector2<float> targetPos,  int maxTime,int speed)
{
	pos_ = startPos;
	radius_ = 20.0f;
	float xv = targetPos.x - startPos.x;
	float yv = targetPos.x - startPos.y;
	float l = sqrtf(xv * xv + yv * yv);
	velocity_ = { xv / l * speed,yv / l * speed };
	maxTime_ = maxTime;
}

PlayerWindParticle::~PlayerWindParticle()
{
}

void PlayerWindParticle::Update()
{
	pos_.x += velocity_.x;
	pos_.y += velocity_.y;

	radius_ += 0.5f;
	float t = static_cast<float>(timer_) / static_cast<float>(maxTime_);
	float save = EaseInQuad(t);

	alpha_ = static_cast<int>(100 - 100 * save);

	timer_++;
	if (timer_ > maxTime_) {
		del_ = true;
	}
}

void PlayerWindParticle::Draw()
{
	Novice::DrawEllipse(
		static_cast<int>(pos_.x) + static_cast<int>(cie_->GetOrigine().x),
		static_cast<int>(pos_.y) + static_cast<int>(cie_->GetOrigine().y),
		static_cast<int>(radius_), static_cast<int>(radius_),
		0.0f,
		0xFFFFFF00 + alpha_, kFillModeSolid
	);
}

bool PlayerWindParticle::GetDelFlag()
{
	return del_;
}

