#pragma once
#include <Novice.h>
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/Coordinate.h"
#include "MyDeta/Source/MyMath.h"

class Stage
{
private:

	Vector2 <float> pos_;
	float radius_;

	float rangeRadius_;

	float bulletVanishRange_;

	int gh_;

	unsigned int color_;

	//==========================================

	static const int kCloudMax = 4;

	struct Base {
		Vector2f pos;
		Vector2f size;
		Vector2f velocity;
		int gh_;
	};

	Base cloud[kCloudMax];

	//==========================================
	//bgm
	//リソース
	int gameBgm_;

	//フラグ
	int gemeBgmHandle_;

	//音量
	float gameBgmVolume_;


	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	Stage();

	void Init();

	void Update();

	void Draw();

	//アクセッサ
	Vector2 <float>GetPos() { return pos_; }

	float GetRadius() { return radius_; }

	float GetRangeRadius() { return rangeRadius_; }
	void SetRangeRadius(float radius) { rangeRadius_ = radius; }

	float GetBulletVanishRange() { return bulletVanishRange_; }

};

