#pragma once

// MySource //
#include "MyDeta/Source/MyStruct.h"

class Orbit {
private:

	// world基準
	Size <float>displaySize_; // 中の円
	Size <float>collisionSize_; // 外の円

	struct Base {
		bool isAlive;
		Vector2 <float>center; // world
	};

	static const int kMaxObjectNum_ = 10;
	Base object_[kMaxObjectNum_];

public:

	// constructor & destructor
	Orbit();
	~Orbit();

	// default method
	void Init();
	void Update();
	void Draw();

	// user method

	// accossor

};

