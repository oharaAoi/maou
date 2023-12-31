#pragma once
#include <Novice.h>


// Library //
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Easing.h"

class BoxTransition {
private:

	int backgroundGH_;

	static const int kSubdivisionWidth_ = 16;
	static const int kSubdivisionHeight_ = 9;

	struct Base {
		Vector2f center;
		Sizef size;

		float theta;
	};

	Sizef maxSize_;
	Base object_[kSubdivisionHeight_ + 1][kSubdivisionWidth_ + 1];

public:

	// constructor & destructor
	BoxTransition();
	~BoxTransition();

	// default method
	void Init();
	void Update(float t);
	void Draw();

	// user method

	// accessor

};

