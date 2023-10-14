#pragma once
#include <Novice.h>
#include "MyDeta/Source/MyStruct.h"
#include "Coordinate.h"

class Stage
{
private:

	Vector2 <float> pos_;
	float radius_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	Stage();

	void Init();

	void Draw();

	//アクセッサ
	Vector2 <float>GetPos() { return pos_; }

	float GetRadius() { return radius_; }

};

