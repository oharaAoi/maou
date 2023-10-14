#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
/*==================================*/
#include <random>
/*==================================*/

// MySource //
#include "MyDeta/Source/MyStruct.h"

/***********************************
* 関数 *
***********************************/
/* ---------------------------------
 Default Function
---------------------------------- */
/* --- Random --- */
void ValueRand(float num, float theta, int bossRadius, int stageRadius);

/* ---------------------------------
 Math Function
---------------------------------- */
/* --- Length --- */
float CheckLength(const Vector2<float>& standerd, const Vector2<float>& target);

/* --- Normalize --- */
Vector2 <float>ConversionNormalizeVector(const Vector2 <float>& vectorA, const Vector2 <float>& vectorB);

/* --- calcVector --- */
Vector2<float> CalcVector(Vector2<float> obj, Vector2<float> other);

/* --- DotProduct --- */
float DotProduct(Vector2<float> v1, Vector2<float> v2);

/* --- Clamp --- */
float Clamp(float t, float start, float end);

/* ==================================
 collision Function
================================== */
/// <summary>
/// <para> 円と円の当たり判定 </para>
/// <para> CircleA -> CircleB </para>
/// </summary>
/// <param name="centerA: CircleA"></param>
/// <param name="radiusA: CircleA"></param>
/// <param name="centerB: CircleB"></param>
/// <param name="radiusB: CircleB"></param>
/// <returns></returns>
bool CheckCollisionCircles(const Vector2 <float>& centerA, float radiusA, const Vector2 <float>& centerB, float radiusB);

