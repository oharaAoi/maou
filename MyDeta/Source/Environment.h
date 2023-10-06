#pragma once

const char kWindowTitle[] = "回王";

/***********************************
 * グローバル変数 *
 ***********************************/
 // window size //
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

//シーン
enum GameScene {
	TITLE,
	TUTORIAL,
	GAME,
	RESULT
};

GameScene scene = TITLE;