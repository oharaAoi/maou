#pragma once
#include <cmath>

// MySource //
#include "MyDeta/Source/MyStruct.h"

class Zoom
{
private:

	//倍率
	float scalar_;
	float maxScalar_;

	//フレーム
	float time_;
	float timeLimit_;
	float t_;

	//スクロール値
	Vector2<float> scroll_;
	Vector2<float> maxScroll_;

	//フラグ
	bool isZoom_;

public:

	Zoom();

	void ZoomInInit(Vector2<float> pos);

	void ZoomOutInit();

	template <typename T>
	void ZoomEase(T& value, T zoomValue, float time);

	void ZoomEase(Vector2<float>& value, Vector2<float> zoomValue, float time);

	void ZoomIn();

	void Update(Vector2<float> pos);

	//アクセッサ
	Vector2<float> GetScroll() { return scroll_; }
	void SetScroll(Vector2<float> value) { scroll_ = value; }

	float GetScalar() { return scalar_; }

	bool GetIsZoom() { return isZoom_; }
	void SetIsZoom(bool flag) { isZoom_ = flag; }
};

