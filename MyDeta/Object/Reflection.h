#pragma once

// MySource //
#include "MyDeta/Source/MyStruct.h"

class Reflection {
private:

	enum ShapeType {

	};


	struct Base {
		ShapeType shapeType;
		Vector2 <float>pos; // world
	};

	Size <float>size_; // world

	static const int kMaxObjectNum = 10;
	Base Object_[kMaxObjectNum];

public:

	// constructor & destructor
	Reflection();
	~Reflection();

	// default method

	void Init();
	void Update();
	void Draw();

	// user method

};