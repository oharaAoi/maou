#pragma once

// MySource //
#include "MyDeta/Source/MyMath.h"

// MyObject //
#include "MyDeta/Object/Player.h"
#include "MyDeta/Object/Reflection.h"
#include "MyDeta/Object/Orbit.h"

#include "MyDeta/Object/BossBullet.h"

class CollisionManager {
private:
public:

	// maou
	void CheckCollision(Player& player, Reflection& reflection);
	void CheckCollision(Player& player, Orbit& orbit);

	// sennpuuki
	void CheckCollision(Player& player, BossBullet& bossBullet);
};