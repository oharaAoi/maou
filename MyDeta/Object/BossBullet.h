#pragma once
#include <Novice.h>
// MySource //
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
// MySystem //
#include "MyDeta/Source/Coordinate.h"
#include <MyDeta/Source/Environment.h>

// MyObject //
#include "MyDeta/Object/Player.h"

enum BulletType {
	SLOW,
	FAST,
	EXPLODE,
	VANISH
};

//弾幕の種類
enum Barrage {
	NONE,
	CHASE,
	FOURS,
	ALL,
	ROTATE,
	RANDAM
};

class BossBullet
{
public:

	static const int kBulletMax_ = 30;

private:

	struct Base {
		//==============================
		//描画で使う
		BulletType type;

		Vector2f pos;
		float radius;

		unsigned int color;

		//==============================
		//速度
		Vector2<float>velocity;
		Vector2<float>accleleration;

		//==============================
		//フラグ
		bool isShot;
		bool isRange;
		bool isPushBacked;
		//==============================

		int bulletType;
	};

	Base objet_[kBulletMax_];
	
	//==============================
	//角度
	float bullet2pRadian_;
	float boss2pRadian_;

	float shotRadian_;

	float shotDire_;

	//==============================
	//2点間の距離
	Vector2<float> bullet2pDis_;
	Vector2<float> boss2pDis_;

	//==============================
	//フレームカウント
	int freamCount_;
	int slowdownCount_;

	//==============================
	static const int kRotateMax_ = 4;
	
	Barrage barrageType_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	BossBullet();
	~BossBullet();

	void Init();

	void Update(Vector2<float> bossPos, Player& player);

	void Draw();

	void RandamInit(int i);

	void OutOfScreenInit(int i);

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

