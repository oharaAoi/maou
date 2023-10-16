#pragma once
#include <Novice.h>

// MySource //
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Coordinate.h"

class PlayerRangeDetector
{
private:

	Vector2<float>b2pDis_;

	//プレイヤーと敵(弾)とのベクトル
	Vector2<float>e2pDis_;

	//プレイヤーとボスとの単位ベクトル
	Vector2<float>unitB2pDis_;

	//ボスとプレイヤーの線形補完
	Vector2<float>b2pLinearCompletion_;

	//敵(弾)の距離(最近傍点)
	Vector2<float>nearBulletPos_;

	float b2pLength_;

	float nearLength_;

	float time_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

	//デバック用(後で消す)
	Vector2<float> verticalLine;

	float vertialTheta;

	Vector2<float> topLineSt;
	Vector2<float> topLineEnd;

	Vector2<float> bottomLineSt;
	Vector2<float> bottomLineEnd;

public:

	PlayerRangeDetector();

	void Init();

	void Update(Vector2<float>playerPos_, Vector2<float>bulletPos_, Vector2<float>bossPos_,
				float playerRadius, float rangeRadius);

	void Draw();

};

