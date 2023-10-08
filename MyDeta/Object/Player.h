#pragma once
#include <Novice.h>

// MySource //
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"

class Player {
private:

	enum Mode {
		SEARCH,
		SHOT,
	};

	Mode mode_;

	Vector2 <float>pos_; // world座標基準
	Size <float>size_; // world座標基準

	// world座標基準はカメラzoom率をかけてscreenに映すこと。

	float speed_; // world座標基準

	Vector2 <float>velocity_;
	Vector2 <float>acceleration_;

	// world座標の1pxとzoomした1pxは違うので注意。

	/* --- totate --- */
	Vector2 <float>rotateCenter_; // world座標基準
	float b2radius_;
	float radian_;
	float theta_;

public:

	// constructor & destructor
	Player();
	~Player();

	// default method
	void Init();
	void Update(char* keys, char* preKeys);
	void Draw();

	// accessor
	// center_
	Vector2 <float>GetPos() { return pos_; }

	// size_
	Size <float>GetSize() { return size_; }

	// velocity_
	Vector2 <float>GetVelocity() { return velocity_; }
	void SetVelocity(Vector2 <float>velocity) { velocity_ = velocity; }
};

