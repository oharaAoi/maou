#include "Result.h"

Result::Result() {
	Init();

	resultGH_[0] = Novice::LoadTexture("./images/resource/result/result.png");
}

Result::~Result() {
}

void Result::Init() {
	isPressSpace_ = false;

	isEndResult_ = false;
	resultFream_ = 0.0f;

	spaceGhPos_.x = 1000.0f;
	spaceGhPos_.y = 600.0f;
	size_.x = 200.0f;
	size_.y = 64.0f;
	drawLt_.x = 0.0f;
	drawLt_.y = 0.0f;

	spaceGH_ = Novice::LoadTexture("./images/Resource/result/space.png");
	spaceGhChangeCount_ = 0;

	gameClearSE_ = Novice::LoadAudio("./images/Sounds/gameClear/gameClearSE.mp3");

	gameClearSEHandle_ = -1;

	gameClearSEVolume_ = 0.2f;

}

void Result::Update(char* keys, char* preKeys) {

	if (!isPressSpace_) {
		if (resultFream_ < 60.0f) { resultFream_++; }
		else if (resultFream_ == 60.0f) {
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) { isPressSpace_ = true; }
		}

	} else {
		if (resultFream_ > 0.0f) { resultFream_--; }
		else if (resultFream_ == 0.0f) { isEndResult_ = true; }
	}

	//========================================
	spaceGhChangeCount_++;

	if (spaceGhChangeCount_ >= 40) {
		if (drawLt_.x == 0) {
			drawLt_.x = 200.0f;
		} else {
			drawLt_.x = 0.0f;
		}

		spaceGhChangeCount_ = 0;
	}
}

void Result::Draw(Timer timer) {

	Novice::DrawBox(
		0, 0,
		1280, 720,
		0.0f,
		ShiftColor(EaseInOutExpo(resultFream_ / 60.0f), 0x00000000, 0x000000B0),
		kFillModeSolid
	);

	DrawWindow(
		{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
		{ Lerp(EaseInOutExpo(resultFream_ / 60.0f), 0.0f, kWindowWidth - 100.0f), Lerp(EaseInOutExpo(resultFream_ / 60.0f), 0.0f, kWindowHeight - 100.0f) },
		0xFFFFFFFF
	);

	// result word
	DrawSprite(
		{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
		{ Lerp(EaseInOutExpo(resultFream_ / 60.0f), 0.0f, kWindowWidth - 100.0f), Lerp(EaseInOutExpo(resultFream_ / 60.0f), 0.0f, kWindowHeight - 100.0f) },
		resultGH_[0],
		{ kWindowWidth - 100.0f , kWindowHeight - 100.0f },
		ShiftColor(EaseInOutExpo(resultFream_ / 60.0f), 0xFFFFFF00, 0xFFFFFFFF)
	);

	// time
	timer.DrawTimer(
		{ (kWindowWidth / 2.0f) - (((21.0f * 2.0f) * 3.0f) / 2.0f) + 10.0f, 240.0f},
		{21.0f * 2.0f, 32.0f * 2.0f},
		timer.GetTimer(), ShiftColor(EaseInOutExpo(resultFream_ / 60.0f), 0xFAFAFA00, 0xFAFAFAFF)
	);
	
	// best time
	float *bestTime = timer.GetBestTimer();

	for (int bi = 0; bi < 3; bi++) {

		timer.DrawTimer(
			{ (kWindowWidth / 2.0f) - (((21.0f * 2.0f) * 3.0f) / 2.0f), 420.0f + (bi * 60.0f)},
			{ 21.0f * 2.0f, 32.0f * 2.0f },
			*(bestTime + bi), ShiftColor(EaseInOutExpo(resultFream_ / 60.0f), 0xFAFA0000, 0xFAFA00FF)
		);
	}

	// goTitle
	if (resultFream_ == 60.0f) {
		Novice::DrawSpriteRect(
			static_cast<int>(spaceGhPos_.x),
			static_cast<int>(spaceGhPos_.y),
			static_cast<int>(drawLt_.x),
			static_cast<int>(drawLt_.y),
			static_cast<int>(size_.x),
			static_cast<int>(size_.y),
			spaceGH_,
			200.0f / 400.0f,
			1.0f,
			0.0f,
			0xFFFFFFFF
		);
	}

	//音を鳴らす
	if (gameClearSEHandle_ == -1) {
		PlayAudio(gameClearSEHandle_, gameClearSE_, gameClearSEVolume_, false);
	}
}
