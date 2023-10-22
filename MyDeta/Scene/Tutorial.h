#pragma once
#include <Novice.h>

// source //
#include "MyDeta/Source/MyMath.h"

// system //
#include "MyDeta/Object/Stage.h"
#include "MyDeta/System/CollisionManager.h"

// object //
#include "MyDeta/Object/Player.h"
#include "MyDeta/Object/Boss.h"

// particle //
#include "MyDeta/Particle/Emitter.h"

enum Progress {
	MOVE,
	WINDOW,
	ENEMY,
	BULLET,
};

class Tutorial {
private:

	int white1x1GH_;

	bool isEndTutorial_;
	float pressFream_;

	Progress progress_;
	float progressFream_;

	

public:
	
	// constructor & destructor
	Tutorial();
	~Tutorial();

	// default method
	void Init();
	void Update(char* keys, char* preKeys, 
		Player& player, Stage& stage, Boss& boss, BossBullet& bossBullet, Emitter& emitter, CollisionManager& collisionManager);
	void Draw(Player player, Stage stage, Boss boss, BossBullet bossBullet);

	// user method

	// accessor
	bool GetIsEndTutorial() { return isEndTutorial_; }
};
