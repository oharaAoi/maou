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
}
