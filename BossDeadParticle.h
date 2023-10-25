#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/Coordinate.h"

class BossDeadParticle
{
public:
	BossDeadParticle(); //コンストラクタ
	~BossDeadParticle(); //デストラクタ

	void Update(); //更新処理
	void Draw(); //描画処理
	void Start(int posX,int posY); //この関数が呼ばれたときにパーティクルを生成する

private:
	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

	struct Circle {
		Vector2<float> pos_;
		Vector2<float> velocity_;
		int alpha_;
		int radius_;
		bool del_;
	};

	Circle circle_[8];
	int speed_ = 8;

};

