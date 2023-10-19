#pragma once
#include <Novice.h>

// MySource //
#include "MyDeta/Source/Easing.h"
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Coordinate.h"

class MyOrbit {
private:

	// particle struct //
	struct Particle {
		bool isDisplay;

		Vector2 <float>center;
		Size <float>size;

		float freamCount;
		unsigned int color;
	};

	// particle //
	static const int particleNum_ = 30;

	Particle orbit_[particleNum_];

	// controll //
	float effectDistance_;

public:
	
	/* --- Init --- */
	void Init();

	/* --- Update --- */
	void Update(Vector2 <float>playerPos);

	/* --- Draw --- */
	void Draw();


};

