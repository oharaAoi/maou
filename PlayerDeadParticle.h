#pragma once
#include <MyDeta/Source/MyStruct.h>
#include "MyDeta/Source/Coordinate.h"

class PlayerDeadParticle
{
public:
	PlayerDeadParticle(Vector2<float>pos,Vector2<float>velocity,float radius); // コンストラクタ
	~PlayerDeadParticle(); // デストラクタ

	void Update(); // 更新処理
	void Draw(); // 描画処理

	bool GetDelFlag(); //パーティクルが削除されたかを取得

private:
	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

	Vector2<float> pos_;
	Vector2<float> velocity_;
	float radius_;
	int alpha_ = 255;
	bool del_ = false;
};

