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

int Rand(int min, int max) {
	std::uniform_int_distribution<int> typeRand(min, max);

	return typeRand(gen);
}

/* --- blinking(点滅) --- */
void Blinking(unsigned int& color) {
	if ((color & 0x000000ff) == 0x000000ff) {
		color -= 0x000000ff;
	} else if ((color & 0x00000000) == 0x000000) {
		color += 0x000000ff;
	}
}

float Lerp(float t, float start, float end) {
	if (t < 0.0f) {
		t = 0.0f;

	} else if (t > 1.0f) {
		t = 1.0f;
	}

	return (1.0f - t) * start + t * end;
}

float DivideParameter(float t, int subdivitionNum, int i) {
	return (t - (static_cast<float>(i) / (subdivitionNum + 1))) * subdivitionNum;
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


/* ---------------------------------
 DrawFunction
---------------------------------- */
void DrawRhombus(Vector2f center, float radius, float length, unsigned int color, int graphHandle) {
	/// --- 更新処理 --- ///

	/// --- 描画処理 --- ///
	// leftTop
	Novice::DrawQuad(
		static_cast<int>(center.x), static_cast<int>(center.y - radius),          // p1
		static_cast<int>(center.x), static_cast<int>(center.y - radius - length), // p2
		static_cast<int>(center.x - radius), static_cast<int>(center.y),          // p3
		static_cast<int>(center.x - radius - length), static_cast<int>(center.y), // p4
		0, 0,
		1, 1,
		graphHandle,
		color
	);

	// leftBottom
	Novice::DrawQuad(
		static_cast<int>(center.x - radius), static_cast<int>(center.y),          // p3
		static_cast<int>(center.x - radius - length), static_cast<int>(center.y), // p4
		static_cast<int>(center.x), static_cast<int>(center.y + radius),          // p5
		static_cast<int>(center.x), static_cast<int>(center.y + radius + length), // p6
		0, 0,
		1, 1,
		graphHandle,
		color
	);

	// rightBottom
	Novice::DrawQuad(
		static_cast<int>(center.x), static_cast<int>(center.y + radius),          // p5
		static_cast<int>(center.x), static_cast<int>(center.y + radius + length), // p6
		static_cast<int>(center.x + radius), static_cast<int>(center.y),          // p7
		static_cast<int>(center.x + radius + length), static_cast<int>(center.y), // p8
		0, 0,
		1, 1,
		graphHandle,
		color
	);

	// rightTop
	Novice::DrawQuad(
		static_cast<int>(center.x + radius), static_cast<int>(center.y),          // p7
		static_cast<int>(center.x + radius + length), static_cast<int>(center.y), // p8
		static_cast<int>(center.x), static_cast<int>(center.y - radius),          // p1
		static_cast<int>(center.x), static_cast<int>(center.y - radius - length), // p2
		0, 0,
		1, 1,
		graphHandle,
		color
	);
}

void DrawRhombusAnimation(float t, Vector2f center, float radius, float length, unsigned int color, int graphHandle) {
	const int pointNum = 10;
	Vector2f point[pointNum] = { 0.0f };

	point[0] = { center.x, center.y - radius };
	point[1] = { center.x, center.y - radius - length };

	const int rangeNum = 4;
	float range[rangeNum] = { 0.0f };

	for (int i = 0; i < rangeNum; i++) {
		range[i] = (t * 4) - i;
	}

	/// --- 更新処理 --- ///
	for (int i = 0; i < rangeNum; i++) {
		if (range[i] >= 1.0f) {
			range[i] = 1.0f;
		}
	}

	if (range[0] >= 0.0f) {
		point[2] = { (1.0f - range[0]) * point[0].x + range[0] * (center.x - radius), (1.0f - range[0]) * point[0].y + range[0] * (center.y) }; // p3
		point[3] = { (1.0f - range[0]) * point[1].x + range[0] * (center.x - radius - length), (1.0f - range[0]) * point[1].y + range[0] * (center.y) }; // p4
	}

	if (range[1] >= 0.0f) {
		point[4] = { (1.0f - range[1]) * point[2].x + range[1] * (center.x), (1.0f - range[1]) * point[2].y + range[1] * (center.y + radius) }; // p5
		point[5] = { (1.0f - range[1]) * point[3].x + range[1] * (center.x), (1.0f - range[1]) * point[3].y + range[1] * (center.y + radius + length) }; // p6
	}

	if (range[2] >= 0.0f) {
		point[6] = { (1.0f - range[2]) * point[4].x + range[2] * (center.x + radius), (1.0f - range[2]) * point[4].y + range[2] * (center.y) }; // p7
		point[7] = { (1.0f - range[2]) * point[5].x + range[2] * (center.x + radius + length), (1.0f - range[2]) * point[5].y + range[2] * (center.y) }; // p8
	}

	if (range[3] >= 0.0f) {
		point[8] = { (1.0f - range[3]) * point[6].x + range[3] * (center.x), (1.0f - range[3]) * point[6].y + range[3] * (center.y - radius) }; // p1
		point[9] = { (1.0f - range[3]) * point[7].x + range[3] * (center.x), (1.0f - range[3]) * point[7].y + range[3] * (center.y - radius - length) }; // p2
	}

	/// --- 描画処理 --- ///
	if (range[0] >= 0.0f) {
		Novice::DrawQuad(
			static_cast<int>(point[0].x), static_cast<int>(point[0].y),
			static_cast<int>(point[1].x), static_cast<int>(point[1].y),
			static_cast<int>(point[2].x), static_cast<int>(point[2].y),
			static_cast<int>(point[3].x), static_cast<int>(point[3].y),
			0, 0,
			1, 1,
			graphHandle,
			color
		);
	}

	if (range[1] >= 0.0f) {
		Novice::DrawQuad(
			static_cast<int>(point[2].x), static_cast<int>(point[2].y),
			static_cast<int>(point[3].x), static_cast<int>(point[3].y),
			static_cast<int>(point[4].x), static_cast<int>(point[4].y),
			static_cast<int>(point[5].x), static_cast<int>(point[5].y),
			0, 0,
			1, 1,
			graphHandle,
			color
		);
	}

	if (range[2] >= 0.0f) {
		Novice::DrawQuad(
			static_cast<int>(point[4].x), static_cast<int>(point[4].y),
			static_cast<int>(point[5].x), static_cast<int>(point[5].y),
			static_cast<int>(point[6].x), static_cast<int>(point[6].y),
			static_cast<int>(point[7].x), static_cast<int>(point[7].y),
			0, 0,
			1, 1,
			graphHandle,
			color
		);
	}

	if (range[3] >= 0.0f) {
		Novice::DrawQuad(
			static_cast<int>(point[6].x), static_cast<int>(point[6].y),
			static_cast<int>(point[7].x), static_cast<int>(point[7].y),
			static_cast<int>(point[8].x), static_cast<int>(point[8].y),
			static_cast<int>(point[9].x), static_cast<int>(point[9].y),
			0, 0,
			1, 1,
			graphHandle,
			color
		);
	}
}