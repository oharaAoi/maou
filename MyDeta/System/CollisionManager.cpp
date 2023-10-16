#include "CollisionManager.h"

CollisionManager::CollisionManager() {
	Init();
}

void CollisionManager::Init() {
	b2bLength_ = 0.0f;
	b2pLength_ = 0.0f;
}

void CollisionManager::CheckCollision(Boss& boss_, BossBullet& bossBullet_) {
	b2bLength_ = CheckLength(bossBullet_.GetPos(), boss_.GetPos());

	if (b2bLength_ < bossBullet_.GetRadius() + boss_.GetRadius()) {
		if (bossBullet_.GetIsPushBacked() == true) {
			//弾の処理
			bossBullet_.SetIsShot(false);
			bossBullet_.SetPos({0.0f,0.0f});
			bossBullet_.SetIsPushBacked(false);

			//ボスの処理
			boss_.SetHp(boss_.GetHp() - 1);
		}
	}

}

void CollisionManager::CheckCollision(Player& player_, BossBullet& bossBullet_) {
	b2pLength_ = CheckLength(bossBullet_.GetPos(), player_.GetPos());

	if (b2pLength_ < player_.GetRadius() + bossBullet_.GetRadius()) {
		//弾の処理
		bossBullet_.SetIsShot(false);
		bossBullet_.SetPos({ 0.0f,0.0f });
		bossBullet_.SetIsPushBacked(false);

		//プレイヤーの処理
		player_.SetHp(player_.GetHp() - 1);
	}
}
