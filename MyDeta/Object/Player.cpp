#include "Player.h"

Player::Player() {
	Init();
}

Player::~Player() {
}

void Player::Init() { // 変数の初期化

	mode_ = SEARCH;

	pos_ = {
		0.0f, // x
		0.0f, // y
	};

	size_.radius = 20.0f;

	speed_ = 1.0f;

	speed_;

	/* --- totate --- */
	rotateCenter_ = {
		0.0f, // x
		0.0f, // y
		/* boss.pos_ */
	};

	b2Length_ = 0.0f; // playerとbossの距離

	radius_ = b2Length_;
	radian_ = 0.0f;
	theta_;

	shotDirection_ = ShotDirection::TO_CENTER;

	velocity_;
	acceleration_;

}

void Player::Update(char* keys, char* preKeys) { /// 更新処理
	switch (mode_) {
		case Mode::SEARCH:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				mode_ = Mode::SHOOT;

				velocity_.x *= speed_;
				velocity_.y *= speed_;
			}

			radian_ = static_cast<float>(static_cast<int>(++radian_) % 400);
			theta_ = (radian_ / 200.0f) * static_cast<float>(M_PI);

			pos_ = {
				(cosf(theta_) * radius_) + rotateCenter_.x, // x
				(sinf(theta_)* radius_) - rotateCenter_.x, // y
			};

			switch (shotDirection_) {
				case ShotDirection::TO_CENTER:

					velocity_ = {
						-cosf(theta_), // x
						-sinf(theta_), // y
					};

					break;

				case ShotDirection::FROM_CENTER:

					velocity_ = {
						cosf(theta_), // x
						sinf(theta_), // y
					};

					break;
			}

			break;

		case Mode::SHOOT:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				mode_ = Mode::SEARCH;
				shotDirection_ = ShotDirection::TO_CENTER;

				rotateCenter_ = { 0.0f }; // boss pos
				radian_ = (atan2f(pos_.y - 0.0f/*boss.pos.y*/, pos_.x - 0.0f/*boss.pos.x*/) / 2.0f * static_cast<float>(M_PI)) * 400.0f;
				// HACK: 内積,外積でたぶんできる。

				// conbo = 0;
			}

			pos_.x += velocity_.x;
			pos_.y += velocity_.y;

			b2Length_ = CheckLength(pos_, { 0.0f, 0.0f }/*boss pos*/);

			if (b2Length_ > 500.0f/*最大半径*/) {
				mode_ = Mode::SEARCH;
				shotDirection_ = ShotDirection::TO_CENTER;

				rotateCenter_ = { 0.0f }; // boss pos
				radian_ = (atan2f(pos_.y - 0.0f/*boss.pos.y*/, pos_.x - 0.0f/*boss.pos.x*/) / 2.0f * static_cast<float>(M_PI)) * 400.0f;
				// HACK: 内積,外積でたぶんできる。

				// conbo = 0;
			}

			break;
	}
}

void Player::Draw() { /// 描画処理

}
