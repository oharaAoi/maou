#pragma once

// MyObject //
#include "MyDeta/Object/Player.h"
#include "MyDeta/Object/Reflection.h"

class CollisionManager {
private:
public:

	void CheckCollision(Player& player, Reflection& reflection);

};