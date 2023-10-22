#include <Novice.h>
#include "PlayerWindEmitter.h"
#include "MyDeta/Particle/Util.h"

PlayerWindEmitter::PlayerWindEmitter()
{

}

PlayerWindEmitter::~PlayerWindEmitter()
{
}

void PlayerWindEmitter::Update(Vector2<float>playerPos,Vector2<float>bossPos,int maxTime,int speed, int interval)
{
	timer_++;
	if (timer_ % interval == 0) {
		PlayerWindEmitter::Emit(playerPos.x, playerPos.y, bossPos.x, bossPos.y,maxTime,speed);
	}

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

void PlayerWindEmitter::Draw()
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

void PlayerWindEmitter::Emit(float centerX, float centerY, float targetX, float targetY, int maxTime,int speed)
{
		float particleX = centerX;
		float particleY = centerY;

		PlayerWindParticle newParticle = PlayerWindParticle({ particleX,particleY }, { targetX,targetY }, maxTime,speed);
		particleList.push_back(newParticle);
}

