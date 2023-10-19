﻿#include "BossBullet.h"

BossBullet::BossBullet() {
}

BossBullet::~BossBullet() {
}

void BossBullet::Init() {
	for (int i = 0; i < kBulletMax_; i++) {
		//==============================
		object_[i].pos.x = 0;
		object_[i].pos.y = 0;

		object_[i].radius = 15.0f;

		object_[i].color = 0x0000ffff;

		object_[i].bulletType = SLOW;

		//==============================
		object_[i].velocity.x = 1.5f;
		object_[i].velocity.y = 1.5f;

		object_[i].accleleration.x = 0.06f;
		object_[i].accleleration.y = 0.06f;

		//==============================
		//当たり判定で使う
		object_[i].isShot = false;
		object_[i].isPushBacked = false;

		object_[i].center2bLength = 0.0f;

	}

	//==============================
	//弾の速度(waveごとに速度を上げる)
	slowSpeed_ = 1.5f;
	fastSpeed_ = 2.5f;
	explodeSpeed_ = 2.0f;
	vanishSpeed_ = 2.0f;

	//==============================
	boss2pDis_.x = 0.0f;
	boss2pDis_.y = 0.0f;

	bullet2pDis_.x = 0.0f;
	bullet2pDis_.y = 0.0f;

	b2bLength_ = 0.0f;

	//==============================
	shotDire_ = 0.0f;
	shotRadian_ = 0.0f;

	bullet2pRadian_ = 0.0f;
	boss2pRadian_ = 0.0f;

	//==============================
	freamCount_ = 0;
	slowdownCount_ = 0;

	coolTimeLimit_ = 40;

	coolTimeRandamLimit_ = 40;
	coolTimeChaseLimit_ = 40;

	//==============================
	barrageType_ = RANDAM;

	explodeRadius_ = 60.0f;

	randTypeMax_ = 1;
}

//弾の種類をランダムにしたい時
void BossBullet::RandamInit(int i) {

	object_[i].bulletType = Rand(0, randTypeMax_);

	//弾の種類によって初期値を変える
	switch (object_[i].bulletType) {
	case SLOW:
		object_[i].radius = 15.0f;

		object_[i].color = 0x0000ffff;

		object_[i].velocity.x = slowSpeed_;
		object_[i].velocity.y = slowSpeed_;

		object_[i].accleleration.x = 0.04f;
		object_[i].accleleration.y = 0.04f;

		break;
	case FAST:
		object_[i].radius = 10.0f;

		object_[i].color = 0x00ff00ff;

		object_[i].velocity.x = fastSpeed_;
		object_[i].velocity.y = fastSpeed_;

		object_[i].accleleration.x = 0.06f;
		object_[i].accleleration.y = 0.06f;

		break;

	case EXPLODE:
		object_[i].radius = 15.0f;

		object_[i].color = 0xFF4500ff;

		object_[i].velocity.x = explodeSpeed_;
		object_[i].velocity.y = explodeSpeed_;

		object_[i].accleleration.x = 0.04f;
		object_[i].accleleration.y = 0.04f;

		object_[i].explodeCount = 0;

		break;

	case VANISH:
		object_[i].radius = 10.0f;

		object_[i].color = 0x7FFFD4ff;

		object_[i].velocity.x = vanishSpeed_;
		object_[i].velocity.y = vanishSpeed_;

		object_[i].accleleration.x = 0.04f;
		object_[i].accleleration.y = 0.04f;

		object_[i].vanishCount = 0;
	}

	object_[i].pos.x = 0;
	object_[i].pos.y = 0;

	object_[i].isShot = false;
	object_[i].isPushBacked = false;
}

//画面外にいった時の初期化
void BossBullet::OutOfScreenInit(int i) {
	//==============================
	object_[i].pos.x = 0;
	object_[i].pos.y = 0;

	object_[i].radius = 15.0f;

	object_[i].color = 0x0000ffff;

	//==============================
	object_[i].velocity.x = slowSpeed_;
	object_[i].velocity.y = slowSpeed_;

	object_[i].accleleration.x = 0.04f;
	object_[i].accleleration.y = 0.04f;

	//==============================
	//当たり判定で使う
	object_[i].isShot = false;
	object_[i].isPushBacked = false;

	/*object_[i].bulletType = SLOW;*/
}

