#pragma once
#include <Novice.h>

// source //
#include "MyDeta/Source/MyMath.h"

enum Progress {
	MOVE,
	WINDOW,
	ENEMY,
	BULLET,
};

class Tutorial {
private:

	int white1x1GH_;

	bool isEndTutorial_;
	float pressFream_;

	Progress progress_;
	float progressFream_;

	

public:
	
	// constructor & destructor
	Tutorial();
	~Tutorial();

	// default method
	void Init();
	void Update(char* keys, char* preKeys);
	void Draw();

	// user method

	// accessor

};

