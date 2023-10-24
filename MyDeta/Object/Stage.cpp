#include "Stage.h"

Stage::Stage() {
	gameBgmHandle_ = -1;
}

void Stage::Init() {
	pos_.x = 0.0f;
	pos_.y = 0.0f;

	radius_ = 300.0f;

	rangeRadius_ = 180.0f;
	
	backGround_[0].pos.x = 0;
	backGround_[0].pos.y = 0;
	backGround_[0].gh = Novice::LoadTexture("./images/Resource/Stage/backGround/bgWave1.png");
	backGround_[0].color = 0xffffffff;

	backGround_[1].pos.x = 0;
	backGround_[1].pos.y = 0;
	backGround_[1].gh = Novice::LoadTexture("./images/Resource/Stage/backGround/bgWave2.png");
	backGround_[1].color = 0xffffff00;

	backGround_[2].pos.x = 0;
	backGround_[2].pos.y = 0;
	backGround_[2].gh = Novice::LoadTexture("./images/Resource/Stage/backGround/bgWave3.png");
	backGround_[2].color = 0xffffff00;
	

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
	isBlackOut_ = false;
	isBlackOutFinish_ = false;
	blackOutColor_ = 0x00000000;

	//==========================================
	changeT_ = 0.0f;

	//==========================================
	

	gameBgm_ = Novice::LoadAudio("./images/Sounds/bgm/souldrive.mp3");

	isStopSound_ = true;

	gameBgmVolume_ = 0.2f;


	//デバック用
	bulletVanishRange_ = 500.0f;
}

void Stage::Update(int waveNum) {
	//音を鳴らす
	if (isStopSound_) {
		isStopSound_ = false;
	}


	for (int i = 0; i < kCloudMax; i++) {
		cloud[i].pos.x -= cloud[i].velocity.x;

		if (cloud[i].pos.x <= -100) {
			cloud[i].pos.x = static_cast<float>(Rand(1350, 1500));
		}
	}

	if (waveNum == 1) {
		if (backGround_[1].color != 0xffffffff) {
			changeT_ += 0.01f;
			backGround_[1].color = ShiftColor(changeT_, 0xffffff00, 0xffffffff);
		}else {
			changeT_ = 0.0f;
		}

	} else if (waveNum == 2) {
		if (backGround_[2].color != 0xffffffff) {
			changeT_ += 0.01f;
			backGround_[2].color = ShiftColor(changeT_, 0xffffff00, 0xffffffff);
		}
	}

	if (isBlackOut_) {
		blackOutCount_ += 0.01f;
		blackOutColor_ = ShiftColor(blackOutCount_, 0x00000000, 0x000000FF);

		if (blackOutCount_ >= 1) {
			isBlackOutFinish_ = true;
		}
	}
}

void Stage::Draw() {
	for (int i = 0; i < 3; i++) {
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
	if (!isStopSound_) {
  		PlayAudio(gameBgmHandle_, gameBgm_, gameBgmVolume_, true);
	}else {
 		Novice::StopAudio(gameBgmHandle_);
	}
}
