#pragma once
#include <MyDeta/Source/MyStruct.h>
#include "MyDeta/Source/Coordinate.h"

class PlayerWindParticle
{
public:
	PlayerWindParticle(Vector2<float> startPos, Vector2<float> targetPos,  int maxTime,int speed);
	~PlayerWindParticle();

	void Update();
	void Draw();

	bool GetDelFlag();

private:
	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

	Vector2<float> pos_;
	float radius_;
	Vector2<float> velocity_;
	int timer_ = 0;
	int alpha_ = 100;
	int speed_;
	int maxTime_;
	bool del_ = false;
};

