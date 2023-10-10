#include "Zoom.h"
#include "MyDeta/Source/Easing.h"
#include <MyDeta/Source/Environment.h>

Zoom::Zoom() {
	
}

//ズームする時に呼び出す初期化(今はこれを最初に呼び出すだけでいい)
void Zoom::ZoomInit() {
	scalar_ = 1.0f;
	maxScalar_ = 1.0f;

	scroll_.x = 0;
	scroll_.y = 0;
	maxScroll_.x = 0;
	maxScroll_.y = 0;

	time_ = 0;
	timeLimit_ = 180.0f;
	t_ = 0;

	isZoom_ = false;
}

void Zoom::ZoomInInit(Vector2<float> pos) {
	scroll_.x = (pos.x - (kWindowWidth / 2.0f));
	scroll_.y = (pos.y - (kWindowHeight / 2.0f));

	isZoom_ = true;

	scalar_ = 3.0f;
	maxScalar_ = 3.0f;

	time_ = 0.0f;
}

void Zoom::ZoomOutInit() {
	//スクロール値を0,0にする
	maxScroll_.x = 0;
	maxScroll_.y = 0;

	isZoom_ = false;

	scalar_ = 1.0f;
	maxScalar_ = 1.0f;

	time_ = 0.0f;
}

//template <typename T>
////倍率のズーム
//void Zoom::ZoomEase(T& value, T zoomValue, float time) {
//	value = std::lerp(value, zoomValue, time);
//}
//
////スクロール値のズーム
//void Zoom::ZoomEase(Vector2<float>& value, Vector2<float> zoomValue, float time) {
//	value.x = std::lerp(value.x, zoomValue.x, time);
//	value.y = std::lerp(value.y, zoomValue.y, time);
//}
//
////flagがtrueの時これを呼び出す(大きくしていく処理)
//void Zoom::ZoomIn() {
//	//time_++;
//
//	t_ = time_ / timeLimit_;
//
//	ZoomEase(scalar_, maxScalar_, EaseInExpo(t_));
//	ZoomEase(scroll_, maxScroll_, EaseInExpo(t_));
//
//	if (time_ > timeLimit_) {
//		isZoom_ = false;
//	}
//}

//ズーム中はこれをずっと呼び出す
void Zoom::Update(Vector2<float> pos) {
	//ズームイン
	if (isZoom_) {
		if(scalar_ == 1.0f)
		ZoomInInit(pos);

		//ズームアウト
	} else {
		if (scalar_ == 3.0f)
		ZoomOutInit();
	}

	if (scalar_ == 3.0f) {
		scroll_.x = pos.x - (kWindowWidth / 2.0f);
		scroll_.y = pos.y - (kWindowHeight / 2.0f);
	}
}