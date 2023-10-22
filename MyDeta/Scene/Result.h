#pragma once
#include <Novice.h>

// MySource //
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"

class Result {
private:

	bool isPressSpace_;
	bool isEndResult_;

	float resultFream_;

public:

	// constructor & destructor
	Result();
	~Result();

	// default method
	void Init();
	void Update(char* keys, char* preKeys);
	void Draw();

	// user method

	// accessor
	bool GetIsEndResult() { return isEndResult_; }
};

