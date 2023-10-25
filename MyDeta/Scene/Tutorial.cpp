#include "Tutorial.h"

Tutorial::Tutorial() {

	Init();



	tutorialGH_[0] = Novice::LoadTexture("./Images/Resource/Tutorial/tutorial1.png");
	tutorialGH_[1] = Novice::LoadTexture("./Images/Resource/Tutorial/tutorial2.png");
	tutorialGH_[2] = Novice::LoadTexture("./Images/Resource/Tutorial/tutorial3.png");

	bulletExplanationGH_[0] = Novice::LoadTexture("./images/Resource/Tutorial/bullet1.png");
	bulletExplanationGH_[1] = Novice::LoadTexture("./images/Resource/Tutorial/bullet2.png");
	bulletExplanationGH_[2] = Novice::LoadTexture("./images/Resource/Tutorial/bullet3.png");
	bulletExplanationGH_[3] = Novice::LoadTexture("./images/Resource/Tutorial/bullet4.png");
	bulletExplanationGH_[4] = Novice::LoadTexture("./images/Resource/Tutorial/bullet5.png");

}

Tutorial::~Tutorial() {
}

void Tutorial::Init() {

	white1x1GH_ = Novice::LoadTexture("./NoviceResources/white1x1.png");
	isEndTutorial_ = false;
	pressFrame_ = 60.0f * 4/*s*/;

	progress_ = MOVE;
	progressFrame_ = 0.0f;

	isTriggerSpace_ = false;

	bulletExplanationCount_ = 0;
	bulletExplanationChange_ = false;

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
			
			if (!isTriggerSpace_) {
				if (keys[DIK_SPACE]) {
					isTriggerSpace_ = true;
				}

			} else {
				progressFrame_++;

				if (progressFrame_ > 60.0f * 5.0f/*s*/) {
					progress_ = Progress::ENEMY;
					progressFrame_ = 0.0f;
				}
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

				if (progressFrame_ >= 300) {
					bulletExplanationChange_ = true;
				}

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
	collisionManager.CheckCollision(player, bossBullet, emitter);
	collisionManager.CheckCollision(boss, bossBullet, emitter);
	emitter.Update();
}

void Tutorial::Draw(Player& player, Stage& stage, Boss boss, BossBullet bossBullet, PlayerWindEmitter playerWindEmitter,Emitter emitter) {
	stage.Draw();
	
	// skip
	DrawRhombusAnimation(
		pressFrame_ / 240.0f,
		{ 100.0f, 100.0f, },
		30.0f, 10.0f,
		0xFAFAFAFF,
		white1x1GH_
	);

	player.Draw();

	playerWindEmitter.Draw();
	
	emitter.Draw();

	// enemy Draw
	switch (progress_) {
		case Progress::ENEMY:

			boss.Draw(progressFrame_ / 60.0f);

			break;

		case Progress::BULLET:

			boss.Draw();
			bossBullet.Draw();

			break;
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

			//弾の説明
			if (!bulletExplanationChange_) {
				DrawWindow(
					{ 1060, 250 },
					{ 200, 80 },
					0xFAFAFAFF
				);

				DrawWindow(
					{ 1060, 350 },
					{ 200, 100 },
					0xFAFAFAFF
				);

				Novice::DrawSprite(
					950,
					200,
					bulletExplanationGH_[0],
					0.8f,
					0.8f,
					0.0f,
					0xFFFFFFFF
				);

				Novice::DrawSprite(
					950,
					300,
					bulletExplanationGH_[1],
					0.8f,
					0.8f,
					0.0f,
					0xFFFFFFFF
				);
			} else {

				DrawWindow(
					{ 1060, 250 },
					{ 200, 80 },
					0xFAFAFAFF
				);

				DrawWindow(
					{ 1060, 350 },
					{ 200, 90 },
					0xFAFAFAFF
				);

				DrawWindow(
					{ 1060, 450 },
					{ 200, 90 },
					0xFAFAFAFF
				);


				Novice::DrawSprite(
					950,
					200,
					bulletExplanationGH_[2],
					0.8f,
					0.8f,
					0.0f,
					0xFFFFFFFF
				);

				Novice::DrawSprite(
					950,
					300,
					bulletExplanationGH_[3],
					0.8f,
					0.8f,
					0.0f,
					0xFFFFFFFF
				);

				Novice::DrawSprite(
					950,
					400,
					bulletExplanationGH_[4],
					0.8f,
					0.8f,
					0.0f,
					0xFFFFFFFF
				);
			}

			break;

	}

}