#include "CollisionManager.h"

void CollisionManager::CheckCollision(Player& player, Reflection& reflection) {
	for (int ri = 0; ri < 10/*reflection.kMaxObjectNum_*/; ri++) {
		if (reflection.GetIsAlive(ri)) {
			// if (reflection.shapeType == CIRCLE)
			if (CheckCollisionCircles( // 見にくかったら修正します...
				player.GetPos(), player.GetSize().radius, // player: center_, size_.radius
				reflection.GetPos(ri), reflection.GetSize().radius // reflection: center_, size_.radius
			)) { // hit

				// playerとreflectionの単位ベクトルの生成
				Vector2 <float>p2rVector = ConversionNormalizeVector(player.GetPos(), reflection.GetPos(ri));

				p2rVector = {
					p2rVector.x * 10.0f/*player.speed*/,
					p2rVector.y * 10.0f/*player.speed*/,
				};


				player.SetVelocity(p2rVector);
				reflection.SetIsAlive(ri, false);

			}
		}
	}
}

void CollisionManager::CheckCollision(Player& player, Orbit& orbit) {
	for (int oi = 0; oi < 10/*reflection.kMaxObjectNum_*/; oi++) {
		if (orbit.GetIsAlive(oi)) {
			if (CheckCollisionCircles(
				player.GetPos(), player.GetSize().radius, // player: center_, size_.radius
				orbit.GetPos(oi), orbit.GetCollisionSize().radius // orbit: center_, size_.radius
			)) { // hit



			}
		}
	}
}
