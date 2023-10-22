#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "MyDeta/Source/MyStruct.h"
#include <assert.h>

struct Matrix3x3 {
	float m[3][3];
};

/*関数*/
/*回転行列*/
Matrix3x3 MakeRotateMatrix(float theta);

/*平行移動行列*/
Matrix3x3 MakeTranslateMatrix(Vector2f translate);

//3x3の行列の積
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

Vector2f Transform(Vector2f vector, Matrix3x3 matrix);