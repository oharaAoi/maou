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

		objet_[i].bulletType = SLOW;

		//==============================
		objet_[i].velocity.x = 1.5f;
		objet_[i].velocity.y = 1.5f;

		objet_[i].accleleration.x = 0.06f;
		objet_[i].accleleration.y = 0.06f;

		//==============================
		//当たり判定で使う
		objet_[i].isShot = false;
		objet_[i].isPushBacked = false;

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

	b2bLength = 0.0f;

	//==============================
	shotDire_ = 0.0f;
	shotRadian_ = 0.0f;

	bullet2pRadian_ = 0.0f;
	boss2pRadian_ = 0.0f;

	//==============================
	freamCount_ = 0;
	slowdownCount_ = 0;

	coolTimeLimit_ = 20;

	//==============================
	barrageType_ = RANDAM;

	explodeRadius = 60.0f;

	randTypeMax_ = 1;
}

//弾の種類をランダムにしたい時
void BossBullet::RandamInit(int i) {

	objet_[i].bulletType = Rand(0, randTypeMax_);

	//弾の種類によって初期値を変える
	switch (objet_[i].bulletType) {
	case SLOW:
		objet_[i].radius = 15.0f;

		objet_[i].color = 0x0000ffff;

		objet_[i].velocity.x = slowSpeed_;
		objet_[i].velocity.y = slowSpeed_;

		objet_[i].accleleration.x = 0.04f;
		objet_[i].accleleration.y = 0.04f;

		break;
	case FAST:
		objet_[i].radius = 10.0f;

		objet_[i].color = 0x00ff00ff;

		objet_[i].velocity.x = fastSpeed_;
		objet_[i].velocity.y = fastSpeed_;

		objet_[i].accleleration.x = 0.06f;
		objet_[i].accleleration.y = 0.06f;

		break;

	case EXPLODE:
		objet_[i].radius = 15.0f;

		objet_[i].color = 0xFF4500ff;

		objet_[i].velocity.x = explodeSpeed_;
		objet_[i].velocity.y = explodeSpeed_;

		objet_[i].accleleration.x = 0.04f;
		objet_[i].accleleration.y = 0.04f;

		objet_[i].explodeCount = 0;

		break;

	case VANISH:
		objet_[i].radius = 10.0f;

		objet_[i].color = 0x7FFFD4ff;

		objet_[i].velocity.x = vanishSpeed_;
		objet_[i].velocity.y = vanishSpeed_;

		objet_[i].accleleration.x = 0.04f;
		objet_[i].accleleration.y = 0.04f;

		objet_[i].vanishCount = 0;
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
	objet_[i].velocity.x = slowSpeed_;
	objet_[i].velocity.y = slowSpeed_;

	objet_[i].accleleration.x = 0.04f;
	objet_[i].accleleration.y = 0.04f;

	//==============================
	//当たり判定で使う
	objet_[i].isShot = false;
	objet_[i].isPushBacked = false;

	objet_[i].bulletType = SLOW;
}

//今はbulletをキーで設定
void BossBullet::BulletShotSelect(char* keys, char* preKeys) {
	if (keys[DIK_Q] && !preKeys[DIK_Q]) {
		for (int i = 0; i < kBulletMax_; i++) {
			OutOfScreenInit(i);
		}
		barrageType_ = CHASE;
		coolTimeLimit_ = 35;
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
		coolTimeLimit_ = 30;
	}
}

void BossBullet::BulletShotChange(Barrage type) {

	barrageType_ = type;

	if (barrageType_ == RANDAM) {
		coolTimeLimit_ = 30;

	}else if (barrageType_ == CHASE) {
		coolTimeLimit_ = 35;

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
void BossBullet::ExplodeBullet(int num) {
	for (int i = 0; i < kBulletMax_; i++) {
		if (objet_[i].isShot) {
			b2bLength = CheckLength(objet_[i].pos, objet_[num].pos);

			//消す処理(エフェクトとかの処理もここでするかも)
			if (explodeRadius > b2bLength) {
				OutOfScreenInit(i);
			}
		}
	}

	OutOfScreenInit(num);
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

//弾をランダムな方向に撃つ
void BossBullet::RandamDireShot() {
	for (int i = 0; i < kBulletMax_; i++) {
		if (objet_[i].isShot == false) {
			RandamInit(i);

			objet_[i].isShot = true;

			shotDire_ = static_cast<float>(Rand(0, 360)) / 180.0f * float(M_PI);

			objet_[i].velocity.x *= cosf(shotDire_);
			objet_[i].velocity.y *= sinf(shotDire_);

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

			shotDire_ = static_cast<float>(i * 4) / (static_cast<float>(kBulletMax_) / 2) * float(M_PI);

			objet_[i].velocity.x *= cosf(shotDire_);
			objet_[i].velocity.y *= sinf(shotDire_);

			//maxまで撃ったらランダムに切り替える
			if (i >= kBulletMax_ - 1) {
				barrageType_ = RANDAM;
			}

			//10発ずつ撃つ
			if (i % 10 == 0) {
				break;
			}
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

			//全部撃ち終わったらランダムにする
			if (i == kBulletMax_ - 1) {
				barrageType_ = RANDAM;
			}

			break;
		}
	}
}

void BossBullet::Update(Vector2<float> bossPos, Player& player) {
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
			for (int i = 0; i < kBulletMax_; i++) {
				if (objet_[i].isShot == false) {
					FourDireIsShot(i);
					if (i % 4 == 0) {
						break;
					}

					if (i == kBulletMax_ - 1) {
						barrageType_ = RANDAM;
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
		if (objet_[i].isShot == true) {
			//消える弾の処理
			if (objet_[i].bulletType == VANISH) {
				objet_[i].vanishCount++;

				if (objet_[i].vanishCount >= 450) {
					Blinking(objet_[i].color);
				}

				if (objet_[i].vanishCount >= 500) {
					OutOfScreenInit(i);
					objet_[i].vanishCount = 0;
				}
			}

			//周りを巻き込んで爆発する弾の処理
			if (objet_[i].bulletType == EXPLODE) {
				objet_[i].explodeCount++;

				if (objet_[i].explodeCount >= 450) {
					Blinking(objet_[i].color);
				}

				//爆発する範囲内のものをすべて初期化
				if (objet_[i].explodeCount >= 500) {
					ExplodeBullet(i);
					objet_[i].explodeCount = 0;
				}
			}

			//==============================================
			//弾を進める
			if (objet_[i].isPushBacked == true) {
				if (objet_[i].isRange) {
					//範囲内にある時
					//ボスに向かうようにする
					bullet2pDis_.x = bossPos.x - objet_[i].pos.x;
					bullet2pDis_.y = bossPos.y - objet_[i].pos.y;

					boss2pRadian_ = atan2f(bullet2pDis_.y, bullet2pDis_.x);

					objet_[i].velocity.x += objet_[i].accleleration.x * player.GetWindVolume().x * cosf(boss2pRadian_);
					objet_[i].velocity.y += objet_[i].accleleration.x * player.GetWindVolume().y * sinf(boss2pRadian_);

				} else {
					//範囲外にある時はゆっくり遅くしていく
					slowdownCount_++;

					if (slowdownCount_ >= 15) {
						objet_[i].velocity.x *= 0.92f;
						objet_[i].velocity.y *= 0.92f;

						slowdownCount_ = 0;
					}
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

			if (objet_[i].bulletType == EXPLODE) {
				Novice::DrawEllipse(
					static_cast<int>(objet_[i].pos.x + cie_->GetOrigine().x),
					static_cast<int>(objet_[i].pos.y + cie_->GetOrigine().y),
					static_cast<int>(explodeRadius),
					static_cast<int>(explodeRadius),
					0.0f,
					objet_[i].color,
					kFillModeWireFrame);
			}
		}

		Novice::ScreenPrintf(10, 20, "barrageType_:%d", barrageType_);
		/*Novice::ScreenPrintf(200, 10 + (i * 20), "isShot:%d", objet_[i].isShot);*/

		/*Novice::ScreenPrintf(1100, 20 + (i * 20), "explodeCount:%d", objet_[i].explodeCount);*/
	}
}