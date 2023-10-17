#pragma once
#include <Novice.h>
// MySource //
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
// MySystem //
#include "MyDeta/Source/Coordinate.h"
#include <MyDeta/Source/Environment.h>

enum BulletType {
	SLOW,
	FAST,
	EXPLODE,
	VANISH
};

//弾幕の種類
enum Barrage {
	NONE,
	RANDAM,
	FOURS,
	ALL,
	ROTATE
};

class BossBullet
{
private:

	/*Vector2<float> pos_;
	float radius_;*/

	static const int kBulletMax_ = 30;

	struct Base {

		//==============================
		//描画で使う
		BulletType type;

		Vector2f pos;
		float radius;

		unsigned int color;

		Vector2<float>velocity;
		Vector2<float>accleleration;
		Vector2<float>deceleration;

		//==============================
		//当たり判定で使う
		bool isShot;

		bool isRange;

		bool isPushBacked;
		//==============================

		int bulletType;

	};

	Base objet_[kBulletMax_];
	
	//==============================

	float bullet2pRadian_;
	float boss2pRadian_;

	Vector2<float> bullet2pDis_;
	Vector2<float> boss2pDis_;

	int freamCount_;

	static const int kRotateMax_ = 4;

	float shotDire_;
	float shotRadian_;

	Barrage barrageType_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	BossBullet();
	~BossBullet();

	void Init();

	void Update(Vector2<float> bossPos, Vector2<float>playerPos);

	void Draw();

	void RandamInit(int i);

	//=================================================
	//弾幕の種類
	void BulletShotSelect(char* keys, char* preKeys);

	void IsShot(Vector2<float> playerPos);

	void FourDireIsShot(int i);

	void AllDireShot();

	void RotateDireShot();

	//=================================================
	/*アクセッサ*/
	void SetPos(Vector2<float> pos_, int i) { objet_[i].pos = pos_; }
	Vector2<float>GetPos(int i) { return objet_[i].pos; }

	float GetRadius(int i) { return objet_[i].radius; }

	void SetColor(unsigned int color, int i) { objet_[i].color = color; }
	unsigned int GetColor(int i) { return objet_[i].color; }

	//デバック用
	Vector2 <float> GetVelocity(int i) { return objet_[i].velocity; }

	//=================================================

	void SetIsShot(bool flag , int i) { objet_[i].isShot = flag; }
	bool GetIsShot(int i) { return objet_[i].isShot; }

	void SetIsRange(bool flag , int i) { objet_[i].isRange = flag; }
	bool GetIsRange(int i) { return objet_[i].isRange; }

	void SetIsPushBacked(bool flag, int i) { objet_[i].isPushBacked = flag; }
	bool GetIsPushBacked(int i) { return objet_[i].isPushBacked; }

	//=================================================

	Barrage GetBarrageType() { return barrageType_; }
	void SetBarrageType(Barrage type) { barrageType_ = type; }
};

