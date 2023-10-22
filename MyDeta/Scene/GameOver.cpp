#include "GameOver.h"

GameOver::GameOver() {
}

void GameOver::Init() {

	bgGh_ = Novice::LoadTexture("./images/Resource/GameOver/GameOver.png");

}

void GameOver::Update() {

}

void GameOver::Draw() {
	Novice::DrawSprite(
		0,
		0,
		bgGh_,
		1.0f,
		1.0f,
		0.0f,
		0xFFFFFFFF
	);
}