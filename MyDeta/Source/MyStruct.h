#pragma once

/***********************************
 * 構造体 *
 ***********************************/
template <typename Mold>
struct Vector2 {
	Mold x;
	Mold y;

	// operator overload //
	// Add
	Vector2 operator+(const Vector2& other) const {
		return { x + other.x, y + other.y };
	}
	void operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
	}

	// Subtract
	Vector2 operator-(const Vector2& other) const {
		return { x - other.x, y - other.y };
	}
	void operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
	}

	// Multiply
	Vector2 operator*(const Vector2& other) const {
		return { x * other.x, y * other.y };
	}
	void operator*=(const Vector2& other) {
		x *= other.x;
		y *= other.y;
	}
};

using Vector2f = Vector2 <float>;

template <typename Mold>
struct Size {
	Mold width;
	Mold height;
	Mold radius;
};

using Sizef = Size <float>;

template <typename Mold>
struct Vertex4 {
	Vector2 <Mold>leftTop;
	Vector2 <Mold>rightTop;
	Vector2 <Mold>leftBottom;
	Vector2 <Mold>rightBottom;
};

using Vertex4f = Vertex4 <float>;

struct Vector4 final {
	float x, y, z, w;
};