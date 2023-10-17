#pragma once
#include <MyDeta/Source/MyStruct.h>
#include "MyDeta/Source/Coordinate.h"

class Particle2
{
public:
	Particle2(Vector2<float> pos, Vector2<float> velocity, int maxTime);
	~Particle2();

	void Update();
	void Draw();

	bool GetDelFlag();

private:
	Vector2<float> pos_;
	Vector2<float> velocity_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

	//パーティクルの粒の長さを設定
	float length_ = 24.0f;

	int timer_ = 0;
	int maxTime_;
	bool del_ = false;
};


