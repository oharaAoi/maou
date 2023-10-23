#include "Stage.h"

Stage::Stage() {
	Init();
}

void Stage::Init() {
	pos_.x = 0.0f;
	pos_.y = 0.0f;

	radius_ = 300.0f;

	rangeRadius_ = 180.0f;

	gh_ = Novice::LoadTexture("./images/Resource/Stage/backGround/bgWave1.png");

	color_ = 0xffffffff;

	//==========================================
	//雲
	for (int i = 0; i < kCloudMax; i++) {
		cloud[i].pos.x = static_cast<float>(Rand(200, 1500));
		cloud[i].pos.y = static_cast<float>(Rand(100, 600));

		cloud[i].velocity.x = 0.5f;
		cloud[i].velocity.y = 0.0f;

		cloud[i].size.x = 64.0f;
		cloud[i].size.y = 64.0f;
	}

	cloud[0].gh_ = Novice::LoadTexture("./images/Resource/Stage/cloud/cloud1.png");
	cloud[1].gh_ = Novice::LoadTexture("./images/Resource/Stage/cloud/cloud2.png");
	cloud[2].gh_ = Novice::LoadTexture("./images/Resource/Stage/cloud/cloud3.png");
	cloud[3].gh_ = Novice::LoadTexture("./images/Resource/Stage/cloud/cloud4.png");

	//==========================================
	gameBgm_ = Novice::LoadAudio("./images/Sounds/bgm/souldrive.mp3");

	gemeBgmHandle_ = -1;

	gameBgmVolume_ = 0.3f;


	//デバック用
	bulletVanishRange_ = 500.0f;
}

void Stage::Update() {
	for (int i = 0; i < kCloudMax; i++) {
		cloud[i].pos.x -= cloud[i].velocity.x;

		if (cloud[i].pos.x <= -100) {
			cloud[i].pos.x = static_cast<float>(Rand(1350, 1500));
		}
	}
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

	for (int i = 0; i < kCloudMax; i++) {
		Novice::DrawSprite(
			static_cast<int>(cloud[i].pos.x),
			static_cast<int>(cloud[i].pos.y),
			cloud[i].gh_,
			1.0f,
			1.0f,
			0.0f,
			color_
		);
	}


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
