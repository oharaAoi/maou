#include "Coordinate.h"

Coordinate::Coordinate() {
	/*Init();*/
}

const Vector2 <float> Coordinate::origine_ = { kWindowWidth / 2, kWindowHeight / 2 };

Coordinate::~Coordinate() {

}

Coordinate* Coordinate::GetInstance() {
	static Coordinate instance;
	return &instance;
}

void Coordinate::Init() {
	/*origine_.x = kWindowWidth / 2;
	origine_.y = kWindowHeight / 2;*/
}
