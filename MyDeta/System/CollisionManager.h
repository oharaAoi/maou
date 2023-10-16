#pragma once

// MySource //
#include "MyDeta/Source/MyMath.h"

// MyObject //
#include "MyDeta/Object/Player.h"
#include "MyDeta/Object/Reflection.h"
#include "MyDeta/Object/Orbit.h"
#include "MyDeta/Object/BossBullet.h"

#include "MyDeta/Object/Boss.h"
#include "MyDeta/Object/BossBullet.h"

class CollisionManager {
private:

	float b2bLength_;
	float b2pLength_;

public:

	CollisionManager();

	void Init();

	void CheckCollision(Boss& boss_, BossBullet& bossBullet_);
	void CheckCollision(Player& player, BossBullet& bossBullet_);

	// sennpuuki
	void CheckCollision(Player& player, BossBullet& bossBullet);
};