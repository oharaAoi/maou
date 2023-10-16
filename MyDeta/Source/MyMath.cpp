#include "MyMath.h"

/***********************************
* 関数 *
***********************************/
/* ---------------------------------
 Default Function
---------------------------------- */

/* --- Rand --- */
unsigned seed = static_cast<unsigned>(std::time(nullptr));
std::mt19937 gen(seed); // Mersenne Twister 乱数生成器をシード値で初期化


void ValueRand(float* num, float* theta, int bossRadius, int stageRadius) {
	//最小値,最大値(ボスの半径,stageの半径)
	//エネミーの座標をステージの半径内に決める
	std::uniform_int_distribution<int> enemyPosRand(bossRadius, stageRadius);
	std::uniform_real_distribution<float> thetaRand(0, 2.0f * float(M_PI));

	for (int i = 0; i < 5; i++) {
		num[i] = static_cast<float>(enemyPosRand(gen));
		theta[i] = thetaRand(gen);
	}
}

int TypeRand(int min, int max) {
	std::uniform_int_distribution<int> typeRand(min, max);

	return typeRand(gen);
}

/* ---------------------------------
 Math Function
---------------------------------- */
/* --- Length --- */
float CheckLength(const Vector2<float>& standerd, const Vector2<float>& target) {
	return sqrtf(powf(target.x - standerd.x, 2) + powf(target.y - standerd.y, 2));
}

/* --- Normalize --- */
Vector2 <float>ConversionNormalizeVector(const Vector2 <float>& vectorA, const Vector2 <float>& vectorB) {
	Vector2 <float>result;
	float length = CheckLength(vectorA, vectorB);

	result = {
		vectorB.x - vectorA.x, // x
		vectorB.y - vectorA.y, // y
	};

	if (length != 0.0f) {
		result.x /= length;
		result.y /= length;
	}

	return result;
}

/* --- calcVector --- */
Vector2<float> CalcVector(Vector2<float> obj, Vector2<float> other) {
	Vector2<float> result{};
	result.x = obj.x - other.x;
	result.y = obj.y - other.y;

	return result;
}

/* --- DotProduct --- */
float DotProduct(Vector2<float> v1, Vector2<float> v2) {
	float dot = v1.x * v2.x + v1.y * v2.y;

	return dot;
}

/* --- Clamp --- */
float Clamp(float t, float start, float end) {
	if (t < start) {
		t = start;
	} else if (t > end) {
		t = end;
	}

	return t;
}

/* ==================================
 collision Function
================================== */
bool CheckCollisionCircles(const Vector2 <float>& centerA, float radiusA, const Vector2 <float>& centerB, float radiusB) {
	// Cricle: centerA, radiusA
	// Circle: centerB, radiusB

	float distance = CheckLength(centerA, centerB);

	if (distance >= radiusA + radiusB) return true;
	else return false;

}