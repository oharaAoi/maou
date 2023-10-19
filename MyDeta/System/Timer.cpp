#include "Timer.h"

Timer::Timer() {
	Init();

	font_;
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

	DrawTimer(timer_);
}

void Timer::DrawTimer(float time) {
	int timeArr[3] = { 0 };
	int second = static_cast<int>(time) / 60;

	if (second > 999) {
		second = 999;
	}

	for (int di = 0; di < 3; di++) {
		timeArr[di] = second / static_cast<int>((std::pow(10.0f, 2.0f) / std::pow(10.0f, static_cast<int>(di))));
		second %= static_cast<int>((std::pow(10.0f, 2.0f) / std::pow(10.0f, static_cast<int>(di))));
	}

	
}
