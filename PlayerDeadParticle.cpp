#include "PlayerDeadParticle.h"
#include <Novice.h>

PlayerDeadParticle::PlayerDeadParticle(Vector2<float>pos, Vector2<float>velocity, float radius)
{
	pos_ = pos;
	velocity_ = velocity;
	radius_ = radius;
}

PlayerDeadParticle::~PlayerDeadParticle()
{
}

void PlayerDeadParticle::Update()
{
	//座標を更新
	pos_.x += velocity_.x;
	pos_.y += velocity_.y;

	//半径が0になるまで小さくする
	if (radius_ > 0) {
		radius_ -= 0.1f;
	}

	//透明度が0になるまで値を下げる
	if (alpha_ > 0) {
		alpha_ -= 10;
	}
	//透明度が0になったら削除
	if (alpha_ < 0) {
		del_ = true;
	}
}

void PlayerDeadParticle::Draw()
{
	Novice::DrawEllipse(
		static_cast<int>(pos_.x) + static_cast<int>(cie_->GetOrigine().x),
		static_cast<int>(pos_.y) + static_cast<int>(cie_->GetOrigine().y),
		static_cast<int>(radius_), static_cast<int>(radius_),
		0.0f,
		0xFFFFFF00 + alpha_, kFillModeSolid
	);
}

bool PlayerDeadParticle::GetDelFlag()
{
	return del_;
}
