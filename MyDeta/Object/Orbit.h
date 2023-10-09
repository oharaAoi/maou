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
		bool isHit;
		Vector2 <float>pos; // world
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
	// center_
	Vector2 <float>GetPos(int i) { return object_[i].pos; }

	// size
	Size <float>GetCollisionSize() { return collisionSize_; }

	// isAlive
	bool GetIsAlive(int i) { return object_[i].isAlive; }
	void SetIsAlive(int i, bool isAlive) { object_[i].isAlive = isAlive; }


	// isHit
	void SetIsHit(int i, bool isHit) { object_[i].isHit = isHit; }
};

