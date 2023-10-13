#include <Novice.h>
#include "Emitter2.h"
#include "Util.h"

Emitter2::Emitter2()
{

}

Emitter2::~Emitter2()
{
}

void Emitter2::Update()
{

	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update();

		// Delフラグがtrueだったら
		if (itr->GetDelFlag()) {
			itr = particleList.erase(itr); // その要素を削除する
		} else {
			itr++; // eraseしなかった場合のみイテレーターをインクリメント
		}
	}
}

void Emitter2::Draw()
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw();
	}

	// デバッグ用パーティクル範囲表示
	/*Novice::DrawBox(
		centerX_ - rangeX_, centerY_ - rangeY_,
		rangeX_ * 2, rangeY_ * 2,
		0.0f,
		WHITE, kFillModeWireFrame
	);*/

}

void Emitter2::Emit(int centerX, int centerY, int count)
{
	// パーティクルを生成する処理を1フレームで指定回数行う

	for (int i = 0; i < count; i++) {
		//パーティクルの粒の初期座標をランダムに生成
		float particleX = static_cast<float>(Random(centerX - rangeX_, centerX + rangeX_));
		float particleY = static_cast<float>(Random(centerY - rangeY_, centerY + rangeY_));

		//パーティクルの速度をランダムに生成
		float velocityX = static_cast<float>(Random(-8, 8));
		float velocityY = static_cast<float>(Random(-8, 8));

		//座標、速度、消えるまでのフレーム数を設定したパーティクルをリストに入れる
		Particle2 newParticle = Particle2({ particleX,particleY }, { velocityX,velocityY }, 60);
		particleList.push_back(newParticle);
	}
}

