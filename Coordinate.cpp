#include "Coordinate.h"

Coordinate::Coordinate() {
}

Coordinate* Coordinate::GetInstance() {
	static Coordinate instance;
	return &instance;
}

void Coordinate::Init() {
	origine_.x = kWindowWidth / 2;
	origine_.y = kWindowHeight / 2;
}
