#pragma once
#include <Novice.h>

// sorce //
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Easing.h"

class Title {
private:

	int whiteGH_;

	int backgroundGH_;
	int titleGH_;

	float frame_;

	// animations
	static const int animationNum_ = 3;
	float animationFrame_[animationNum_];

	//======================================
	// soundEffect credit
	int otLogicGh_;
	int pokketSoundGh_;
	int soundEffectGh_;


public:

	// constructor & destructor
	Title();
	~Title();

	// default method
	void Init();
	void Update();
	void Draw();

	// user method

	// accessor

};

