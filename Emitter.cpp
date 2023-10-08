#include <Novice.h>
#include "Emitter.h"
#include "Util.h"

Emitter::Emitter()
{

}

Emitter::~Emitter()
{
}

void Emitter::Update()
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

void Emitter::Draw()
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

void Emitter::Emit(int centerX, int centerY, int count)
{
	// パーティクルを生成する処理を1フレームで12回行う

	for (int i = 0; i < count; i++) {
		float particleX = static_cast<float>(Random(centerX - rangeX_, centerX + rangeX_));
		float particleY = static_cast<float>(Random(centerY - rangeY_, centerY + rangeY_));

		float velocityX = static_cast<float>(Random(-8, 8));
		float velocityY = static_cast<float>(Random(-8, 8));

		Particle newParticle = Particle({ particleX,particleY }, { velocityX,velocityY }, 30);
		particleList.push_back(newParticle);
	}
}
