#pragma once
#include <MyDeta/Source/MyStruct.h>

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
	int timer_ = 0;
	int maxTime_;
	bool del_ = false;
};


