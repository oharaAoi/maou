#include "Zoom.h"
#include "MyDeta/Source/Easing.h"

Zoom::Zoom() {
	scalar_ = 1.0f;
	maxScalar_ = 0.0f;

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
	//スクロール値がプレイヤーの座標になるようにする(playerの座標がカメラ座標で0,0になる)
	maxScroll_.x = pos.x;
	maxScroll_.y = pos.y;

	maxScalar_ = 3.0f;

	isZoom_ = true;

	time_ = 0.0f;
}

void Zoom::ZoomOutInit() {
	//スクロール値を0,0にする
	maxScroll_.x = 0;
	maxScroll_.y = 0;

	maxScalar_ = 1.0f;

	isZoom_ = true;

	time_ = 0.0f;
}

template <typename T>
//倍率のズーム
void Zoom::ZoomIn(T& value, T zoomValue, float time) {
	value = std::lerp(value, zoomValue, time);
}

//スクロール値のズーム
void Zoom::ZoomIn(Vector2<float>& value, Vector2<float> zoomValue, float time) {
	value.x = std::lerp(value.x, zoomValue.x, time);
	value.y = std::lerp(value.y, zoomValue.y, time);
}

//flagがtrueの時これを呼び出す
void Zoom::Update() {
	time_++;

	t_ = time_ / timeLimit_;

	ZoomIn(scalar_, maxScalar_, EaseInExpo(t_));
	ZoomIn(scroll_, maxScroll_, EaseInExpo(t_));

	if (time_ > timeLimit_) {
		isZoom_ = false;
	}
}