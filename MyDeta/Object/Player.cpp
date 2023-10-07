#include "Player.h"

Player::Player() {
	Init();
}

Player::~Player() {
}

void Player::Init() { // 変数の初期化

	mode_ = SEARCH;

	center_ = {
		0.0f, // x
		0.0f, // y
	};

	size_.radius = 20.0f;

	speed_ = 1.0f;
}

void Player::Update(char* keys, char* preKeys) { /// 更新処理
	switch (mode_) {
		case Mode::SEARCH:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				mode_ = Mode::SHOT;
			}

			

			break;

		case Mode::SHOT:

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				mode_ = Mode::SHOT;
			}



			break;
	}
}

void Player::Draw() { /// 描画処理

}
