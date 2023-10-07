#include <Novice.h>
#include "Emitter.h"

// 指定した範囲の乱数を生成する関数
int Random(int min, int max) {
	int range = max - min + 1;

	return rand() % range + min;
}

Emitter::Emitter()
{

}

Emitter::~Emitter()
{
}

void Emitter::Update()
{
	// パーティクルを生成する処理

	float particleX = static_cast<float>(Random(centerX - rangeX, centerX + rangeX));
	float particleY = static_cast<float>(Random(centerY - rangeY, centerY + rangeY));

	Particle newParticle = Particle({ particleX,particleY },60);
	particleList.push_back(newParticle);

	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update();

		if (itr->GetDelFlag()) {
			itr = particleList.erase(itr);
		} else {
			itr++;
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
	Novice::DrawBox(
		centerX - rangeX, centerY - rangeY,
		rangeX * 2, rangeY * 2,
		0.0f,
		WHITE, kFillModeWireFrame
	);

}
