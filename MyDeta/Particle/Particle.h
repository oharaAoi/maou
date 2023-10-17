#pragma once
#include <MyDeta/Source/MyStruct.h>
#include "MyDeta/Source/Coordinate.h"

class Particle
{
public:
	Particle(Vector2<float> pos,Vector2<float> velocity,int maxTime);
	~Particle();

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
	int maxTime_;
	bool del_ = false;
};

