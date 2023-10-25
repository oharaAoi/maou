#pragma once
#include <Novice.h>

// MySource //
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Easing.h"

// System //
#include "MyDeta/System/Timer.h"

class Result {
private:

	int resultGH_[1];

	bool isPressSpace_;
	bool isEndResult_;

	float resultFream_;

	// spaceChange
	Vector2f spaceGhPos_;
	Vector2f size_;
	Vector2f drawLt_;
	int spaceGH_;
	int spaceGhChangeCount_;

	//sound
	int gameClearSE_;
	int gameClearSEHandle_;
	float gameClearSEVolume_;

	int resultEndSE_;
	int resultEndSEHandle_;
	float  resultEndSEVolume_;
	bool isResultEndSE_;

public:

	// constructor & destructor
	Result();
	~Result();

	// default method
	void Init();
	void Update(char* keys, char* preKeys);
	void Draw(Timer timer);

	// user method

	// accessor
	bool GetIsEndResult() { return isEndResult_; }
};

