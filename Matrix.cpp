#include "Matrix.h"

/*回転行列*/
Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 result{};
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);
	result.m[2][2] = 1;

	return result;
}

/*平行移動行列*/
Matrix3x3 MakeTranslateMatrix(Vector2f translate) {
	Matrix3x3 result{};
	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1;

	return result;
}

//3x3の行列の積
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result{};
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			for (int i = 0; i < 3; i++) {
				result.m[row][col] += matrix1.m[row][i] * matrix2.m[i][col];
			}
		}
	}

	return result;
}

//2次元ベクトルを同次座標系として変換する
Vector2f Transform(Vector2f vector, Matrix3x3 matrix) {
	Vector2f result;//w=1がデカルト座標系であるので(x,y1)のベクトルとしてmatrixとの積をとる
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;

	return result;
}