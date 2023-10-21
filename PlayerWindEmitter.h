#pragma once
#include "PlayerWindParticle.h"
#include <list>

class PlayerWindEmitter
{
public:
	PlayerWindEmitter();
	~PlayerWindEmitter();

	void Update(Vector2<float>playerPos, Vector2<float>bossPos,int maxTime ,int speed,int interval);
	void Draw();

	void Emit(float centerX, float centerY, float targetX, float targetY,int maxTime,int speed);



private:
	/*Particle particle = Particle ({ 640,0 });*/

	/*Particle particles[300];*/

	std::list<PlayerWindParticle> particleList;

	//パーティクルの範囲
	int centerX_ = 640;
	int rangeX_ = 20;

	int centerY_ = 100;
	int rangeY_ = 20;

	int timer_ = 0;
};

