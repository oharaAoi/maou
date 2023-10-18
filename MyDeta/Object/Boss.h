#pragma once
#include <Novice.h>
// MySource //
#include "MyDeta/Source/MyStruct.h"
#include <MyDeta/Source/Environment.h>
//System
#include "MyDeta/Source/Coordinate.h"

enum BossType {
	wave1,
	wave2,
	wave3
};

class Boss
{
private:

	Vector2 <float> pos_;
	float radius_;
	unsigned int color_;

	float hp_;

	bool isAlive_;

	int dethCount_;

	BossType type_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	Boss();

	void Init();

	void UpDate();

	void Draw();

	//アクセッサ
	Vector2 <float>GetPos() { return pos_; }

	float GetRadius() { return radius_; }

	void SetColor(unsigned int color) { color_ = color; }
	unsigned int GetColor() { return color_; }

	void SetHp(float hp) { hp_ = hp; }
	float GetHp() { return hp_; }

	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; }
	bool GetIsAlive() { return isAlive_; }

	void SetDethCount(int num) { dethCount_ = num; }
	int GetDethCount() { return dethCount_; }

	BossType GetType() { return type_; }

};

