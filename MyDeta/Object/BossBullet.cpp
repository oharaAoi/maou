#include "BossBullet.h"

BossBullet::BossBullet() {
}

BossBullet::~BossBullet() {
	delete new BossBullet;
}

void BossBullet::Init() {
	for (int bi = 0; bi < kMaxBossBulletNum; bi++) {
		object_[bi] = {
			false, // = isShot

			{0.0f, 0.0f}, // pos
			0.0f, // radius

			{0.0f, 0.0f}, // velocity
			{0.0f, 0.0f}, // acceleration

			0.0f, // theta
		};
	}
}

