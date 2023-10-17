#include "BossBullet.h"

BossBullet::BossBullet() {
}

BossBullet::~BossBullet() {
}

void BossBullet::Init() {
	for (int i = 0; i < kBulletMax_; i++) {
		//==============================
		objet_[i].pos.x = 0;
		objet_[i].pos.y = 0;

		objet_[i].radius = 15.0f;

		objet_[i].color = 0x0000ffff;

		//==============================
		objet_[i].velocity.x = 2.0f;
		objet_[i].velocity.y = 2.0f;

		objet_[i].accleleration.x = 0.04f;
		objet_[i].accleleration.y = 0.04f;

		objet_[i].deceleration.x = 0.1f;
		objet_[i].deceleration.y = 0.1f;

		//==============================
		//当たり判定で使う
		objet_[i].isShot = false;
		objet_[i].isPushBacked = false;

		bullet2pDis_.x = 0.0f;
		bullet2pDis_.y = 0.0f;

		boss2pDis_.x = 0.0f;
		boss2pDis_.y = 0.0f;

	}

	shotDire_ = 0.0f;
	shotRadian_ = 0.0f;

	freamCount_ = 0;

	barrageType_ = NONE;

	bullet2pRadian_ = 0.0f;
	boss2pRadian_ = 0.0f;
}

//弾の種類をランダムにしたい時
void BossBullet::RandamInit(int i) {

	objet_[i].bulletType = TypeRand(0, 3);

	//弾の種類によって初期値を変える
	switch (objet_[i].bulletType) {
	case SLOW:
		objet_[i].radius = 15.0f;

		objet_[i].color = 0x0000ffff;

		objet_[i].velocity.x = 2.0f;
		objet_[i].velocity.y = 2.0f;

		objet_[i].accleleration.x = 0.04f;
		objet_[i].accleleration.y = 0.04f;
		objet_[i].deceleration.x = 0.1f;
		objet_[i].deceleration.y = 0.1f;

		break;
	case FAST:
		objet_[i].radius = 10.0f;

		objet_[i].color = 0x00ff00ff;

		objet_[i].velocity.x = 3.0f;
		objet_[i].velocity.y = 3.0f;

		objet_[i].accleleration.x = 0.04f;
		objet_[i].accleleration.y = 0.04f;
		objet_[i].deceleration.x = 0.1f;
		objet_[i].deceleration.y = 0.1f;

		break;

	case EXPLODE:
		objet_[i].radius = 15.0f;

		objet_[i].color = 0xFF4500ff;

		objet_[i].velocity.x = 3.0f;
		objet_[i].velocity.y = 3.0f;

		objet_[i].accleleration.x = 0.04f;
		objet_[i].accleleration.y = 0.04f;
		objet_[i].deceleration.x = 0.1f;
		objet_[i].deceleration.y = 0.1f;

		break;

	case VANISH:
		objet_[i].radius = 10.0f;

		objet_[i].color = 0x7FFFD4ff;

		objet_[i].velocity.x = 3.0f;
		objet_[i].velocity.y = 3.0f;

		objet_[i].accleleration.x = 0.04f;
		objet_[i].accleleration.y = 0.04f;
		objet_[i].deceleration.x = 0.1f;
		objet_[i].deceleration.y = 0.1f;
	}

	objet_[i].pos.x = 0;
	objet_[i].pos.y = 0;

	objet_[i].isShot = false;
	objet_[i].isPushBacked = false;
}

//画面外にいった時の初期化
void BossBullet::OutOfScreenInit(int i) {
	//==============================
	objet_[i].pos.x = 0;
	objet_[i].pos.y = 0;

	objet_[i].radius = 15.0f;

	objet_[i].color = 0x0000ffff;

	//==============================
	objet_[i].velocity.x = 2.0f;
	objet_[i].velocity.y = 2.0f;

	objet_[i].accleleration.x = 0.04f;
	objet_[i].accleleration.y = 0.04f;

	objet_[i].deceleration.x = 0.1f;
	objet_[i].deceleration.y = 0.1f;

	//==============================
	//当たり判定で使う
	objet_[i].isShot = false;
	objet_[i].isPushBacked = false;
}

void BossBullet::BulletShotSelect(char* keys, char* preKeys) {
	if (keys[DIK_Q] && preKeys[DIK_Q] == false) {
		Init();
		barrageType_ = RANDAM;
	}

	if (keys[DIK_E] && preKeys[DIK_E] == false) {
		Init();
		barrageType_ = FOURS;
	}

	if (keys[DIK_R] && preKeys[DIK_R] == false) {
		Init();
		barrageType_ = ALL;
	}

	if (keys[DIK_T] && preKeys[DIK_T] == false) {
		Init();
		barrageType_ = ROTATE;
	}
}

