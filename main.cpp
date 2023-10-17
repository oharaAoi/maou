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

// MyObject //
#include "MyDeta/Object/Player.h"
#include "MyDeta/Object/Reflection.h"
#include "MyDeta/Object/Stage.h"
#include "MyDeta/Object/Boss.h"
#include "MyDeta/Object/BossBullet.h"

// MyParticle //
#include "Emitter.h"
#include "Emitter2.h"

//シーン
enum GameScene {
	TITLE,
	TUTORIAL,
	GAME,
	RESULT
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

	//========================================================
	//System
	CollisionManager collision;

	Coordinate* cie_ = Coordinate::GetInstance();
	cie_->Init();

	PlayerRangeDetector range_;
	range_.Init();

	//========================================================
	//Object
	//boss
	Boss boss_;
	boss_.Init();


	BossBullet bossBullet_;
	bossBullet_.Init();

	Stage stage_;
	stage_.Init();

	Player player_;
	player_.Init();

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

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {
				scene = TUTORIAL;
			}

			///
			/// ↑更新処理ここまで
			/// 

			///
			/// ↓描画処理ここから
			/// 

			Novice::ScreenPrintf(10, 10, "scene:%d", scene);

			///
			/// ↑描画処理ここまで
			/// 

			break;

		case TUTORIAL:

			///
			/// ↓更新処理ここから
			/// 

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {
				scene = GAME;
			}

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			/// 

			Novice::ScreenPrintf(10, 10, "scene:%d", scene);

			///
			/// ↑描画処理ここまで
			/// 

			break;

		case GAME:

			///
			/// ↓更新処理ここから
			/// 

			player_.Update(keys, preKeys, stage_);

			//========================================================================
			//弾の更新
			range_.Update(player_, bossBullet_);

			//撃つ弾の種類を決める
			bossBullet_.BulletShotSelect(keys, preKeys);

			//弾を進める
			bossBullet_.Update(boss_.GetPos(), player_.GetPos());

			//弾とプレイヤー
			collision.CheckCollision(player_, bossBullet_);

			//弾と敵の当たり判定
			collision.CheckCollision(boss_, bossBullet_);

			//========================================================================

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


			bossBullet_.Draw();

			/*Novice::ScreenPrintf(10, 10 + (i * 20), "isPushBack:%d", bossBullet_[i].GetIsPushBacked());
			Novice::ScreenPrintf(150, 10 + (i * 20), "isShot:%d", bossBullet_[i].GetIsShot());*/

			/*Novice::ScreenPrintf(800, 10 + (i * 20), "bulletVelocity.x:%f", bossBullet_[i].GetVelocity().x);*/



		///
		/// ↑描画処理ここまで
		/// 

			break;

		case RESULT:

			///
			/// ↓更新処理ここから
			/// 

			///
			/// ↑更新処理ここまで
			/// 

			///
			/// ↓描画処理ここから
			/// 

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
