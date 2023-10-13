#include "BossBullet.h"

BossBullet::BossBullet() {
}

BossBullet::~BossBullet() {
	delete new BossBullet;
}

void BossBullet::Init() {
	pos_.x = 0;
	pos_.y = 0;

	radius_ = 15.0f;

	velocity_.x = 8.0f;
	velocity_.y = 8.0f;

	velocity_.x = 0.2f;
	velocity_.y = 0.2f;

	isShot_ = false;

}

