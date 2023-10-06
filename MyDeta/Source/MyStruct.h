#pragma once

/***********************************
 * 構造体 *
 ***********************************/
template <typename Mold>
struct Vector2 {
	Mold x;
	Mold y;
};

template <typename Mold>
struct Size {
	Mold width;
	Mold height;
	Mold radius;
};

template <typename Mold>
struct Vertex4 {
	Vector2 <Mold>leftTop;
	Vector2 <Mold>rightTop;
	Vector2 <Mold>leftBottom;
	Vector2 <Mold>rightBottom;
};