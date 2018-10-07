#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define DEG_TO_RAD(DEG)	((DEG) * (M_PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / M_PI))

// �萔�̒�` ==============================================================

// <System> ----------------------------------------------------------
#define GAME_TITLE "KAMESUTAR STRIKE !!"        // �Q�[���^�C�g��


// <Window> --------------------------------------------------------------
#define SCREEN_WIDTH    (1024)                  // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (512 + 256)                  // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)

// <Game Screen>
#define GAME_SCREEN_WIDTH	(512)
#define GAME_SCREEN_HEIGHT	(SCREEN_HEIGHT)

#define GAME_SCREEN_TOP		(0)
#define GAME_SCREEN_BOTTOM	(SCREEN_BOTTOM)
#define GAME_SCREEN_LEFT	(0)
#define GAME_SCREEN_RIGHT	(SCREEN_WIDTH)

#define GAME_SCREEN_CENTER_X	(GAME_SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define GAME_SCREEN_CENTER_Y	(GAME_SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)

// <Game Object>
#define NOT_FOUND_TEXTURE	(-1)
#define TEXTURE_NONE		(-2)