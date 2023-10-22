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

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		isPressSpace_ = true;
	}

	if (!isPressSpace_) {
		if (resultFream_ < 60.0f) { resultFream_++; }
	}
}

void Result::Draw() {

	Novice::DrawBox(
		0, 0,
		1280, 720,
		0.0f,
		ShiftColor(resultFream_ / 60.0f, 0x00000000, 0x00000080),
		kFillModeSolid
	);

	DrawWindow(
		{ kWindowWidth / 2.0f, kWindowHeight / 2.0f },
		{ kWindowWidth - 100.0f, kWindowHeight - 100.0f },
		0xFFFFFFFF
	);
}
