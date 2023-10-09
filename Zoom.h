#pragma once
#include <cmath>

// MySource //
#include "MyDeta/Source/MyStruct.h"

class Zoom
{
private:

	float scalar_;
	float maxScalar_;

	float time_;
	float timeLimit_;
	float t_;

	Vector2<float> scroll_;
	Vector2<float> maxScroll_;

	bool isZoom_;

public:

	Zoom();

	void ZoomInInit(Vector2<float> pos);

	void ZoomOutInit();

	template <typename T>
	void ZoomIn(T& value, T zoomValue, float time);

	void ZoomIn(Vector2<float>& value, Vector2<float> zoomValue, float time);

	void Update();

	//アクセッサ
	Vector2<float> GetScroll() { return scroll_; }
	void SetScroll(Vector2<float> value) { scroll_ = value; }

	float GetScalar() { return scalar_; }

	bool GetIsZoom() { return isZoom_; }
	void SetIsZoom(bool flag) { isZoom_ = flag; }
};

