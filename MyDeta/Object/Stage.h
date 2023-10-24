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

	static const int kCloudMax = 4;

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

	//==========================================
	//bgm
	//リソース
	int gameBgm_;

	//フラグ
	int gemeBgmHandle_;

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
	Vector2 <float>GetPos() { return pos_; }

	Vector2f GetScrollPos(int i) { return backGround_[i].pos; }

	float GetRadius() { return radius_; }

	float GetRangeRadius() { return rangeRadius_; }
	void SetRangeRadius(float radius) { rangeRadius_ = radius; }

	float GetBulletVanishRange() { return bulletVanishRange_; }

	int GetGemeBgmHandle() { return gemeBgmHandle_; }
	void SetGameBgmHandle(int flag) { gemeBgmHandle_ = flag; }

	void SetIsBlackOut(bool isBlackOut) { isBlackOut_ = isBlackOut; }
	bool GetIsBlackOut() { return isBlackOut_; }

	void SetIsBlackOutFinish(bool isBlackOutFinish) { isBlackOutFinish_ = isBlackOutFinish; }
	bool GetIsBlackOutFinish() { return isBlackOutFinish_; }

	unsigned int GetBlackOutColor() { return blackOutColor_; }

};

