#include "GameOver.h"

GameOver::GameOver() {
	Init();
}

void GameOver::Init() {

	goToGame_ = true;

	changeToGame_ = false;
	changeToTitle_ = false;

	//==========================================
	//ゲームへ
	object_[0].width = 256;
	object_[0].height = 64;

	object_[0].pos.x = kWindowWidth / 2;
	object_[0].pos.y = 450;

	object_[0].size.x = 1.0f;
	object_[0].size.y = 1.0f;

	object_[0].gh = Novice::LoadTexture("./images/Resource/GameOver/goToGame.png");

	//==========================================
	//タイトルへ
	object_[1].width = 256;
	object_[1].height = 64;

	object_[1].pos.x = kWindowWidth / 2;
	object_[1].pos.y = 550;

	object_[1].size.x = 1.0f;
	object_[1].size.y = 1.0f;

	object_[1].gh = Novice::LoadTexture("./images/Resource/GameOver/goToTitle.png");

	//==========================================
	bgGh_ = Novice::LoadTexture("./images/Resource/GameOver/GameOver.png");

}

void GameOver::Update(char* keys, char* preKeys) {
	if (keys[DIK_W] && !preKeys[DIK_W]) {
		if (goToGame_) {
			goToGame_ = false;
		} else {
			goToGame_ = true;
		}
	}

	if (keys[DIK_S] && !preKeys[DIK_S]){
		if (goToGame_) {
			goToGame_ = false;
		} else {
			goToGame_ = true;
		}
	}

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (goToGame_) {
			changeToGame_ = true;
		} else {
			changeToTitle_ = true;
		}
	}

	if (goToGame_) {
		object_[0].size.x = 1.2f;
		object_[0].size.y = 1.2f;

		object_[1].size.x = 1.0f;
		object_[1].size.y = 1.0f;

	} else {
		object_[0].size.x = 1.0f;
		object_[0].size.y = 1.0f;

		object_[1].size.x = 1.2f;
		object_[1].size.y = 1.2f;
	}
}

void GameOver::Draw() {
	//==========================================
	Novice::DrawSprite(
		0,
		0,
		bgGh_,
		1.0f,
		1.0f,
		0.0f,
		0xFFFFFFFF
	);

	//==========================================
	//ゲームへ
	/*Novice::DrawSprite(
		static_cast<int>(object_[0].pos.x),
		static_cast<int>(object_[0].pos.y),
		object_[0].gh,
		object_[0].size.x,
		object_[0].size.y,
		0.0f,
		0xFFFFFFFF
	);*/

	Novice::DrawQuad(
		static_cast<int>(object_[0].pos.x - (object_[0].width / 2) * object_[0].size.x),
		static_cast<int>(object_[0].pos.y - (object_[0].height / 2) * object_[0].size.y),
		static_cast<int>(object_[0].pos.x + (object_[0].width / 2) * object_[0].size.x),
		static_cast<int>(object_[0].pos.y - (object_[0].height / 2) * object_[0].size.y),
		static_cast<int>(object_[0].pos.x - (object_[0].width / 2) * object_[0].size.x),
		static_cast<int>(object_[0].pos.y + (object_[0].height / 2) * object_[0].size.y),
		static_cast<int>(object_[0].pos.x + (object_[0].width / 2) * object_[0].size.x),
		static_cast<int>(object_[0].pos.y + (object_[0].height / 2) * object_[0].size.y),
		0,
		0,
		static_cast<int>(object_[0].width),
		static_cast<int>(object_[0].height),
		object_[0].gh,
		0xFFFFFFFF
	);

	//==========================================
	//タイトルへ
	/*Novice::DrawSprite(
		static_cast<int>(object_[1].pos.x),
		static_cast<int>(object_[1].pos.y),
		object_[1].gh,
		object_[1].size.x,
		object_[1].size.y,
		0.0f,
		0xFFFFFFFF
	);*/

	Novice::DrawQuad(
		static_cast<int>(object_[1].pos.x - (object_[1].width / 2) * object_[1].size.x),
		static_cast<int>(object_[1].pos.y - (object_[1].height / 2) * object_[1].size.y),
		static_cast<int>(object_[1].pos.x + (object_[1].width / 2) * object_[1].size.x),
		static_cast<int>(object_[1].pos.y - (object_[1].height / 2) * object_[1].size.y),
		static_cast<int>(object_[1].pos.x - (object_[1].width / 2) * object_[1].size.x),
		static_cast<int>(object_[1].pos.y + (object_[1].height / 2) * object_[1].size.y),
		static_cast<int>(object_[1].pos.x + (object_[1].width / 2) * object_[1].size.x),
		static_cast<int>(object_[1].pos.y + (object_[1].height / 2) * object_[1].size.y),
		0,
		0,
		static_cast<int>(object_[1].width),
		static_cast<int>(object_[1].height),
		object_[1].gh,
		0xFFFFFFFF
	);


	Novice::ScreenPrintf(1000, 100, "obj[0].pos.x:%f", object_[0].pos.x);
}