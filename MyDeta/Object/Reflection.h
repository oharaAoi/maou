#pragma once
#include <Novice.h>

// MySource //
#include "MyDeta/Source/MyStruct.h"

class Reflection { // 赤色のやつ
private:

	enum ShapeType {
		CIRCLE,
		SQUARE,
	};


	struct Base {
		ShapeType shapeType;

		bool isAlive;
		Vector2 <float>center; // world
	};

	Size <float>size_; // world

	static const int kMaxObjectNum = 10;
	Base object_[kMaxObjectNum];

public:

	// constructor & destructor
	Reflection();
	~Reflection();

	// default method

	void Init();
	void Update();
	void Draw();

	// user method
	// accessor
	// center_
	Vector2 <float>GetCenter(int i) { return object_[i].center; }

	// size
	Size <float>GetSize() { return size_; }

	// isAlive
	void SetIsAlive(int i, bool isAlive) { object_[i].isAlive = isAlive; }
};