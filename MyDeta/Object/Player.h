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
#include "MyDeta/Source/Coordinate.h"

enum ShotDirection {
	TO_CENTER, // 中心方向
	FROM_CENTER, // 中心と反対方向
};

class Player {
private:

	Vector2 <float>pos_; // world座標基準
	Vector2 <float>rangePos_;

	float radius_;
	float rangeRadius_;

	Size <float>size_; // world座標基準

	float theta_;

	int hp_;

	ShotDirection shotDirection_;

	Vector2 <float>velocity_;
	Vector2 <float>acceleration_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	// constructor & destructor
	Player();
	~Player();

	// default method
	void Init();
	void Update(char* keys, Vector2<float> stagePos, float radius, float rangeRadius);
	void Draw();

	// accessor
	// center_
	Vector2 <float>GetPos() { return pos_; }
	Vector2 <float>GetRangePos() { return rangePos_; }

	// size_
	Size <float>GetSize() { return size_; }

	// velocity_
	Vector2 <float>GetVelocity() { return velocity_; }
	void SetVelocity(Vector2 <float>velocity) { velocity_ = velocity; }

	// shotDirection
	void SetDirection(ShotDirection shotDirection) { shotDirection_ = shotDirection; }

	// radius_
	float GetRadius() { return radius_; }
	void SetRadius(float radius) { radius_ = radius; }

	float GetRangeRadius() { return rangeRadius_; }

	void SetHp(int hp) { hp_ = hp; }
	int GetHp() { return hp_; }

};

