#include "MyOrbit.h"

void MyOrbit::Init() {

	// particle //
	for (int pi = 0; pi < particleNum_; pi++) {
		orbit_[pi] = {
			false, // = isDisplay

			{0.0f, 0.0f}, // pos
			{0.0f, 0.0f}, // size

			0.0f, // freamCount
			0x00000000, // color
		};
	}

	effectDistance_ = 0.0f;

}

void MyOrbit::Update(Vector2 <float>playerPos) {

	if (effectDistance_ > 0.0f) {
		effectDistance_--;
	}

	//  //
	if (effectDistance_ == 0.0f) {
		for (int pi = 0; pi < particleNum_; pi++) {
			if (!orbit_[pi].isDisplay) {

				orbit_[pi].isDisplay = true;
				orbit_[pi].center = playerPos;
				orbit_[pi].size = { 30.0f, 30.0f, };
				orbit_[pi].freamCount = 60.0f;

				effectDistance_ = 7.0;

				break;
			}
		}
	}

	for (int pi = 0; pi < particleNum_; pi++) {
		if (orbit_[pi].isDisplay) {
			
			orbit_[pi].freamCount--;

			// effect //
			orbit_[pi].size = {
				EaseInOutSine(orbit_[pi].freamCount / 60.0f) * 12.0f, // width
				EaseInOutSine(orbit_[pi].freamCount / 60.0f) * 12.0f, // height
			};

			orbit_[pi].color = ShiftColor(EaseInOutSine((orbit_[pi].freamCount - 60.0f) / 60.0f), 0xFAFAFAFF, 0xFAFAFA00);

			if (orbit_[pi].freamCount == 0.0f) {
				orbit_[pi].isDisplay = false;
			}
		}
	}
}

void MyOrbit::Draw() {
	for (int pi = 0; pi < particleNum_; pi++) {
		if (!orbit_[pi].isDisplay) continue;

		Novice::DrawBox(
			static_cast<int>(orbit_[pi].center.x - (orbit_[pi].size.width / 2.0f)),
			static_cast<int>(orbit_[pi].center.y - (orbit_[pi].size.height / 2.0f)),
			static_cast<int>(orbit_[pi].size.width),
			static_cast<int>(orbit_[pi].size.height),
			0.0f,
			orbit_[pi].color,
			kFillModeSolid
		);
	}
}
