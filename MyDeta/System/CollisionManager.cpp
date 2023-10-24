#include "CollisionManager.h"

CollisionManager::CollisionManager() {
	Init();
}

void CollisionManager::Init() {
	b2bLength_ = 0.0f;
	b2pLength_ = 0.0f;
}

void CollisionManager::CheckCollision(Boss& boss_, BossBullet& bossBullet_, Emitter& emitter) {
	for (int i = 0; i < BossBullet::kBulletMax_; i++) {
		b2bLength_ = CheckLength(bossBullet_.GetPos(i), boss_.GetPos());

		if (b2bLength_ < bossBullet_.GetRadius(i) + boss_.GetRadius()) {
			if (bossBullet_.GetIsPushBacked(i) == true) {
				//弾がボスに当たった時の処理
				switch (bossBullet_.GetBulletType(i)) {
				case SLOW:
					boss_.SetHp(boss_.GetHp() - 1);
					//エフェクトの生成処理
					emitter.Emit(static_cast<int>(bossBullet_.GetPos(i).x), static_cast<int>(bossBullet_.GetPos(i).y), 6);

					break;

				case FAST:
					boss_.SetHp(boss_.GetHp() - 2);

					//エフェクトの生成処理
					emitter.Emit(static_cast<int>(bossBullet_.GetPos(i).x), static_cast<int>(bossBullet_.GetPos(i).y), 12);

					break;

				case EXPLODE:
					boss_.SetHp(boss_.GetHp() - 2);

					//エフェクトの生成処理
					emitter.Emit(static_cast<int>(bossBullet_.GetPos(i).x), static_cast<int>(bossBullet_.GetPos(i).y), 12);
					break;

				case VANISH:
					boss_.SetHp(boss_.GetHp() - 1);

					//エフェクトの生成処理
					emitter.Emit(static_cast<int>(bossBullet_.GetPos(i).x), static_cast<int>(bossBullet_.GetPos(i).y), 6);
					break;
				}

				//弾の処理
				if (bossBullet_.GetBarrageType() == CHASE || bossBullet_.GetBarrageType() == RANDAM) {
					bossBullet_.SetIsShot(false, i);
					bossBullet_.SetPos({ static_cast<int>(kWindowWidth), static_cast<int>(kWindowHeight) }, i);
					bossBullet_.SetIsPushBacked(false, i);
					bossBullet_.SetIsHit(true, i);
				} else {
					bossBullet_.SetPos({ static_cast<int>(kWindowWidth), static_cast<int>(kWindowHeight) }, i);
					bossBullet_.SetIsPushBacked(false, i);
				}
				
				if (bossBullet_.GetBulletType(i) == SLOW || bossBullet_.GetBulletType(i) == VANISH) {
					boss_.SetHp(boss_.GetHp() - 1);
				} else {
					boss_.SetHp(boss_.GetHp() - 2);
				}

				if (boss_.GetHp() == 40 || boss_.GetHp() == 20) {
					boss_.SetBulletChange(true);
				}
				
				if (boss_.GetHp() <= 0) {
					boss_.SetIsAlive(false);
					boss_.SetDeathCount(boss_.GetDeathCount() + 1);
				}
			}
		}
	}
}

void CollisionManager::CheckCollision(Player& player_, BossBullet& bossBullet_, Emitter& emitter) {
	for (int i = 0; i < BossBullet::kBulletMax_; i++) {
		b2pLength_ = CheckLength(bossBullet_.GetPos(i), player_.GetPos());

		if (b2pLength_ < player_.GetRadius() + bossBullet_.GetRadius(i)) {
			//エフェクトの生成処理
			emitter.Emit(static_cast<int>(bossBullet_.GetPos(i).x), static_cast<int>(bossBullet_.GetPos(i).y), 12);

			//弾の処理
			bossBullet_.SetIsShot(false, i);
			bossBullet_.SetPos({ 0.0f,0.0f }, i);
			bossBullet_.SetIsPushBacked(false, i);

			//プレイヤーの処理
			player_.SetHp(player_.GetHp() - 1);
		}
	}
}
