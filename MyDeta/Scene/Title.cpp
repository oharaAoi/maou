#include "Title.h"

Title::Title() {
	Init();

	whiteGH_ = Novice::Novice::LoadTexture("./images/resource/sceneChange/sceneChange.png");
	
	backgroundGH_ = Novice::LoadTexture("./images/resource/stage/background/bgWave1.png");
	titleGH_ = Novice::LoadTexture("./images/resource/title/title.png");

	otLogicGh_ = Novice::LoadTexture("./images/Resource/credit/otLogic.png");
	pokketSoundGh_ = Novice::LoadTexture("./images/Resource/credit/pokettoSound.png");
	soundEffectGh_ = Novice::LoadTexture("./images/Resource/credit/soundEffect.png");
}

Title::~Title() {
}

void Title::Init() {
	frame_ = 0.0f;

	for (int ai = 0; ai < animationNum_; ai++) {
		animationFrame_[ai] = 0.0f;
	}
}

void Title::Update() {

	if (frame_ < animationNum_ * 60.0f) { frame_++; }
	

	for (int ai = 0; ai < animationNum_; ai++) {
		animationFrame_[ai] = frame_ - (60.0f * ai);
	}

}

void Title::Draw() {
	// title
	// pos = 270, 280; size = 730, 150;

	Novice::DrawSprite(
		0, 0,
		whiteGH_,
		1.0f, 1.0f,
		0.0f,
		0xFFFFFFFF
	);

	// animation 0x000000FF
	// line
	Novice::DrawLine(
		0,
		280,
		static_cast<int>(Lerp(EaseInExpo(animationFrame_[0] / 60.0f), 0.0f, kWindowWidth)),
		280,
		0x000000FF
	);

	Novice::DrawLine(
		kWindowWidth,
		280 + 150,
		static_cast<int>(Lerp(EaseInExpo(animationFrame_[0] / 60.0f), kWindowWidth, 0.0f)),
		280 + 150,
		0x000000FF
	);

	Novice::DrawLine(
		270,
		0,
		270,
		static_cast<int>(Lerp(EaseOutExpo(animationFrame_[0] / 60.0f), 0.0f, kWindowHeight)),
		0x000000FF
	);

	Novice::DrawLine(
		270 + 730,
		kWindowHeight,
		270 + 730,
		static_cast<int>(Lerp(EaseOutExpo(animationFrame_[0] / 60.0f), kWindowHeight, 0.0f)),
		0x000000FF
	);

	// box
	Novice::DrawBox(
		270, 280,
		static_cast<int>(Lerp(EaseOutExpo(animationFrame_[1] / 60.0f), 0.0f, 730.0f)),
		150,
		0.0f,
		0x000000FF,
		kFillModeSolid
	);

	// allBox
	Novice::DrawBox(
		1280, 0,
		static_cast<int>(Lerp(EaseOutQuint(animationFrame_[2] / 40.0f), 0.0f, -kWindowWidth)), 720,
		0.0f,
		0x000000FF,
		kFillModeSolid
	);

	Novice::SetBlendMode(kBlendModeScreen);

	Novice::DrawSprite(
		0, 0,
		backgroundGH_,
		1.0f, 1.0f,
		0.0f,
		0xFFFFFFFF
	);

	Novice::SetBlendMode(kBlendModeNormal);

	//titleGH
	Novice::DrawSprite(
		0, 2,
		titleGH_,
		1.0f, 1.0f,
		0.0f,
		ShiftColor(animationFrame_[2] / 60.0f, 0x40404000, 0x40404060)
		/*0x40404070*/
	); // 30

	Novice::DrawSprite(
		0, 0,
		titleGH_,
		1.0f, 1.0f,
		0.0f,
		0xFAFAFAFF
	);

	//soundEffect credit
	Novice::DrawSprite(
		900,
		680,
		soundEffectGh_,
		0.5f,
		0.5f,
		0.0f,
		0xFFFFFFFF
	);

	Novice::DrawSprite(
		1000,
		680,
		otLogicGh_,
		0.5f,
		0.5f,
		0.0f,
		0xFFFFFFFF
	);

	Novice::DrawSprite(
		1120,
		680,
		pokketSoundGh_,
		0.5f,
		0.5f,
		0.0f,
		0xFFFFFFFF
	);
}