void BossBullet::BarrageInit() {
	for (int i = kBulletMax_ / 2; i < kBulletMax_; i++) {
		object_[i].pos.x = 0;
		object_[i].pos.y = 0;

		object_[i].isShot = false;
		object_[i].isPushBacked = false;

		//==============================
		object_[i].velocity.x = slowSpeed_;
		object_[i].velocity.y = slowSpeed_;

		object_[i].accleleration.x = 0.04f;
		object_[i].accleleration.y = 0.04f;
	}
}

//今はbulletをキーで設定
void BossBullet::BulletShotSelect(char* keys, char* preKeys) {
	if (keys[DIK_Q] && !preKeys[DIK_Q]) {
		for (int i = 0; i < kBulletMax_; i++) {
			OutOfScreenInit(i);
		}
		barrageType_ = CHASE;
		coolTimeLimit_ = 10;
	}

	if (keys[DIK_E] && !preKeys[DIK_E]) {
		for (int i = 0; i < kBulletMax_; i++) {
			OutOfScreenInit(i);
		}
		barrageType_ = FOURS;
		coolTimeLimit_ = 20;
	}

	if (keys[DIK_R] && !preKeys[DIK_R]) {
		for (int i = 0; i < kBulletMax_; i++) {
			OutOfScreenInit(i);
		}
		barrageType_ = ALL;
		coolTimeLimit_ = 25;
	}

	if (keys[DIK_T] && !preKeys[DIK_T]) {
		for (int i = 0; i < kBulletMax_; i++) {
			OutOfScreenInit(i);
		}
		barrageType_ = ROTATE;
		coolTimeLimit_ = 10;
	}

	if (keys[DIK_Y] && !preKeys[DIK_Y]) {
		for (int i = 0; i < kBulletMax_; i++) {
			OutOfScreenInit(i);
		}

		barrageType_ = RANDAM;
		coolTimeLimit_ = 10;
	}
}

void BossBullet::BulletShotChange(Barrage type) {

	barrageType_ = type;

	if (barrageType_ == RANDAM) {
		coolTimeLimit_ = coolTimeRandamLimit_;

	} else if (barrageType_ == CHASE) {
		coolTimeLimit_ = coolTimeChaseLimit_;

	} else if (barrageType_ == FOURS) {
		coolTimeLimit_ = 25;

	} else if (barrageType_ == ALL) {
		coolTimeLimit_ = 25;

	} else if (barrageType_ == ROTATE) {
		coolTimeLimit_ = 10;
	}

	/*for (int i = 0; i < kBulletMax_; i++) {
		OutOfScreenInit(i);
	}*/
}

//爆発する弾の近くの弾を誘爆させる
void BossBullet::ExplodeBullet(int num, Emitter& emitter) {
	for (int i = 0; i < kBulletMax_; i++) {
		if (object_[i].isShot) {
			b2bLength_ = CheckLength(object_[i].pos, object_[num].pos);

			//消す処理(エフェクトとかの処理もここでするかも)
			if (explodeRadius_ > b2bLength_) {

				emitter.Emit(static_cast<int>(object_[i].pos.x), static_cast<int>(object_[i].pos.y), 6);

				OutOfScreenInit(i);
			}
		}
	}

	OutOfScreenInit(num);
}

//プレイヤーに向かって弾を撃つ
void BossBullet::IsShot(Vector2<float> playerPos) {
	for (int i = 0; i < kBulletMax_ / 2; i++) {
		if (object_[i].isShot == false) {
			RandamInit(i);

			object_[i].isShot = true;

			//プレイヤーと弾のと距離から角度を求める
			bullet2pDis_.x = playerPos.x - object_[i].pos.x;
			bullet2pDis_.y = playerPos.y - object_[i].pos.y;

			bullet2pRadian_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

			//速度に角度をかける
			object_[i].velocity.x *= cosf(bullet2pRadian_);
			object_[i].velocity.y *= sinf(bullet2pRadian_);

			break;
		}
	}
}

//弾をランダムな方向に撃つ
void BossBullet::RandamDireShot() {
	for (int i = 0; i < kBulletMax_ / 2; i++) {
		if (object_[i].isShot == false) {
			RandamInit(i);

			object_[i].isShot = true;

			shotDire_ = static_cast<float>(Rand(0, 360)) / 180.0f * float(M_PI);

			object_[i].velocity.x *= cosf(shotDire_);
			object_[i].velocity.y *= sinf(shotDire_);

			break;
		}
	}
}

