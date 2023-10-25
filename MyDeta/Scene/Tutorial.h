#pragma once
#include <Novice.h>

// source //
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/JapaneseAscii.h"

// system //
#include "MyDeta/Object/Stage.h"
#include "MyDeta/System/CollisionManager.h"
#include "MyDeta/System/PlayerRangeDetector.h"

// object //
#include "MyDeta/Object/Player.h"
#include "MyDeta/Object/Boss.h"

// particle //
#include "MyDeta/Particle/Emitter.h"
#include "PlayerWindEmitter.h"

enum Progress {
	MOVE,
	WINDOW,
	ENEMY,
	BULLET,
};

class Tutorial {
private:

	int japaneseFontGH_;
	int white1x1GH_;

	bool isEndTutorial_;
	float pressFrame_;

	Progress progress_;
	float progressFrame_;
	bool isTriggerSpace_;

	int tutorialGH_[3];

	int bulletExplanationGH_[5];

	int bulletExplanationCount_;
	bool bulletExplanationChange_;

public:
	
	// constructor & destructor
	Tutorial();
	~Tutorial();

	// default method
	void Init();
	void Update(char* keys, char* preKeys, 
		Player& player, Stage& stage, Boss& boss, BossBullet& bossBullet, Emitter& emitter, CollisionManager& collisionManager, PlayerRangeDetector& playerRangeDetector, PlayerWindEmitter& playerWindEmitter);
	void Draw(Player& player, Stage& stage, Boss boss, BossBullet bossBullet, PlayerWindEmitter playerWindEmitter, Emitter emitter);

	// user method

	// accessor
	bool GetIsEndTutorial() { return isEndTutorial_; }
};

