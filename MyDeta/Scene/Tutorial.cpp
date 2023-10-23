#include "Tutorial.h"

Tutorial::Tutorial() {

	Init();

	

	tutorialGH_[0] = Novice::LoadTexture("./Images/Resource/Tutorial/tutorial1.png");
	tutorialGH_[1] = Novice::LoadTexture("./Images/Resource/Tutorial/tutorial2.png");
	tutorialGH_[2] = Novice::LoadTexture("./Images/Resource/Tutorial/tutorial3.png");
}

Tutorial::~Tutorial() {
}

void Tutorial::Init() {

	white1x1GH_ = Novice::LoadTexture("./NoviceResources/white1x1.png");
	isEndTutorial_ = false;
	pressFrame_ = 60.0f * 4/*s*/;

	progress_ = MOVE;
	progressFrame_ = 0.0f;

}

void Tutorial::Update(char* keys, char* preKeys,
	Player& player, Stage& stage, Boss& boss, BossBullet& bossBullet, Emitter& emitter, CollisionManager& collisionManager, PlayerRangeDetector& playerRangeDetector, PlayerWindEmitter& playerWindEmitter) {

	if (keys[DIK_SPACE]) {
		if (pressFrame_ > 0.0f) { pressFrame_--; }

		if (pressFrame_ == 0.0f) {
			isEndTutorial_ = true;
		}

	} else {
		if (pressFrame_ > 0.0f) {
			pressFrame_ = 60.0f * 4/*s*/;
		}
	}

	if (progress_ == Progress::MOVE) {
		player.Update(keys, stage, MOVE_ONLY);

	} else {
		player.Update(keys, preKeys, stage);
	}

	switch (progress_) {
		case Progress::MOVE:

			if (keys[DIK_A] && !preKeys[DIK_A] || keys[DIK_D] && !preKeys[DIK_D]) {
				progress_ = Progress::WINDOW;
			}

			break;

		case Progress::WINDOW:

			if (keys[DIK_SPACE]) {
				progress_ = Progress::ENEMY;
			}

			break;

		case Progress::ENEMY:

			if (progressFrame_ < 60.0f * 5/*s*/) {
				progressFrame_++;
			
			} else {
				progress_ = Progress::BULLET;
				progressFrame_ = 0.0f;
			}
		

			break;

		case Progress::BULLET:

			boss.UpDate(bossBullet);
			bossBullet.Update(boss.GetPos(), player, stage, emitter);

			if (progressFrame_ < 60.0f * 10/*s*/) {
				progressFrame_++;

			} else {
				isEndTutorial_ = true;
			}

			break;
	}

	switch (player.GetWindowStrength()) {
		case OFF:
			playerWindEmitter.Update(player.GetPos(), boss.GetPos(), 0, 0, 1000);

			break;

		case WEAK:
			playerWindEmitter.Update(player.GetPos(), boss.GetPos(), 20, 6, 7);

			break;

		case STRONG:
			playerWindEmitter.Update(player.GetPos(), boss.GetPos(), 20, 12, 4);

			break;
	}

	playerRangeDetector.Update(player, bossBullet);
	collisionManager.CheckCollision(player, bossBullet);
	collisionManager.CheckCollision(boss, bossBullet, emitter);
}

void Tutorial::Draw(Player player, Stage stage, Boss boss, BossBullet bossBullet, PlayerWindEmitter playerWindEmitter) {
	// skip
	DrawRhombusAnimation(
		pressFrame_ / 240.0f,
		{ 100.0f, 100.0f, },
		30.0f, 10.0f,
		0xFAFAFAFF,
		white1x1GH_
	);

	stage.Draw();
	player.Draw();

	playerWindEmitter.Draw();

	if (progress_ >= Progress::ENEMY) {
		boss.Draw();
		bossBullet.Draw();
	}

	// window
	DrawWindow(
		{ kWindowWidth / 2.0f, kWindowHeight - 60.0f },
		{ kWindowWidth - 200.0f, 100.0f },
		0xFAFAFAFF
	);

	// word
	switch (progress_) {
		case Progress::MOVE:

			Novice::DrawSprite(
				100, 610,
				tutorialGH_[0],
				1.0f, 1.0f,
				0.0f,
				0xFFFFFFFF
			);

			break;

		case Progress::WINDOW:

			Novice::DrawSprite(
				100, 610,
				tutorialGH_[1],
				1.0f, 1.0f,
				0.0f,
				0xFFFFFFFF
			);

			break;

		case Progress::ENEMY:
		case Progress::BULLET:

			Novice::DrawSprite(
				100, 610,
				tutorialGH_[2],
				1.0f, 1.0f,
				0.0f,
				0xFFFFFFFF
			);

			break;

	}

}