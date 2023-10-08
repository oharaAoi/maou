#include "MyMath.h"

/***********************************
* 関数 *
***********************************/
/* ---------------------------------
 Default Function
---------------------------------- */

/* --- Rand --- */
void ValueRand(float* num, float* theta, int bossRadius, int stageRadius) {
	unsigned seed = static_cast<unsigned>(std::time(nullptr));
	std::mt19937 gen(seed); // Mersenne Twister 乱数生成器をシード値で初期化

	//最小値,最大値(ボスの半径,stageの半径)
	//エネミーの座標をステージの半径内に決める
	std::uniform_int_distribution<int> enemyPosRand(bossRadius, stageRadius);
	std::uniform_real_distribution<float> thetaRand(0, 2.0f * float(M_PI));

	for (int i = 0; i < 5; i++) {
		num[i] = static_cast<float>(enemyPosRand(gen));
		theta[i] = thetaRand(gen);
	}
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