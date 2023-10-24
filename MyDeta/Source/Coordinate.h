#pragma once
#include "MyDeta/Source/MyStruct.h"
#include <MyDeta/Source/Environment.h>
#include "MyDeta/Source/MyMath.h"
#include "MyDeta/Source/Easing.h"

class Coordinate final
{
private:
	
	Coordinate();
	~Coordinate();

public:
	static const Vector2 <float> origine_;

	//シングルトンで使う
	//コピーコンストラクタの禁止
	Coordinate(const Coordinate& obj) = delete;
	//Coordinate operator + (const Coordinate& obj)の範囲を削除している
	Coordinate operator + (const Coordinate& obj) = delete;

	static Coordinate* GetInstance();

	void Init();

	void Update(float t, Vector2f startPos, Vector2f endPos);

	//この関数を持ってきてworld1座標系からscereen座標系に変換
	const Vector2<float> GetOrigine()const { return origine_; }

};

