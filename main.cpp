#include <Novice.h>
#include <time.h>

// MySource //
//#include "MyDeta/Source/Easing.h"
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Coordinate.h"

// MySystem //
#include "MyDeta/System/CollisionManager.h"
#include "MyDeta/System/PlayerRangeDetector.h"
#include "MyDeta/System/Timer.h"
#include "MyDeta/System/LoadFile.h"


// MyObject //
#include "MyDeta/Object/Player.h"
#include "MyDeta/Object/Reflection.h"
#include "MyDeta/Object/Stage.h"
#include "MyDeta/Object/Boss.h"
#include "MyDeta/Object/BossBullet.h"

// MyParticle //
#include "MyDeta/Particle/Emitter.h"
#include "MyDeta/Particle/Emitter2.h"
#include "BossDeadParticle.h"
#include "PlayerDeadEmitter.h"
#include "PlayerWindEmitter.h"

// MySceneChange //
#include "MyDeta/SceneChange/BoxTransition.h"

// MyScene //
#include "MyDeta/Scene/Tutorial.h"
#include "MyDeta/Scene/Result.h"
#include "MyDeta/Scene/GameOver.h"
#include "MyDeta/Scene/title.h"


#include "MyDeta/System/LoadFile.h"

//シーン
enum GameScene {
	TITLE,
	TUTORIAL,
	GAME,
	GAME_OVER,
	RESULT
};

struct Sounds {
	int sound;
	int handle;
	float volume;
	bool isSound;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// 乱数のシード決定
	srand(static_cast<unsigned int>(time(nullptr)));

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	

	GameScene scene = TITLE;

	// エミッターのインスタンスを作成
	Emitter emitter;

	PlayerWindEmitter playerWindEmitter;

	PlayerDeadEmitter playerDeadEmitter;

	//========================================================
	// Source

	//========================================================
	//System
	CollisionManager collision;

	PlayerRangeDetector range_;
	range_.Init();

	LoadFile loadFile_;
	loadFile_.Init();

	//========================================================
	//Object
	//boss
	Boss boss_;
	boss_.Init();

	BossBullet bossBullet_;
	bossBullet_.Init();

	Stage stage_;
	stage_.Init();
	int waveNum = 0;

	Player player_;
	player_.Init();

	/* scene */
	// scene change
	float sceneT = 0.0f;
	bool isChangeScene = false;

	BoxTransition boxTransition;
	Timer timer;

	// game over
	GameOver gameOver_;
	gameOver_.Init();

	Tutorial tutorial;

	Result result;

	Title title;

