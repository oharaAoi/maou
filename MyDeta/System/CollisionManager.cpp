#include "CollisionManager.h"

void CollisionManager::CheckCollision(Player& player, Reflection& reflection) {
	for (int ri = 0; ri < 10; ri++) {
		// TODO: if isAlive
		if (CheckCollisionCircles( // 見にくかったら修正します...
			player.GetCenter(), player.GetSize().radius, // player: center_, size_.radius
			reflection.GetCenter(ri), reflection.GetSize().radius // reflection: center_, size_.radius
		)) { // hit

			Vector2 <float>p2rVector = ConversionNormalizeVector(player.GetCenter(), reflection.GetCenter(ri));

			p2rVector = {
				p2rVector.x * 10.0f/*player.speed*/,
				p2rVector.y * 10.0f/*player.speed*/,
			};


			player.SetVelocity(p2rVector);
			reflection.SetIsAlive(ri, false);

		}
	}
}
