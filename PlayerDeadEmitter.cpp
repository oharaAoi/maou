#include "PlayerDeadEmitter.h"
#include "MyDeta/Particle/Util.h"
#include <Novice.h>

PlayerDeadEmitter::PlayerDeadEmitter()
{
}

PlayerDeadEmitter::~PlayerDeadEmitter()
{
}

void PlayerDeadEmitter::Update()
{
	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = playerDeadParticleList.begin(); itr != playerDeadParticleList.end();) {
		itr->Update();

		// Delフラグがtrueだったら
		if (itr->GetDelFlag()) {
			itr = playerDeadParticleList.erase(itr); // その要素を削除する
		} else {
			itr++; // eraseしなかった場合のみイテレーターをインクリメント
		}
	}

	//広がる円の更新処理
	if (circleAlpha_ > 0) {
		circleAlpha_ -= 15;
		circleRadius_ += 8.0f;
		isGenerate_ = true;
	} else {
		circleDel_ = true;
	}
}

void PlayerDeadEmitter::Draw()
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& playerDeadParticle : playerDeadParticleList) {
		playerDeadParticle.Draw();
	}

	//広がる円の描画処理
	Novice::DrawEllipse(
		static_cast<int>(circlePos_.x) + static_cast<int>(cie_->GetOrigine().x),
		static_cast<int>(circlePos_.y) + static_cast<int>(cie_->GetOrigine().y),
		static_cast<int>(circleRadius_), static_cast<int>(circleRadius_),
		0.0f,
		0xFFFFFF00 + circleAlpha_, kFillModeSolid
	);
}

void PlayerDeadEmitter::PlayerDeadEmit(int centerX, int centerY, int count)
{
	for (int i = 0; i < count; i++) {
		float particleX = static_cast<float>(Random(centerX - range_.x, centerX + range_.x));
		float particleY = static_cast<float>(Random(centerY - range_.y, centerY + range_.y));

		float velocityX = static_cast<float>(Random(-6, 6));
		float velocityY = static_cast<float>(Random(-6, 6));

		float radius = static_cast<float>(Random(4, 12)); //半径を指定範囲でランダムに設定

		PlayerDeadParticle newplayerDeadParticle = PlayerDeadParticle({ particleX,particleY }, { velocityX,velocityY }, radius);
		playerDeadParticleList.push_back(newplayerDeadParticle);
	}

	circlePos_ = { centerX,centerY }; //広がる円の中心座標を設定
	circleRadius_ = 20.0f;
	circleAlpha_ = 255;
	circleDel_ = false;

	isGenerate_ = false;
}
