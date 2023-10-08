#include <Novice.h>
#include <time.h>

// MySource //
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
//#include "MyDeta/Source/Easing.h"

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
	char keys[256] = {0};
	char preKeys[256] = {0};

	// マウス入力を受け取る
	int mouseX, mouseY;

	GameScene scene = TITLE;

	Emitter2 emitter;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		// マウス入力を受け取る
		Novice::GetMousePosition(&mouseX, &mouseY);

		switch (scene) {
		case TITLE:

			///
			/// ↓更新処理ここから
			/// 

			if (keys[DIK_SPACE]) {
				scene = TUTORIAL;
			}

			emitter.Update();

			// Pキーが押されたときのみパーティクルを生成
			if (keys[DIK_P] && !preKeys[DIK_P]) {
				emitter.Emit(mouseX,mouseY,12);
			}

			///
			/// ↑更新処理ここまで
			/// 
			
			///
			/// ↓描画処理ここから
			/// 

			emitter.Draw();

			///
			/// ↑描画処理ここまで
			/// 

			break;

		case TUTORIAL:

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

		case GAME:

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
