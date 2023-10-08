#include "Reflection.h"

Reflection::Reflection() {
	Init();
}

Reflection::~Reflection() {

}

void Reflection::Init() {

	for (int oi = 0; oi < kMaxObjectNum; oi++) {
		object_[oi] = {
			ShapeType::CIRCLE,// shapeType

			false, // = isAlive
			{0.0f, 0.0f} // pos

			// positionはランダムになる
		};
	}

	size_.radius = 10.0f;

}

void Reflection::Update() {
	// collision Maneger
}

void Reflection::Draw() {
	for (int oi = 0; oi < kMaxObjectNum; oi++) {
		if (object_[oi].isAlive) {
			if (object_[oi].shapeType == CIRCLE) {
				Novice::DrawEllipse(
					static_cast<int>(object_[oi].pos.x), static_cast<int>(object_[oi].pos.y),
					static_cast<int>(size_.radius), static_cast<int>(size_.radius),
					0.0f,
					0xFA0000FF,
					kFillModeSolid
				);

			} else if (object_[oi].shapeType == SQUARE) {
				Novice::DrawBox(
					static_cast<int>(object_[oi].pos.x), static_cast<int>(object_[oi].pos.y),
					static_cast<int>(size_.width), static_cast<int>(size_.height),
					0.0f,
					0xFA0000FF,
					kFillModeSolid
				);
			}
		}
	}
}