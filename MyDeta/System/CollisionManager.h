#pragma once

// MySource //
#include "MyDeta/Source/MyMath.h"

// MyObject //
#include "MyDeta/Object/Player.h"
#include "MyDeta/Object/Reflection.h"
#include "MyDeta/Object/Orbit.h"

#include "MyDeta/Object/Boss.h"

class CollisionManager {
private:
public:

	void CheckCollision(Player& player, Reflection& reflection);
	void CheckCollision(Player& player, Orbit& orbit);

};