#pragma once
#include <Novice.h>
#include <cmath>

// MySource //
//#include "MyDeta/Source/Easing.h"
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Coordinate.h"

class Timer {
private:

	int font_;

	float timer_;

public:

	// constructor & destructor
	Timer();
	~Timer();

	// default method
	void Init();
	void Update();
	void Draw();

	// user method
	void DrawTimer(float time);

	// accessor

};

