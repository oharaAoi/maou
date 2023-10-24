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

		float drawTheta;

		float drawWidth;
		float drawHeight;

		Vector2f drawLt;

		Vector2f p2bDis;
		Vector2f p2bVertical;

		Vector2f originLt;
		Vector2f originRt;
		Vector2f originLb;
		Vector2f originRb;

		Vector2f lt;
		Vector2f rt;
		Vector2f lb;
		Vector2f rb;

		//回転行列
		Matrix3x3 rotateMatrix{};

		//平行移動行列
		Matrix3x3 translateMatrix{};

		//結合した行列
		Matrix3x3 worldMatrix{};

		//==============================
		//速度
		Vector2<float>velocity;
		Vector2<float>accleleration;

		//==============================
		//フラグ
		bool isShot;
		bool isRange;
		bool isPushBacked;
		bool isHit;

		//==============================
		//タイプ
		int bulletType;

		int vanishCount;
		int explodeCount;

		//==============================
		// 弾が範囲外に出た時の変数
		//ステージ外に出た時の処理のための距離
		float center2bLength;

		//カウント
		int rangeOutCount;

		//==============================
		//撃つ角度
		float shotDire;

	};

	Base object_[kBulletMax_];

	int bulletGh_[4];

	//==============================
	//弾の速度(waveごとに速度を上げる)
	float slowSpeed_;
	float fastSpeed_;
	float explodeSpeed_;
	float vanishSpeed_;

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

	//==============================
	//サウンド
	int bossHitSe_;

	//音量
	float bossHitSeVolume_;


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

	void RotateBullet(int num, float theta);

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

	void SetIsHit(bool flag, int i) { object_[i].isHit = flag; }
	bool GetISHit(int i) { return object_[i].isHit; }

	void SetIsRange(bool flag , int i) { object_[i].isRange = flag; }
	bool GetIsRange(int i) { return object_[i].isRange; }

	void SetIsPushBacked(bool flag, int i) { object_[i].isPushBacked = flag; }
	bool GetIsPushBacked(int i) { return object_[i].isPushBacked; }

	//=================================================

	void SetRandTypeMax(int num) { randTypeMax_ = num; }
	int GetRandTypeMax() { return randTypeMax_; }

	Barrage GetBarrageType() { return barrageType_; }
	void SetBarrageType(Barrage type) { barrageType_ = type; }

	int GetBulletType(int i) { return object_[i].bulletType; }

	//=================================================
	void SetSlowSpeed(float speed) { slowSpeed_ = speed; }
	void SetFastSpeed(float speed) { fastSpeed_ = speed; }
	void SetExplodeSpeed(float speed) { explodeSpeed_ = speed; }
	void SetVanishSpeed(float speed) { vanishSpeed_ = speed; }

	void SetRandamCoolTimeLimit(int limit) { coolTimeRandamLimit_ = limit; }
	void SetChaseCoolTimeLimit(int limit) { coolTimeChaseLimit_ = limit; }
};

