#pragma once
#include "PlayerDeadParticle.h"
#include <list>

class PlayerDeadEmitter
{
public:
	PlayerDeadEmitter(); //コンストラクタ
	~PlayerDeadEmitter(); //デストラクタ

	void Update(); //更新処理
	void Draw(); //描画処理

	void PlayerDeadEmit(int centerX, int centerY, int count); //パーティクルの生成関数

private:
	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

	std::list<PlayerDeadParticle> playerDeadParticleList; //パーティクルを格納するリストを作成

	Vector2<int> range_ = { 20,20 }; //パーティクル出現範囲

	//広がっていく円の情報
	Vector2<int> circlePos_ = { 0,0 };
	float circleRadius_ = 0.0f;
	int circleAlpha_ = 0;
	bool circleDel_ = false;
};