//プレイヤーに向かって弾を撃つ
void BossBullet::IsShot(Vector2<float> playerPos) {
	for (int i = 0; i < kBulletMax_; i++) {
		if (objet_[i].isShot == false) {
			RandamInit(i);

			objet_[i].isShot = true;

			//プレイヤーと弾のと距離から角度を求める
			bullet2pDis_.x = playerPos.x - objet_[i].pos.x;
			bullet2pDis_.y = playerPos.y - objet_[i].pos.y;

			bullet2pRadian_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

			//速度に角度をかける
			objet_[i].velocity.x *= cosf(bullet2pRadian_);
			objet_[i].velocity.y *= sinf(bullet2pRadian_);

			break;
		}
	}
}

//4方向に弾を撃つ
void BossBullet::FourDireIsShot(int num) {
	if (objet_[num].isShot == false) {
		objet_[num].isShot = true;

		shotDire_ = static_cast<float>(num) / 2.0f * float(M_PI);

		objet_[num].velocity.x *= cosf(shotDire_);
		objet_[num].velocity.y *= sinf(shotDire_);
	}
}

//全方向に撃つ弾
void BossBullet::AllDireShot() {
	for (int i = 0; i < kBulletMax_; i++) {
		if (objet_[i].isShot == false) {
			objet_[i].isShot = true;

			shotDire_ = static_cast<float>(i) / (static_cast<float>(kBulletMax_) / 2) * float(M_PI);

			objet_[i].velocity.x *= cosf(shotDire_);
			objet_[i].velocity.y *= sinf(shotDire_);
		}
	}
}

//弾を撃つ方向が回転する
void BossBullet::RotateDireShot() {
	for (int i = 0; i < kBulletMax_; i++) {
		if (objet_[i].isShot == false) {
			objet_[i].isShot = true;

			shotDire_ = static_cast<float>(i) / (static_cast<float>(kBulletMax_) / 2) * float(M_PI);

			objet_[i].velocity.x *= cosf(shotDire_);
			objet_[i].velocity.y *= sinf(shotDire_);

			break;
		}
	}
}

void BossBullet::Update(Vector2<float> bossPos, Vector2<float>playerPos) {
	freamCount_++;

	//==============================================
	// 弾の種類を決める //
	if (freamCount_ >= 30) {
		//プレイヤーを追う弾幕
		if (barrageType_ == RANDAM) {
			IsShot(playerPos);

			//4方向の弾幕
		}else if (barrageType_ == FOURS) {
			for (int i = 0; i < kBulletMax_; i++) {
				if (objet_[i].isShot == false) {
					FourDireIsShot(i);
					if (i % 4 == 0) {
						break;
					}
				}
			}

			//全方向の弾幕
		}else if (barrageType_ == ALL) {
			AllDireShot();

			//回転する弾幕
		}else if (barrageType_ == ROTATE) {
			RotateDireShot();
		}
	}

	if (freamCount_ >= 20) {
		freamCount_ = 0;
	}

	//==============================================
	//弾を進める
	for (int i = 0; i < kBulletMax_; i++) {
		if (objet_[i].isShot == true) {
			if (objet_[i].isPushBacked == true) {
				if (objet_[i].isRange) {
					//範囲内にある時
					//ボスに向かうようにする
					bullet2pDis_.x = bossPos.x - objet_[i].pos.x;
					bullet2pDis_.y = bossPos.y - objet_[i].pos.y;

					boss2pRadian_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

					objet_[i].velocity.x += objet_[i].accleleration.x * cosf(boss2pRadian_);
					objet_[i].velocity.y += objet_[i].accleleration.y * sinf(boss2pRadian_);

				} else {
					objet_[i].velocity.x += objet_[i].deceleration.x * cosf(boss2pRadian_);
					objet_[i].velocity.y += objet_[i].deceleration.y * sinf(boss2pRadian_);

					/*if (velocity_.x < -0.002f || velocity_.x > 0.002f) {
						velocity_.x = 0.0f;
					}

					if (velocity_.y < -0.002f || velocity_.y > 0.002f) {
						velocity_.y = 0.0f;
					}*/
				}
			}

			objet_[i].pos.x += objet_[i].velocity.x;
			objet_[i].pos.y += objet_[i].velocity.y;

		}

		//=====================================================
		//弾が画面外に出た時の処理
		if (objet_[i].pos.x < -kWindowWidth / 2 || objet_[i].pos.x > kWindowWidth / 2) {
			OutOfScreenInit(i);
		}

		if (objet_[i].pos.y < -kWindowHeight / 2 || objet_[i].pos.y > kWindowHeight / 2) {
			OutOfScreenInit(i);
		}
	}
}

void BossBullet::Draw() {
	for (int i = 0; i < kBulletMax_; i++) {
		if (objet_[i].isShot == true) {
			Novice::DrawEllipse(
				static_cast<int>(objet_[i].pos.x + cie_->GetOrigine().x),
				static_cast<int>(objet_[i].pos.y + cie_->GetOrigine().y),
				static_cast<int>(objet_[i].radius),
				static_cast<int>(objet_[i].radius),
				0.0f,
				objet_[i].color,
				kFillModeSolid);
		}

		Novice::ScreenPrintf(10, 10 + (i * 20), "isPushBack:%d", objet_[i].isPushBacked);
		Novice::ScreenPrintf(150, 10 + (i * 20), "isShot:%d", objet_[i].isShot);
	}
}