#pragma once
#include <Novice.h>

// sorce //
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"

class Title {
private:

	int backgroundGH_;
	int titleGH_;

	static const int cloudNum = 3;

	int cloudGH_[cloudNum];
	Vector2f pos_[cloudNum];

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