	//========================================================
	//sound
	Sounds gameStartSE{};
	gameStartSE.sound = Novice::LoadAudio("./images/Sounds/sceneChangeSE/sceneChange.mp3");
	gameStartSE.handle = -1;
	gameStartSE.volume = 0.3f;
	gameStartSE.isSound = false;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);



		switch (scene) {
		case TITLE:

			///
			/// ↓更新処理ここから
			/// 

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				isChangeScene = true;
				gameStartSE.isSound = true;
			}

			title.Update();

			if (isChangeScene) {
				if (sceneT < 120.0f) { sceneT++; }

				if (sceneT == 120.0f) {
					scene = TUTORIAL;
					isChangeScene = false;

					gameStartSE.isSound = false;
					Novice::StopAudio(gameStartSE.handle);
				}

			} else {
				if (sceneT > 0.0f) { sceneT--; }
			}

			boxTransition.Update(sceneT);

			///
			/// ↑更新処理ここまで
			/// 

			///
			/// ↓描画処理ここから
			/// 

			title.Draw();

			boxTransition.Draw();
			Novice::ScreenPrintf(10, 10, "scene:%d", scene);

			//ゲームスタート時の音
			if (gameStartSE.isSound) {
				PlayAudio(gameStartSE.handle, gameStartSE.sound, gameStartSE.volume, false);
			} 

			///
			/// ↑描画処理ここまで
			/// 

			break;

		case TUTORIAL:

			///
			/// ↓更新処理ここから
			/// 

			if (tutorial.GetIsEndTutorial()) {
				isChangeScene = true;
			}

			if (isChangeScene) {
				if (sceneT < 120.0f) { sceneT++; }

				if (sceneT == 120.0f) {
					scene = GAME;
					isChangeScene = false;

					// -> GAME
					player_.Init();
					boss_.Init();
					bossBullet_.Init();
					collision.Init();
					stage_.Init();
					result.Init();
				}


			} else {
				if (sceneT > 0.0f) { sceneT--; }
			}

			tutorial.Update(keys, preKeys, player_, stage_, boss_, bossBullet_, emitter, collision, range_, playerWindEmitter);
			boxTransition.Update(sceneT);

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			/// 

			tutorial.Draw(player_, stage_, boss_, bossBullet_, playerWindEmitter);
			boxTransition.Draw();
			Novice::ScreenPrintf(10, 10, "scene:%d", scene);

			///
			/// ↑描画処理ここまで
			/// 

			break;

		case GAME:

			///
			/// ↓更新処理ここから
			/// 

			if (isChangeScene) {
				if (sceneT < 120.0f) { sceneT++; }

				if (sceneT == 120.0f) {
					scene = GAME;
					isChangeScene = false;
				}

			} else {
				if (sceneT > 0.0f) { sceneT--; }
			}

			boxTransition.Update(sceneT);

			// ==================================================

			if (!isChangeScene) {

				stage_.Update(waveNum);

				player_.Update(keys, preKeys, stage_);

				// ==================================================
				boss_.UpDate(bossBullet_);

				/* bossのwaveを保存 */
				waveNum = boss_.GetType();

				// ==================================================


				playerDeadEmitter.Update(); //プレイヤー死亡時のエミッターの更新処理

				if (player_.GetHp() <= 0 && playerDeadEmitter.GetIsGenerate() == false) { //プレイヤー死亡時にプレイヤーの位置にパーティクルを生成
					playerDeadEmitter.PlayerDeadEmit(static_cast<int>(player_.GetPos().x), static_cast<int>(player_.GetPos().y), 16);
				}
				if (player_.GetHp() > 0) {
					playerDeadEmitter.SetIsGenerate(false);
				}

				//デバック用
				boss_.BossHpDecrece(keys, preKeys);


				emitter.Update(); //エミッターの更新処理

				// プレイヤーの状態によって風エフェクトの消滅までの時間、速さ、発生間隔を変更
				switch (player_.GetWindowStrength()) {
				case OFF:
					playerWindEmitter.Update(player_.GetPos(), boss_.GetPos(), 0, 0, 1000);

					break;

				case WEAK:
					playerWindEmitter.Update(player_.GetPos(), boss_.GetPos(), 20, 6, 7);

					break;

				case STRONG:
					playerWindEmitter.Update(player_.GetPos(), boss_.GetPos(), 20, 12, 4);

					break;
				}

				//========================================================================
				/* 弾の処理 */
				//撃つ弾の種類を決める(デバック用)
				bossBullet_.BulletShotSelect(keys, preKeys);

				//弾を進める
				bossBullet_.Update(boss_.GetPos(), player_, stage_, emitter);

				//弾の更新
				range_.Update(player_, bossBullet_);


				//弾とプレイヤー
				collision.CheckCollision(player_, bossBullet_, emitter);


				//弾と敵の当たり判定
				collision.CheckCollision(boss_, bossBullet_, emitter);

				//========================================================================

				timer.Update();

				//========================================================================
				//3WAVE目にボスを倒していたらresultに移行
				if (boss_.GetType() == WAVE3 && boss_.GetIsAlive() == false) {
					scene = RESULT;

					loadFile_.WriteFile(timer.GetTimer());

					loadFile_.LoadJsonFile(timer.GetBestTimer());

					player_.SetIsWindSeStop(true);
				}

				//========================================================================
				//playerが死んだらgameOverへ
				if (player_.GetIsAlive() == false) {
					scene = GAME_OVER;
				}


				if (keys[DIK_G]) {
					scene = GAME_OVER;
				}
			}

			///
			/// ↑更新処理ここまで
			/// 

			///
			/// ↓描画処理ここから
			/// 

			stage_.Draw();
			boss_.Draw();
			range_.Draw();
			emitter.Draw(); // エミッターの描画処理を呼ぶ
			playerWindEmitter.Draw(); // プレイヤーの風の描画処理
			playerDeadEmitter.Draw(); // プレイヤー死亡時のパーティクルの描画処理

			bossBullet_.Draw();

			timer.Draw();

			player_.Draw();

			boxTransition.Draw();

			if (stage_.GetIsBlackOut() == true) {
				Novice::DrawBox(
					0,
					0,
					1280,
					720,
					0.0f,
					stage_.GetBlackOutColor(),
					kFillModeSolid
				);
			}


			///
			/// ↑描画処理ここまで
			/// 

			break;

		case GAME_OVER:

			///
			/// ↓更新処理ここから
			/// 

			//プレイヤーの音を止めてしまう(余裕があったら変えたい)
			player_.AllSoundStop();

			gameOver_.Update(keys, preKeys);

			if (gameOver_.GetChangeToGame() == true) {
				scene = GAME;
				range_.Init();
				boss_.Init();
				bossBullet_.Init();
				player_.Init();
				gameOver_.Init();
				timer.Init();
				stage_.Init();

			} else if (gameOver_.GetChangeToTitle() == true) {
				scene = TITLE;
				range_.Init();
				boss_.Init();
				bossBullet_.Init();
				player_.Init();
				gameOver_.Init();
				timer.Init();
				stage_.Init();
			}

			///
			/// ↑更新処理ここまで
			/// 

			///
			/// ↓描画処理ここから
			/// 

			gameOver_.Draw();

			///
			/// ↑描画処理ここまで
			/// 

			break;

		case RESULT:

			///
			/// ↓更新処理ここから
			/// 

			//プレイヤーの音を止めてしまう(余裕があったら変えたい)
			player_.AllSoundStop();

			result.Update(keys, preKeys);

			if (result.GetIsEndResult()) {
				scene = GameScene::TITLE;
				range_.Init();
				boss_.Init();
				bossBullet_.Init();
				stage_.Init();
				player_.Init();
				gameOver_.Init();
				timer.Init();
				tutorial.Init();
			}

			///
			/// ↑更新処理ここまで
			/// 

			///
			/// ↓描画処理ここから
			/// 

			boss_.Draw();
			stage_.Draw();
			player_.Draw();
			range_.Draw();
			emitter.Draw(); // エミッターの描画処理を呼ぶ
			playerWindEmitter.Draw(); // プレイヤーの風の描画処理

			result.Draw(timer);

			///
			/// ↑描画処理ここまで
			/// 

			break;
		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
