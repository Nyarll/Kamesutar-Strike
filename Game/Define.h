#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define DEG_TO_RAD(DEG)	((DEG) * (M_PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / M_PI))

// 定数の定義 ==============================================================

// <System> ----------------------------------------------------------
#define GAME_TITLE "KAMESUTAR STRIKE !!"        // ゲームタイトル


// <Window> --------------------------------------------------------------
#define SCREEN_WIDTH    (1024)                  // 画面の幅[pixel]
#define SCREEN_HEIGHT   (512 + 256)                  // 画面の高さ[pixel]

#define SCREEN_TOP      (0)                    // 画面の上端
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // 画面の下端
#define SCREEN_LEFT     (0)                    // 画面の左端
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // 画面の右端

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // 画面の中央(X座標)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // 画面の中央(Y座標)

// <Game Screen>
#define GAME_SCREEN_WIDTH	(512)
#define GAME_SCREEN_HEIGHT	(SCREEN_HEIGHT)

#define GAME_SCREEN_TOP		(0)
#define GAME_SCREEN_BOTTOM	(SCREEN_BOTTOM)
#define GAME_SCREEN_LEFT	(0)
#define GAME_SCREEN_RIGHT	(SCREEN_WIDTH)

#define GAME_SCREEN_CENTER_X	(GAME_SCREEN_WIDTH  / 2)    // 画面の中央(X座標)
#define GAME_SCREEN_CENTER_Y	(GAME_SCREEN_HEIGHT / 2)    // 画面の中央(Y座標)

// <Game Object>
#define NOT_FOUND_TEXTURE	(-1)
#define TEXTURE_NONE		(-2)