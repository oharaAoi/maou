#pragma once
#include <Novice.h>

#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Environment.h"

class GameOver
{
private:

	static const int kSelectMax = 2;

	struct Base {
		Vector2f pos;
		float width;
		float height;
		Vector2f size;
		int gh;
	};

	Base object_[kSelectMax];

	bool goToGame_;

	bool changeToGame_;
	bool changeToTitle_;

	//==========================================
	//背景
	int bgGh_;

	//==========================================
	//sound
	int gameOverBgm_;
	float gameOverBgmVolume_;

	bool playSound_;


public:

	GameOver();

	void Init();

	void Update(char* keys, char* preKeys);

	void Draw();

	//アクセッサ
	bool GetChangeToGame() { return changeToGame_; }
	bool GetChangeToTitle() { return changeToTitle_; }

	void SetPlaySound(bool playSound) { playSound_ = playSound; }
	bool GetPlaySound() { return  playSound_; }
};

