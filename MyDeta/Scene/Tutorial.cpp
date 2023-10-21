#include "Tutorial.h"

Tutorial::Tutorial() {

	Init();

	white1x1GH_ = Novice::LoadTexture("./NoviceResources/white1x1.png");
}

Tutorial::~Tutorial() {
}

void Tutorial::Init() {
	isEndTutorial_ = false;
	pressFream_ = 60.0f * 4/*s*/;

	progress_ = MOVE;
	progressFream_ = 0.0f;
}

void Tutorial::Update(char* keys, char* preKeys,
	Player& player, Stage& stage, Boss& boss, BossBullet& bossBullet, Emitter& emitter, CollisionManager& collisionManager) {
	if (keys[DIK_SPACE]) {
		if (pressFream_ > 0.0f) { pressFream_--; }

		if (pressFream_ == 0.0f) {
			isEndTutorial_ = true;
		}

	} else {
		if (pressFream_ > 0.0f) {
			pressFream_ = 60.0f * 4/*s*/;
		}
	}

	player.Update(keys, preKeys, stage);

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

			if (progressFream_ < 60.0f * 10/*s*/) {
				progressFream_++;
			
			} else {
				progress_ = Progress::BULLET;
				progressFream_ = 0.0f;
			}
		

			break;

		case Progress::BULLET:

			boss.UpDate(bossBullet);
			bossBullet.Update(boss.GetPos(), player, stage, emitter);

			if (progressFream_ < 60.0f * 10/*s*/) {
				progressFream_++;

			} else {
				isEndTutorial_ = true;
			}

			break;
	}

	collisionManager.CheckCollision(player, bossBullet);
	collisionManager.CheckCollision(boss, bossBullet, emitter);
}

void Tutorial::Draw(Player player, Stage stage, Boss boss, BossBullet bossBullet) {
	// skip
	DrawRhombusAnimation(
		pressFream_ / 240.0f,
		{100.0f, 100.0f,},
		30.0f, 10.0f,
		0xFAFAFAFF,
		white1x1GH_
	);
	
	stage.Draw();
	player.Draw();

	if (progress_ >= Progress::ENEMY) {
		boss.Draw();
		bossBullet.Draw();
	}
}
