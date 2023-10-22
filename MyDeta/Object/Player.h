#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

// MySource //
#include "MyDeta/Source/Environment.h"
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
#include "Matrix.h"

// MySystem //
#include "MyDeta/System/Zoom.h"
#include "MyDeta/Source/Coordinate.h"

// MyObject //
#include "MyDeta/Object/Stage.h"

enum ShotDirection {
	TO_CENTER, // 中心方向
	FROM_CENTER, // 中心と反対方向
};

enum WindowStrength {
	OFF,
	WEAK,
	STRONG
};

enum Restrictions {
	MOVE_ONLY,
};

class Player {
private:

	int white1x1GH;

	//==========================================
	//プレイヤーの座標や半径
	Vector2 <float>pos_; // world座標基準
	Vector2 <float>rangePos_;

	float radius_;
	float rangeRadius_;

	Size <float>size_; // world座標基準

	//==========================================
	//描画に使う
	int frameCount_;
	int frameCountLimit_;

	int gh_;
	float drawTheta_;

	float drawWidth_;
	float drawHeight_;

	Vector2f spriteSize;

	Vector2f drawLt_;

	Vector2f p2bDis_;
	Vector2f p2bVertical_;

	Vector2f originLt_;
	Vector2f originRt_;
	Vector2f originLb_;
	Vector2f originRb_;

	Vector2f lt_;
	Vector2f rt_;
	Vector2f lb_;
	Vector2f rb_;

	//回転行列
	Matrix3x3 rotateMatrix{};

	//平行移動行列
	Matrix3x3 translateMatrix{};

	//結合した行列
	Matrix3x3 worldMatrix{};

	//==========================================
	//角度やhpなどのステータス
	float radianSpeed_;
	float theta_;

	int hp_;
	float overHeat_;

	Vector2<float> windVolume_;

	WindowStrength windowStrength_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	// constructor & destructor
	Player();
	~Player();

	// default method
	void Init();
	void Update(char* keys, char* preKeys, Stage& stage_);
	void Draw();


	// default method - overload
	void Update(char* keys, Stage& stage_, Restrictions restriction); // -> use tutorial

	// accessor
	// center_
	Vector2 <float>GetPos() { return pos_; }
	Vector2 <float>GetRangePos() { return rangePos_; }

	// size_
	Size <float>GetSize() { return size_; }

	// radius_
	float GetRadius() { return radius_; }
	void SetRadius(float radius) { radius_ = radius; }
	float GetRangeRadius() { return rangeRadius_; }

	// hp
	void SetHp(int hp) { hp_ = hp; }
	int GetHp() { return hp_; }

	// windVolume
	void SetWindVolume(Vector2<float> valume) { windVolume_ = valume; }
	Vector2<float> GetWindVolume() { return windVolume_; }

	// windwStrength
	WindowStrength GetWindowStrength() { return windowStrength_; }
};

