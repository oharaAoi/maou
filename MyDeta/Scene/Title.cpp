#include "Title.h"

Title::Title() {
	Init();

	backgroundGH_ = Novice::LoadTexture("./images/resource/stage/background/bgWave1.png");
	titleGH_ = Novice::LoadTexture("./images/resource/title/title.png");

	cloudGH_[0] = Novice::LoadTexture("./images/resource/stage/cloud/cloud1.png");
}

Title::~Title() {
}

void Title::Init() {
	for (int ci = 0; ci < cloudNum; ci) {
		pos_[ci] = { kWindowWidth / 2.0f, kWindowHeight / 2.0f };
	}
}

void Title::Update() {
}

void Title::Draw() {
	// background
	Novice::DrawSprite(
		0, 0,
		backgroundGH_,
		1.0f, 1.0f,
		0.0f,
		0xFAFAFAFF
	);

	for (int ci = 0; ci < cloudNum; ci++) {
		Novice::DrawSprite(
			static_cast<int>(pos_[ci].x - (64.0f)), static_cast<int>(pos_[ci].y - (64.0f)),
			cloudGH_[0],
			2.0f, 2.0f,
			0.0f,
			0xFFFFFFFF
		);
	}

	// titleGH
	Novice::DrawSprite(
		0, 2,
		titleGH_,
		1.0f, 1.0f,
		0.0f,
		0x40404070
	); // 30

	Novice::DrawSprite(
		0, 0,
		titleGH_,
		1.0f, 1.0f,
		0.0f,
		0xFAFAFAFF
	);

	
}
