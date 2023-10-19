#include "Stage.h"

Stage::Stage() {
}

void Stage::Init() {
	pos_.x = 0.0f;
	pos_.y = 0.0f;

	radius_ = 300.0f;

	rangeRadius_ = 180.0f;

	//デバック用
	bulletVanishRange_ = 500.0f;
}

void Stage::Draw() {
	Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
		static_cast<int>(pos_.y + cie_->GetOrigine().y),
		static_cast<int>(radius_),
		static_cast<int>(radius_),
		0.0f,
		0xffffffff,
		kFillModeWireFrame);

	Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
		static_cast<int>(pos_.y + cie_->GetOrigine().y),
		static_cast<int>(rangeRadius_),
		static_cast<int>(rangeRadius_),
		0.0f,
		0xffffffff,
		kFillModeWireFrame);

	Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
		static_cast<int>(pos_.y + cie_->GetOrigine().y),
		static_cast<int>(bulletVanishRange_),
		static_cast<int>(bulletVanishRange_),
		0.0f,
		0xff0000ff,
		kFillModeWireFrame);

}
