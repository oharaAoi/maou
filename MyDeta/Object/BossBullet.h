#pragma once
#include <Novice.h>

// MySource //
#include "MyDeta/Source/MyStruct.h"

static const int kMaxBossBulletNum = 100;

class BossBullet {
private:

	struct Base {
		bool isShot;

		Vector2f pos;
		float radius;

		Vector2f velocity;
		Vector2f acceleration;

		float theta;
	};

	Base object_[kMaxBossBulletNum];

public:

	BossBullet();
	~BossBullet();

	void Init();

	void Update();

	void Draw();
};

