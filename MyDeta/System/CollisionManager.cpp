#include "CollisionManager.h"

CollisionManager::CollisionManager() {
	Init();
}

void CollisionManager::Init() {
	b2bLength_ = 0.0f;
	b2pLength_ = 0.0f;
}

void CollisionManager::CheckCollision(Boss& boss_, BossBullet& bossBullet_) {
	for (int i = 0; i < 40; i++) {
		b2bLength_ = CheckLength(bossBullet_.GetPos(i), boss_.GetPos());
void CollisionManager::CheckCollision(Boss& boss_, BossBullet& bossBullet_,Emitter& emitter) {
	b2bLength_ = CheckLength(bossBullet_.GetPos(), boss_.GetPos());

	if (b2bLength_ < bossBullet_.GetRadius() + boss_.GetRadius()) {
		if (bossBullet_.GetIsPushBacked() == true) {
			//エフェクトの生成処理
			emitter.Emit(static_cast<int>(bossBullet_.GetPos().x), static_cast<int>(bossBullet_.GetPos().y), 12);

			//弾の処理
			bossBullet_.SetIsShot(false);
			bossBullet_.SetPos({0.0f,0.0f});
			bossBullet_.SetIsPushBacked(false);
		if (b2bLength_ < bossBullet_.GetRadius(i) + boss_.GetRadius()) {
			if (bossBullet_.GetIsPushBacked(i) == true) {
				//弾の処理
				bossBullet_.SetIsShot(false, i);
				bossBullet_.SetPos({ 0.0f,0.0f }, i);
				bossBullet_.SetIsPushBacked(false, i);

				//ボスの処理
				boss_.SetHp(boss_.GetHp() - 1);
			}
		}
	}
}

void CollisionManager::CheckCollision(Player& player_, BossBullet& bossBullet_) {
	for (int i = 0; i < 40; i++) {
		b2pLength_ = CheckLength(bossBullet_.GetPos(i), player_.GetPos());

		if (b2pLength_ < player_.GetRadius() + bossBullet_.GetRadius(i)) {
			//弾の処理
			bossBullet_.SetIsShot(false, i);
			bossBullet_.SetPos({ 0.0f,0.0f }, i);
			bossBullet_.SetIsPushBacked(false, i);

			//プレイヤーの処理
			player_.SetHp(player_.GetHp() - 1);
		}
	}
}
