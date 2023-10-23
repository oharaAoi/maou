﻿#include "Stage.h"

Stage::Stage() {
	Init();
}

void Stage::Init() {
	pos_.x = 0.0f;
	pos_.y = 0.0f;

	radius_ = 300.0f;

	rangeRadius_ = 180.0f;
	
	backGround_[0].pos.x = 0;
	backGround_[0].pos.y = 720;
	backGround_[0].gh = Novice::LoadTexture("./images/Resource/Stage/backGround/bgWave1.png");
	backGround_[0].color = 0xffffffff;

	backGround_[1].pos.x = 0;
	backGround_[1].pos.y = 0;
	backGround_[1].gh = Novice::LoadTexture("./images/Resource/Stage/backGround/bgWave1.png");
	backGround_[1].color = 0xffffffff;

	backGround_[2].pos.x = 0;
	backGround_[2].pos.y = -720;
	backGround_[2].gh = Novice::LoadTexture("./images/Resource/Stage/backGround/bgWave2.png");
	backGround_[2].color = 0xffffffff;

	backGround_[3].pos.x = 0;
	backGround_[3].pos.y = -1440;
	backGround_[3].gh = Novice::LoadTexture("./images/Resource/Stage/backGround/bgWave3.png");
	backGround_[3].color = 0xffffffff;
	

	//==========================================
	//雲
	for (int i = 0; i < kCloudMax; i++) {
		cloud[i].pos.x = static_cast<float>(Rand(200, 1500));
		cloud[i].pos.y = static_cast<float>(Rand(100, 600));

		cloud[i].velocity.x = 0.5f;
		cloud[i].velocity.y = 0.0f;

		cloud[i].size.x = 64.0f;
		cloud[i].size.y = 64.0f;

		cloud[i].color = 0xffffffff;
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
	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite(
			static_cast<int>(backGround_[i].pos.x),
			static_cast<int>(backGround_[i].pos.y),
			backGround_[i].gh,
			1.0f,
			1.0f,
			0.0f,
			backGround_[i].color
		);
	}

	for (int i = 0; i < kCloudMax; i++) {
		Novice::DrawSprite(
			static_cast<int>(cloud[i].pos.x),
			static_cast<int>(cloud[i].pos.y),
			cloud[i].gh_,
			1.0f,
			1.0f,
			0.0f,
			cloud[i].color
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
