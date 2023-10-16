#pragma once
#include <Novice.h>
// MySource //
#include "MyDeta/Source/MyStruct.h"
#include "MyDeta/Source/MyMath.h"
// MySystem //
#include "MyDeta/Source/Coordinate.h"

class BossBullet
{
private:

	//基本のもの
	Vector2<float> pos_;
	float radius_;

	unsigned int color_;

	Vector2<float>velocity_;
	Vector2<float>accleleration_;

	bool isShot_;

	float length_;

	Vector2<float> bullet2pDis_;

	//方向を変えたりいろいろ
	float theta_;

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

	/*アクセッサ*/

	Vector2<float>GetPos() { return pos_; }

	void SetIsShot(bool flag) { isShot_ = flag; }
	bool GetIsShot() { return isShot_; }

	void SetColor(unsigned int color) { color_ = color; }
	unsigned int GetColor() { return color_; }

};

