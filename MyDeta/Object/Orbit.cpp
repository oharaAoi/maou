#include "Orbit.h"

Orbit::Orbit() {
	Init();
}

Orbit::~Orbit() {
}

void Orbit::Init() {

	displaySize_.radius = 10.0f;
	collisionSize_.radius = 80.0f;

	for (int oi = 0; oi < kMaxObjectNum_; oi++) {
		object_[oi] = {
			false, // = isAlive
			{0.0f, 0.0f,} // center

			// positionはランダムになる
		};
	}
}

void Orbit::Update() {
}
