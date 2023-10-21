#include "Tutorial.h"

Tutorial::Tutorial() {

	Init();

	white1x1GH_ = Novice::LoadTexture("./NoviceResource/white1x1.png");
}

Tutorial::~Tutorial() {
}

void Tutorial::Init() {
	isEndTutorial_ = false;
	pressFream_ = 60.0f * 5/*s*/;

	progress_ = MOVE;
	progressFream_ = 0.0f;
}

void Tutorial::Update(char* keys, char* preKeys) {
	if (keys[DIK_SPACE]) {
		pressFream_--;

		if (pressFream_ == 0.0f) {
			isEndTutorial_ = true;
		}

	} else {
		pressFream_ = 60.0f * 5/*s*/;
	}

	switch (progress_) {
		case Progress::MOVE:

			if (keys[DIK_A] || keys[DIK_D]) {
				progress_ = Progress::WINDOW;
			}

			break;

		case Progress::WINDOW:

			if (keys[DIK_SPACE]) {
				progress_ = Progress::ENEMY;
			}

			break;

		case Progress::ENEMY:

			if (progressFream_ < 60.0f * 10/*s*/) { progressFream_++; }
			

			break;

		case Progress::BULLET:



			break;
	}
}

void Tutorial::Draw() {
	DrawRhombusAnimation(
		pressFream_ / 300.0f,
		{100.0f, 100.0f,},
		30.0f, 10.0f,
		0xFAFAFAFF,
		white1x1GH_
	);
}
