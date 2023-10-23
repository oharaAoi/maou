#include "Timer.h"

Timer::Timer() {
	Init();

	font_ = Novice::LoadTexture("./images/Resource/Font/numberFont.png");
	fontSize_ = { 210.0f / 10.0f, 36.0f };
}

Timer::~Timer() {
}

void Timer::Init() {
	timer_ = 0.0f;

	
}

void Timer::Update() {
	timer_++;
}

void Timer::Draw() {
	DrawWindow(
		{100.0f, 50.0f}, {140.0f, 50.0f,},
		0xFAFAFAFF
	);

	DrawTimer({ 65.0f, 35.0f }, fontSize_, timer_, 0xFAFAFAFF);
}

void Timer::DrawTimer(Vector2f pos, Sizef size, float time, unsigned int color) {
	int timeArr[3] = { 0 };
	int second = static_cast<int>(time) / 60;

	if (second > 999) {
		second = 999;
	}

	for (int di = 0; di < 3; di++) {
		timeArr[di] = second / static_cast<int>((std::pow(10.0f, 2.0f) / std::pow(10.0f, static_cast<int>(di))));
		second %= static_cast<int>((std::pow(10.0f, 2.0f) / std::pow(10.0f, static_cast<int>(di))));
	}

	for (int di = 0; di < 3; di++) {
		Novice::DrawSpriteRect(
			static_cast<int>(pos.x + (di * size.width)), static_cast<int>(pos.y),
			static_cast<int>(fontSize_.width * timeArr[di]), 0,
			static_cast<int>(fontSize_.width), static_cast<int>(fontSize_.height),
			font_,
			size.width / (fontSize_.width * 10), size.height / fontSize_.height,
			0.0f,
			color
		);
	}
}
