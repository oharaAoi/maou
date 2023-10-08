#pragma once
#include "Particle2.h"
#include <list>

class Emitter2
{
public:
	Emitter2();
	~Emitter2();

	void Update();
	void Draw();

	void Emit(int centerX, int centerY, int count);



private:
	/*Particle particle = Particle ({ 640,0 });*/

	/*Particle particles[300];*/

	std::list<Particle2> particleList;

	//パーティクルの範囲
	int centerX_ = 640;
	int rangeX_ = 20;

	int centerY_ = 100;
	int rangeY_ = 20;

};



