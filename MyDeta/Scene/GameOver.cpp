#include "GameOver.h"

GameOver::GameOver() {
	Init();

	gameOverBgmHandle_ = -1;
	sceneChangeSEHandle_ = -1;
	selectMoveSEHAndle_ = -1;
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

	object_[0].color = 0xFFFFFFFF;

	//==========================================
	//タイトルへ
	object_[1].width = 256;
	object_[1].height = 64;

	object_[1].pos.x = kWindowWidth / 2;
	object_[1].pos.y = 550;

	object_[1].size.x = 1.0f;
	object_[1].size.y = 1.0f;

	object_[1].gh = Novice::LoadTexture("./images/Resource/GameOver/goToTitle.png");

	object_[1].color = 0xFFFFFFFF;

	//==========================================
	bgGh_ = Novice::LoadTexture("./images/Resource/GameOver/GameOver.png");

	//==========================================
	gameOverBgm_ = Novice::LoadAudio("./images/Sounds/bgm/gameOver.mp3");
	scnenChangeSE_ = Novice::LoadAudio("./images/Sounds/sceneChangeSE/decideSE.mp3");
	selectMoveSE_ = Novice::LoadAudio("./images/Sounds/sceneChangeSE/selectMoveSE.mp3");

	gameOverBgmVolume_ = 0.02f;
	sceneChangeSEVolume_ = 0.2f;
	selectMoveSEVolume_ = 0.2f;

	playSound_ = false;
	isSelectMoveSE_ = false;
	isSceneChangeSE_ = false;
	

	Novice::StopAudio(gameOverBgm_);

}

void GameOver::Update(char* keys, char* preKeys) {
	if (isSelectMoveSE_) {
		isSelectMoveSE_ = false;
	}

	if (isSceneChangeSE_) {
		isSceneChangeSE_ = false;
	}

	if (keys[DIK_W] && !preKeys[DIK_W]) {
		if (goToGame_) {
			goToGame_ = false;
		} else {
			goToGame_ = true;
		}

		isSelectMoveSE_ = true;
	}

	if (keys[DIK_S] && !preKeys[DIK_S]) {
		if (goToGame_) {
			goToGame_ = false;
		} else {
			goToGame_ = true;
		}

		isSelectMoveSE_ = true;
	}

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (goToGame_) {
			changeToGame_ = true;

		} else {
			changeToTitle_ = true;
		}

		isSceneChangeSE_ = true;
	}

	if (goToGame_) {
		object_[0].size.x = 1.2f;
		object_[0].size.y = 1.2f;

		object_[1].size.x = 1.0f;
		object_[1].size.y = 1.0f;

		object_[0].color = 0xFFFFFFFF;
		object_[1].color = 0x808080FF;

	} else {
		object_[0].size.x = 1.0f;
		object_[0].size.y = 1.0f;

		object_[1].size.x = 1.2f;
		object_[1].size.y = 1.2f;

		object_[0].color = 0x808080FF;
		object_[1].color = 0xFFFFFFFF;
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
		object_[0].color
	);

	//==========================================
	//タイトルへ
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
		object_[1].color
	);

	//==========================================
	if (!changeToGame_ && !changeToTitle_) {
		if (gameOverBgmHandle_ == -1) {
			PlayAudio(gameOverBgmHandle_, gameOverBgm_, gameOverBgmVolume_, false);
		}
	} else {
		Novice::StopAudio(gameOverBgmHandle_);
	}

	if (isSceneChangeSE_) {
		Novice::PlayAudio(scnenChangeSE_, false, sceneChangeSEVolume_);
	} else {
		Novice::StopAudio(sceneChangeSEHandle_);
	}

	if (isSelectMoveSE_) {
		Novice::PlayAudio(selectMoveSE_, false, selectMoveSEVolume_);
	}
}