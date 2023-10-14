#pragma once
#include <Novice.h>
// MySource //
#include "MyDeta/Source/MyStruct.h"

class BossBullet
{
private:

	//基本のもの
	Vector2<float> pos_;
	float radius_;

	Vector2<float>velocity_;
	Vector2<float>accleleration_;

	bool isShot_;

	//方向を変えたりいろいろ
	float theta_;

	struct Base {
		
	};

public:

	BossBullet();
	~BossBullet();

	void Init();

	void Update();

	void Draw();

	/*アクセッサ*/

	Vector2<float>GetPos() { return pos_; }
};

