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
#include "MyDeta/Object/Stage.h"

// Particle //
#include "MyDeta/Particle/Emitter.h"
#include "MyDeta/Particle/Emitter2.h"

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
	CHASE,
	FOURS,
	ALL,
	ROTATE,
};

class BossBullet
{
public:

	static const int kBulletMax_ = 60;

private:

	struct Base {
		//==============================
		//描画で使う
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
		//タイプ
		int bulletType;

		int vanishCount;
		int explodeCount;

		//==============================
		// 距離
		//ステージ外に出た時の処理のための距離
		float center2bLength;

	};

	Base object_[kBulletMax_];

	//==============================
	//弾の速度(waveごとに速度を上げる)
	float slowSpeed_;
	float fastSpeed_;
	float explodeSpeed_;
	float vanishSpeed_;
	
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

	//誘爆のために弾と弾の距離を取る
	float b2bLength_;

	//==============================
	//フレームカウント
	int freamCount_;
	int slowdownCount_;

	int coolTimeLimit_;

	int coolTimeRandamLimit_;
	int coolTimeChaseLimit_ ;

	//==============================
	static const int kRotateMax_ = 4;
	int randTypeMax_;

	Barrage barrageType_;

	//爆発する半径
	float explodeRadius_;

	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	BossBullet();
	~BossBullet();

	void Init();

	void Update(Vector2<float> bossPos, Player& player, Stage stage, Emitter& emitter);

	void Draw();

	void RandamInit(int i);

	void OutOfScreenInit(int i);

	//=================================================
	//弾幕の種類
	void BulletShotSelect(char* keys, char* preKeys);
	void BulletShotChange(Barrage type);

	void BarrageInit();

	/*void BulletSpeedChange(BossType wave);*/

	void IsShot(Vector2<float> playerPos);

	void FourDireIsShot(int i);

	void AllDireShot();

	void RotateDireShot();

	void RandamDireShot();

	//=================================================
	void ExplodeBullet(int num, Emitter& emitter);

	//=================================================
	/*アクセッサ*/
	void SetPos(Vector2<float> pos_, int i) { object_[i].pos = pos_; }
	Vector2<float>GetPos(int i) { return object_[i].pos; }

	float GetRadius(int i) { return object_[i].radius; }

	void SetColor(unsigned int color, int i) { object_[i].color = color; }
	unsigned int GetColor(int i) { return object_[i].color; }

	//デバック用
	Vector2 <float> GetVelocity(int i) { return object_[i].velocity; }

	//=================================================

	void SetIsShot(bool flag , int i) { object_[i].isShot = flag; }
	bool GetIsShot(int i) { return object_[i].isShot; }

	void SetIsRange(bool flag , int i) { object_[i].isRange = flag; }
	bool GetIsRange(int i) { return object_[i].isRange; }

	void SetIsPushBacked(bool flag, int i) { object_[i].isPushBacked = flag; }
	bool GetIsPushBacked(int i) { return object_[i].isPushBacked; }

	//=================================================

	void SetRandTypeMax(int num) { randTypeMax_ = num; }
	int GetRandTypeMax() { return randTypeMax_; }

	Barrage GetBarrageType() { return barrageType_; }
	void SetBarrageType(Barrage type) { barrageType_ = type; }

	//=================================================
	void SetSlowSpeed(float speed) { slowSpeed_ = speed; }
	void SetFastSpeed(float speed) { fastSpeed_ = speed; }
	void SetExplodeSpeed(float speed) { explodeSpeed_ = speed; }
	void SetVanishSpeed(float speed) { vanishSpeed_ = speed; }

	void SetRandamCoolTimeLimit(int limit) { coolTimeRandamLimit_ = limit; }
	void SetChaseCoolTimeLimit(int limit) { coolTimeChaseLimit_ = limit; }
};