//4方向に弾を撃つ
void BossBullet::FourDireIsShot(int num) {
	if (object_[num].isShot == false) {
		object_[num].isShot = true;

		shotDire_ = static_cast<float>(num) / 2.0f * float(M_PI);

		object_[num].velocity.x *= cosf(shotDire_);
		object_[num].velocity.y *= sinf(shotDire_);
	}
}

//全方向に撃つ弾
void BossBullet::AllDireShot() {
	for (int i = kBulletMax_ / 2; i < kBulletMax_; i++) {
		if (object_[i].isShot == false) {
			object_[i].isShot = true;

			shotDire_ = static_cast<float>(i) / (static_cast<float>(kBulletMax_) / 4) * float(M_PI);

			object_[i].velocity.x *= cosf(shotDire_);
			object_[i].velocity.y *= sinf(shotDire_);

			//maxまで撃ったらランダムに切り替える
			if (i >= kBulletMax_ - 1) {
				BulletShotChange(RANDAM);
			}

			//10発ずつ撃つ
			/*if (i % 10 == 0) {
				break;
			}*/
		}
	}
}

//弾を撃つ方向が回転する
void BossBullet::RotateDireShot() {
	for (int i = kBulletMax_ / 2; i < kBulletMax_; i++) {
		if (object_[i].isShot == false) {
			object_[i].isShot = true;

			shotDire_ = static_cast<float>(i) / (static_cast<float>(kBulletMax_) / 4) * float(M_PI);

			object_[i].velocity.x *= cosf(shotDire_);
			object_[i].velocity.y *= sinf(shotDire_);

			//全部撃ち終わったらランダムにする
			if (i == kBulletMax_ - 1) {
				BulletShotChange(RANDAM);
			}

			break;
		}
	}
}

void BossBullet::Update(Vector2<float> bossPos, Player& player, Stage stage, Emitter& emitter) {
	freamCount_++;

	//==============================================
	// 弾の種類を決める //
	//プレイヤーを追う弾幕
	if (barrageType_ == CHASE) {
		if (freamCount_ >= coolTimeLimit_) {
			IsShot(player.GetPos());
		}

		//4方向の弾幕
	} else if (barrageType_ == FOURS) {
		if (freamCount_ >= coolTimeLimit_) {
			for (int i = kBulletMax_ / 2; i < kBulletMax_; i++) {
				if (object_[i].isShot == false) {
					FourDireIsShot(i);
					if (i % 4 == 0) {
						break;
					}

					if (i == kBulletMax_ - 1) {
						BulletShotChange(RANDAM);
					}
				}
			}
		}

		//全方向の弾幕
	} else if (barrageType_ == ALL) {
		if (freamCount_ >= coolTimeLimit_) {
			AllDireShot();
		}

		//回転する弾幕
	} else if (barrageType_ == ROTATE) {
		if (freamCount_ >= coolTimeLimit_) {
			RotateDireShot();
		}

		//ランダムな方向の弾幕
	} else if (barrageType_ == RANDAM) {
		if (freamCount_ >= coolTimeLimit_) {
			RandamDireShot();
		}
	}

	if (freamCount_ >= coolTimeLimit_) {
		freamCount_ = 0;
	}

	//==============================================
	for (int i = 0; i < kBulletMax_; i++) {
		if (object_[i].isShot == true) {
			//消える弾の処理
			if (object_[i].bulletType == VANISH) {
				object_[i].vanishCount++;

				//点滅の処理
				if (object_[i].vanishCount >= 450) {
					Blinking(object_[i].color);
				}

				if (object_[i].vanishCount >= 500) {
					OutOfScreenInit(i);
					object_[i].vanishCount = 0;
				}
			}

			//周りを巻き込んで爆発する弾の処理
			if (object_[i].bulletType == EXPLODE) {
				object_[i].explodeCount++;

				if (object_[i].explodeCount >= 45) {
					Blinking(object_[i].color);
				}

				//爆発する範囲内のものをすべて初期化
				if (object_[i].explodeCount >= 50) {
					ExplodeBullet(i, emitter);
					object_[i].explodeCount = 0;
				}
			}

			//==============================================
			//弾を進める
			if (object_[i].isPushBacked == true) {
				if (object_[i].isRange) {
					//範囲内にある時
					//ボスに向かうようにする
					bullet2pDis_.x = bossPos.x - object_[i].pos.x;
					bullet2pDis_.y = bossPos.y - object_[i].pos.y;

					boss2pRadian_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

					object_[i].velocity.x += object_[i].accleleration.x * player.GetWindVolume().x * cosf(boss2pRadian_);
					object_[i].velocity.y += object_[i].accleleration.x * player.GetWindVolume().y * sinf(boss2pRadian_);

				} else {
					//範囲外にある時はゆっくり遅くしていく
					slowdownCount_++;

					if (slowdownCount_ >= 15) {
						object_[i].velocity.x *= 0.92f;
						object_[i].velocity.y *= 0.92f;

						slowdownCount_ = 0;
					}
				}
			}

			object_[i].pos.x += object_[i].velocity.x;
			object_[i].pos.y += object_[i].velocity.y;
		}

		//=====================================================
		//弾がプレイヤーの円周の外に出た時の処理
		object_[i].center2bLength = CheckLength(stage.GetPos(), object_[i].pos);

		//弾が赤円周とプレイヤーの円周の間で止まった時の処理
		if (object_[i].center2bLength > stage.GetRadius()) {
			if (static_cast<int>(object_[i].velocity.x) == 0 && static_cast<int>(object_[i].velocity.y) == 0) {
				OutOfScreenInit(i);
			}
		}

		//赤い範囲を超えたら消す
		if (object_[i].center2bLength > stage.GetBulletVanishRange()) {

			if (barrageType_ == RANDAM || barrageType_ == CHASE) {
				OutOfScreenInit(i);
			} else {
				if (i == kBulletMax_ - 1) {
					BarrageInit();
				}
			}
		}
	}
}

