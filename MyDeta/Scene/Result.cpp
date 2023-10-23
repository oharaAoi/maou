#include "Result.h"

Result::Result() {
	Init();
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

void Result::Draw() {

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
}
