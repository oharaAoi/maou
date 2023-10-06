#include "Player.h"

Player::Player() {
	Init();
}

Player::~Player() {
}

void Player::Init() { // •Ï”‚Ì‰Šú‰»

	mode_ = SEARCH;

	pos_ = {
		0.0f, // x
		0.0f, // y
	};

	size_.radius = 20.0f;

	speed_ = 1.0f;
}

void Player::Update(char* keys, char* preKeys) { /// XVˆ—
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

void Player::Draw() { /// •`‰æˆ—

}
