#pragma once
#include "Particle.h"
#include <list>

class Emitter
{
public:
	Emitter();
	~Emitter();

	void Update();
	void Draw();

	//パーティクルの範囲
	int centerX = 640;
	int rangeX = 300;

	int centerY = 100;
	int rangeY = 50;

private:
	/*Particle particle = Particle ({ 640,0 });*/

	/*Particle particles[300];*/

	std::list<Particle> particleList;

};

