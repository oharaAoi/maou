﻿#pragma once
#include "MyDeta/Source/MyStruct.h"
#include <MyDeta/Source/Environment.h>

class Coordinate
{
private:

	Vector2 <float> origine_;
	Coordinate();

public:

	//シングルトンで使う
	//コピーコンストラクタの禁止
	Coordinate(const Coordinate& obj) = delete;
	//Coordinate operator + (const Coordinate& obj)の範囲を削除している
	Coordinate operator + (const Coordinate& obj) = delete;

	static Coordinate* GetInstance();

	void Init();

	//この関数を持ってきてworld1座標系からscereen座標系に変換
	Vector2 <float>GetOrigine() { return origine_; }

};

