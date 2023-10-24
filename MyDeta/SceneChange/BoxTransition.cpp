#include "BoxTransition.h"

BoxTransition::BoxTransition() {
	Init();

	backgroundGH_ = Novice::LoadTexture("./images/resource/sceneChange/sceneChange.png");
}

BoxTransition::~BoxTransition() {
}

void BoxTransition::Init() {

	
	maxSize_ = {
		static_cast<float>(kWindowWidth) / static_cast<float>(kSubdivisionWidth_),
		static_cast<float>(kWindowHeight) / static_cast<float>(kSubdivisionHeight_)
	};

	for (int row = 0; row < kSubdivisionHeight_ + 1; row++) {
		for (int column = 0; column < kSubdivisionWidth_ + 1; column++) {
			object_[row][column] = {
				{
					((static_cast<float>(kWindowWidth) / static_cast<float>(kSubdivisionWidth_)) / 2.0f) * ((column * 2.0f) + 1.0f),
					((static_cast<float>(kWindowHeight) / static_cast<float>(kSubdivisionHeight_)) / 2.0f) * ((row * 2.0f) + 1.0f),
				}, // center

				{0.0f, 0.0f}
			};
		}
	}
}

void BoxTransition::Update(float t) {

	if (t < 120.0f) { t++; }

	for (int row = 0; row < kSubdivisionHeight_ + 1; row++) {
		for (int column = 0; column < kSubdivisionWidth_ + 1; column++) {
			object_[row][column].size.width = Lerp(DivideParameter(EaseInOutSine(t / 120.0f), kSubdivisionHeight_, row), 0.0f, maxSize_.width);
			object_[row][column].size.height = Lerp(DivideParameter(EaseInOutSine(t / 120.0f), kSubdivisionHeight_, row), 0.0f, maxSize_.height);
		}
	}
	
}

void BoxTransition::Draw() {
	for (int row = 0; row < kSubdivisionHeight_ + 1; row++) {
		for (int column = 0; column < kSubdivisionWidth_ + 1; column++) {
			/*Novice::DrawBox(
				static_cast<int>(object_[row][column].center.x - (object_[row][column].size.width / 2.0f)),
				static_cast<int>(object_[row][column].center.y - (object_[row][column].size.height / 2.0f)),
				static_cast<int>(object_[row][column].size.width),
				static_cast<int>(object_[row][column].size.height),
				0.0f,
				0xFAFAFAFF,
				kFillModeSolid
			);*/

			Novice::DrawSpriteRect(
				static_cast<int>(object_[row][column].center.x - (object_[row][column].size.width / 2.0f)),
				static_cast<int>(object_[row][column].center.y - (object_[row][column].size.height / 2.0f)),
				static_cast<int>(object_[row][column].center.x - (object_[row][column].size.width / 2.0f)),
				static_cast<int>(object_[row][column].center.y - (object_[row][column].size.height / 2.0f)),
				static_cast<int>(object_[row][column].size.width),
				static_cast<int>(object_[row][column].size.height),
				backgroundGH_,
				object_[row][column].size.width / 1280.0f, object_[row][column].size.height / 720.0f,
				0.0f,
				0xFFFFFFFF
			);
		}
	}
}
