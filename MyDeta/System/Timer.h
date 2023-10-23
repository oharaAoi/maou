#pragma once
#include <Novice.h>
#include <cmath>

// MySource //
//#include "MyDeta/Source/Easing.h"
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Coordinate.h"

#include "MyDeta/System/LoadFile.h"

class Timer {
private:

	int font_;
	Sizef fontSize_;

	float timer_;

	float bestTime_[3];

public:

	// constructor & destructor
	Timer();
	~Timer();

	// default method
	void Init();
	void Update();
	void Draw();

	// user method
	void DrawTimer(Vector2f pos, Sizef size, float time, unsigned int color);

	// accessor
	float GetTimer() { return timer_; }

	float* GetBestTimer() { return bestTime_; }
};