void BossBullet::Draw() {
	for (int i = 0; i < kBulletMax_; i++) {
		if (object_[i].isShot == true) {
			/*Novice::DrawEllipse(
				static_cast<int>(object_[i].pos.x + cie_->GetOrigine().x),
				static_cast<int>(object_[i].pos.y + cie_->GetOrigine().y),
				static_cast<int>(object_[i].radius),
				static_cast<int>(object_[i].radius),
				0.0f,
				object_[i].color,
				kFillModeSolid);*/

			Novice::DrawBox(
				static_cast<int>((object_[i].pos.x - object_[i].radius) + cie_->GetOrigine().x),
				static_cast<int>((object_[i].pos.y - object_[i].radius) + cie_->GetOrigine().y),
				static_cast<int>(object_[i].radius * 2),
				static_cast<int>(object_[i].radius * 2),
				0.0f,
				object_[i].color,
				kFillModeSolid);


			if (object_[i].bulletType == EXPLODE) {
				Novice::DrawEllipse(
					static_cast<int>(object_[i].pos.x + cie_->GetOrigine().x),
					static_cast<int>(object_[i].pos.y + cie_->GetOrigine().y),
					static_cast<int>(explodeRadius_),
					static_cast<int>(explodeRadius_),
					0.0f,
					object_[i].color,
					kFillModeWireFrame);
			}
		}

		Novice::ScreenPrintf(10, 20, "barrageType_:%d", barrageType_);

		Novice::ScreenPrintf(10, 40, "randTypeMax_:%d", randTypeMax_);

		/*Novice::ScreenPrintf(200 + ((i / 10) * 75), 10 + ((i % 10) * 20), ":%d", object_[i].isShot);*/

		Novice::ScreenPrintf(10, 60, "coolTimeRandamLimit_ :%d", coolTimeRandamLimit_);
		Novice::ScreenPrintf(10, 80, "coolTimeChaseLimit_ :%d", coolTimeChaseLimit_);
		Novice::ScreenPrintf(10, 100, "freamCount_ :%d", freamCount_);
		Novice::ScreenPrintf(10, 120, "coolTimeLimit_ :%d", coolTimeLimit_);


		/*Novice::ScreenPrintf(1100, 20 + (i * 20), "explodeCount:%d", object_[i].explodeCount);*/
	}
}