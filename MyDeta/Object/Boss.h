 #pragma once
#include <Novice.h>
// MySource //
#include "MyDeta/Source/MyStruct.h"
#include <MyDeta/Source/Environment.h>
// System //
#include "MyDeta/Source/Coordinate.h"
// MyObject //
#include "MyDeta/Object/BossBullet.h"

enum BossType {
	WAVE1,
	WAVE2,
	WAVE3
};

class Boss
{
private:

	//==============================
	Vector2 <float> pos_;
	float radius_;
	unsigned int color_;

	//==============================
	float hp_;
	bool isAlive_;

	//==============================
	int deathCount_;
	int frameCount_;
	int bulletChangeCount_;

	//==============================
	BossType type_;
	bool barrageChange_;

	//==============================
	//描画に使う
	int gh_;

	float drawWidth_;
	float drawHeight_;

	Vector2f spriteSize_;

	Vector2f drawLt_;

	int drawCount_;
	int drawCountLimit_;

	//==============================
	//sounds
	int gaugeBreakSE_;
	int gaugeBreakSEHandle_;
	float gaugeBreakSEVolume_;
	bool isGaugeBreakSE_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

	int white1x1GH;

public:

	Boss();

	void Init();

	void UpDate(BossBullet& bossBullet_);

	void Draw();

	void BulletSpeedChange(BossBullet& bossBullet_);

	void BossHpDecrece(char* keys, char* preKeys);

	// default method overload
	void Draw(float t);

	//アクセッサ
	//=================================================
	Vector2 <float>GetPos() { return pos_; }

	float GetRadius() { return radius_; }

	void SetColor(unsigned int color) { color_ = color; }
	unsigned int GetColor() { return color_; }

	//=================================================

	void SetHp(float hp) { hp_ = hp; }
	float GetHp() { return hp_; }

	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; }
	bool GetIsAlive() { return isAlive_; }

	void SetDeathCount(int num) { deathCount_ = num; }
	int GetDeathCount() { return deathCount_; }

	void SetBulletChange(bool flag) { barrageChange_ = flag; }
	bool GetBulletChange() { return barrageChange_; }

	//=================================================

	BossType GetType() { return type_; }

};

