﻿#pragma once
#include <Novice.h>
/*==================================*/
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

int Rand(int min, int max);

/* --- blinking(点滅) --- */
void Blinking(unsigned int& color);

float Lerp(float t, float start, float end);

float DivideParameter(float t, int subdivitionNum, int i);

unsigned int ShiftColor(float t, unsigned int beforeColor, unsigned int afterColor);

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

/* --- ClampLerp --- */
float ClampLerp(float t, float start, float end);

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

/* ---------------------------------
 DrawFunction
---------------------------------- */
void DrawRhombus(Vector2f center, float radius, float length, unsigned int color, int graphHandle);

void DrawRhombusAnimation(float t, Vector2f center, float radius, float length, unsigned int color, int graphHandle);

void DrawCircleAnimation(float t, const Vector2f& center, float radius, float width, int textureHandle, uint32_t color);

void DrawWindow(const Vector2f& center, const Sizef& size, uint32_t color);

void DrawSprite(const Vector2f& center, const Sizef& size, int textureHandle, const Sizef& textureSize, uint32_t color);

void DrawJapanese(const Vector2 <int>& pos, const Sizef& size, int wordNum, short int* word, uint32_t color, int font);

/* ---------------------------------
 AudioFunction
---------------------------------- */

void PlayAudio(int& voiceHandle, int soundHandle, float soundVolume, bool isLoop);

void PlaySe(int& voiceHandle, int soundHandle, float soundVolume);
