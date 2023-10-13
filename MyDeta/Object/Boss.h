#pragma once
#include <Novice.h>
// MySource //
#include "MyDeta/Source/MyStruct.h"
#include <MyDeta/Source/Environment.h>

enum BossType {
	wave1,
	wave2,
	wave3
};

class Boss
{
private:

	Vector2 <float> pos_;
	float radius_;
	unsigned int color_;

	float hp_;

	BossType type_;

public:

	Boss();

	void Init();

	void UpDate();

	void Draw();

};

