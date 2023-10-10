#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

// MySource //
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"

// MySystem //
#include "MyDeta/System/Zoom.h"

enum Mode {
	SEARCH,
	SHOOT,
};

enum ShotDirection {
	TO_CENTER, // 中心方向
	FROM_CENTER, // 中心と反対方向
};

class Player {
private:

	Mode mode_;

	Vector2 <float>pos_; // world座標基準
	Size <float>size_; // world座標基準

	// world座標基準はカメラzoom率をかけてscreenに映すこと。

	float speed_; // world座標基準

	// world座標の1pxとzoomした1pxは違うので注意。

	/* --- totate --- */
	Vector2 <float>rotateCenter_; // world座標基準
	float b2Length_;

	float radius_;
	float radian_;
	float theta_;

	ShotDirection shotDirection_;

	Vector2 <float>velocity_;
	Vector2 <float>acceleration_;

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

	// mode_
	void SetMode(Mode mode) { mode_ = mode; }

	// shotDirection
	void SetDirection(ShotDirection shotDirection) { shotDirection_ = shotDirection; }

	// radius_
	void SetRadius(float radius) { radius_ = radius; }

	// radian_
	void SetRadian(float radian) { radian_ = radian; }

	// rotateCenter_
	void SetRotateCenter(Vector2 <float>center) { rotateCenter_ = center; }
};

