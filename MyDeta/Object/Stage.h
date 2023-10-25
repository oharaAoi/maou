#pragma once
#include <Novice.h>
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/Coordinate.h"
#include "MyDeta/Source/MyMath.h"

class Stage
{
private:

	Vector2 <float> pos_;
	float radius_;

	float rangeRadius_;

	float bulletVanishRange_;

	struct BackGround {
		Vector2f pos;
		int gh;
		unsigned int color;
	};

	BackGround backGround_[4];

	//==========================================

	static const int kCloudMax = 9;

	struct Base {
		Vector2f pos;
		Vector2f size;
		Vector2f velocity;
		int gh_;
		unsigned int color;
	};

	Base cloud[kCloudMax];

	//==========================================
	//ブラックアウトの変数
	bool isBlackOut_;
	bool isBlackOutFinish_;
	unsigned int blackOutColor_;

	//==========================================
	//フレームカウント
	float changeT_;
	float blackOutCount_;
	int cloudMoveTime_;

	//==========================================
	//bgm
	//リソース
	int gameBgm_;

	//フラグ
	int gameBgmHandle_;
	bool isStopSound_;

	//音量
	float gameBgmVolume_;


	//インスタンス
	Coordinate* cie_ = Coordinate::GetInstance();

public:

	Stage();

	void Init();

	void Update(int waveNum);

	void Draw();

	//アクセッサ
	/*中心の座標*/
	Vector2 <float>GetPos() { return pos_; }
	Vector2f GetScrollPos(int i) { return backGround_[i].pos; }

	/*中心の半径*/
	float GetRadius() { return radius_; }

	/*風の範囲*/
	float GetRangeRadius() { return rangeRadius_; }
	void SetRangeRadius(float radius) { rangeRadius_ = radius; }

	/*弾が消える範囲*/
	float GetBulletVanishRange() { return bulletVanishRange_; }

	/*音*/
	int GetGemeBgmHandle() { return gameBgmHandle_; }
	void SetGameBgmHandle(int flag) { gameBgmHandle_ = flag; }

	void SetIsStopSound(bool isStopSound) { isStopSound_ = isStopSound; }

	/*ブラックアウト*/
	void SetIsBlackOut(bool isBlackOut) { isBlackOut_ = isBlackOut; }
	bool GetIsBlackOut() { return isBlackOut_; }

	void SetIsBlackOutFinish(bool isBlackOutFinish) { isBlackOutFinish_ = isBlackOutFinish; }
	bool GetIsBlackOutFinish() { return isBlackOutFinish_; }

	unsigned int GetBlackOutColor() { return blackOutColor_; }

};

