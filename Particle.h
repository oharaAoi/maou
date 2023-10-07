#pragma once
#include <MyDeta/Source/MyStruct.h>

class Particle
{
public:
	Particle(Vector2<float> pos,int maxTime);
	~Particle();

	void Update();
	void Draw();

	bool GetDelFlag();

private:
	Vector2<float> pos_;
	Vector2<float> velocity_;
	int timer_ = 0;
	int maxTime_;
	bool del_ = false;
};

