#include "Stage.h"

Stage::Stage() {
	Init();
}

void Stage::Init() {
	pos_.x = 0.0f;
	pos_.y = 0.0f;

	radius_ = 300.0f;

	rangeRadius_ = 180.0f;

	gh_ = Novice::LoadTexture("./images/Resource/Stage/bgWave1.png");

	color_ = 0xffffffff;

	//==========================================
	gameBgm_ = Novice::LoadAudio("./images/Sounds/bgm/souldrive.mp3");

	gemeBgmHandle_ = -1;

	gameBgmVolume_ = 0.3f;


	//デバック用
	bulletVanishRange_ = 500.0f;
}

void Stage::Draw() {
	Novice::DrawSprite(
		0,
		0,
		gh_,
		1.0f,
		1.0f,
		0.0f,
		color_
	);


	Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
		static_cast<int>(pos_.y + cie_->GetOrigine().y),
		static_cast<int>(radius_),
		static_cast<int>(radius_),
		0.0f,
		0xffffffff,
		kFillModeWireFrame);

	/*Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
		static_cast<int>(pos_.y + cie_->GetOrigine().y),
		static_cast<int>(rangeRadius_),
		static_cast<int>(rangeRadius_),
		0.0f,
		0xffffffff,
		kFillModeWireFrame);*/

	Novice::DrawEllipse(static_cast<int>(pos_.x + cie_->GetOrigine().x),
		static_cast<int>(pos_.y + cie_->GetOrigine().y),
		static_cast<int>(bulletVanishRange_),
		static_cast<int>(bulletVanishRange_),
		0.0f,
		0xff0000ff,
		kFillModeWireFrame);

	//==========================================
	//sound
	PlayAudio(gemeBgmHandle_, gameBgm_, gameBgmVolume_);
}
