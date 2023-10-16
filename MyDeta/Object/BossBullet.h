#pragma once
#include <Novice.h>
// MySource //
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
// MySystem //
#include "MyDeta/Source/Coordinate.h"

enum BulletType {
	SLOW,
	FAST,
	EXPLODE,
	VANISH
};

class BossBullet
{
private:

	//==============================
	//
	Vector2<float> pos_;
	float radius_;

	unsigned int color_;

	float theta_;
	Vector2<float>velocity_;
	Vector2<float>accleleration_;
	Vector2<float>deceleration_;

	int type_;

	//==============================
	//当たり判定で使う
	bool isShot_;

	bool isRange_;

	bool isPushBacked_;

	float length_;

	Vector2<float> bullet2pDis_;

	//==============================

	struct Base {
		
	};

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	BossBullet();
	~BossBullet();

	void Init();

	void Update(Vector2<float> playerPos);

	void Draw();

	void IsShot(char* keys, char* preKeys, Vector2<float> playerPos);

	//=================================================
	/*アクセッサ*/
	void SetPos(Vector2<float> pos) { pos_ = pos; }
	Vector2<float>GetPos() { return pos_; }

	float GetRadius() { return radius_; }

	void SetColor(unsigned int color) { color_ = color; }
	unsigned int GetColor() { return color_; }

	//デバック用
	Vector2 <float> GetVelocity() { return velocity_; }

	//=================================================

	void SetIsShot(bool flag) { isShot_ = flag; }
	bool GetIsShot() { return isShot_; }

	void SetIsRange(bool flag) { isRange_ = flag; }
	bool GetIsRange() { return isRange_; }

	void SetIsPushBacked(bool flag) { isPushBacked_ = flag; }
	bool GetIsPushBacked() { return isPushBacked_; }
};

