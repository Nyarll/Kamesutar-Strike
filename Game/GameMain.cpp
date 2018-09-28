//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma warning (disable:4244)

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "Vector.h"
#include "Collision.h"
#include "../ScreenShot.h"
#include <math.h>



// 定数の定義 ==============================================================
#define PLAYER_SIZE (32)

#define BLOCK_SIZE (32)
#define BLOCK_NUM (3)

#define JUMP_ACCELERATOR (2.0)

#define MAX_VEL (4.0)


// 構造体の定義 ============================================================
Vector2D mouse;
Vector2D circle_pos;

Vector2D box_pos;
float box_angle;

char key[256];
char key_old[256];

// グローバル変数の定義 ====================================================




// プロトタイプ宣言 ========================================================

void InitializeGame(void);  // ゲームの初期化処理
void UpdateGame(void);      // ゲームの更新処理
void RenderGame(void);      // ゲームの描画処理
void FinalizeGame(void);    // ゲームの終了処理

void DrawBoxQuad(Vector2D pos, int siz_x, int siz_y, double rad, UINT color, int fill);


// 関数の定義 ==============================================================

// ゲームの初期化処理
void InitializeGame(void)
{
	circle_pos = Vector2D_Create(100, 0);
	box_pos = Vector2D_Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	box_angle = 0;
}

// ゲームの更新処理
void UpdateGame(void)
{
	static double  deg = 0;
	static const float rad_1 = DEG_TO_RAD(1);
	int x, y;
	GetMousePoint(&x, &y);
	GetHitKeyStateAll(key);
	mouse.x = (float)x;	mouse.y = (float)y;

	circle_pos = Vect2Rota(&circle_pos, rad_1);

	box_angle += rad_1;
}

// ゲームの描画処理
void RenderGame(void)
{
	UINT color = 0xffff0000;
	UINT b_color = 0xffff00ff;
	Vector2D cpos = Vect2Add(&mouse, &circle_pos);

	Vector2D m_p = Vect2Sub(&cpos, &box_pos);
	Vector2D temp = Vect2Add(&box_pos, &Vect2Rota(&m_p, -box_angle));

	static char name[256] = {0};

	if (BoxCollision(temp.x, temp.y, 3, 3, box_pos.x, box_pos.y, 120, 120))
	{
		b_color = 0xff0000ff;
	}

	DrawBoxQuad(box_pos, 120, 120, box_angle, b_color, TRUE);

	DrawLine(mouse.x, mouse.y, mouse.x + circle_pos.x, mouse.y + circle_pos.y, color);
	DrawCircle(cpos.x,cpos.y, 3, color);

	if (BoxCollision(temp.x, temp.y, 3, 3, box_pos.x, box_pos.y, 120, 120))
	{
		SetFontSize(40);
		DrawFormatString(SCREEN_CENTER_X - 40, SCREEN_CENTER_Y - 20, COLOR_WHITE, "HIT !");
	}

	static int change_flag = FALSE;
	if ((key[KEY_INPUT_P] == 1) && (key_old[KEY_INPUT_P] != 1))
	{
		SaveScreenShotToPng(0, 0, SCREEN_RIGHT, SCREEN_BOTTOM, name, &change_flag);
	}
	DrawSaveScreenShotLog(name, &change_flag);

	GetHitKeyStateAll(key_old);
}

// ゲームの終了処理
void FinalizeGame(void)
{

}


// 以下オリジナル関数 --------------------------------------------------
void DrawBoxQuad(Vector2D pos,int siz_x, int siz_y, double rad, UINT color, int fill)
{
	Vector2D p1 = Vect2Add(&pos, &Vect2Rota(&Vector2D_Create(-siz_x / 2, -siz_y / 2), rad));
	Vector2D p2 = Vect2Add(&pos, &Vect2Rota(&Vector2D_Create(+siz_x / 2, -siz_y / 2), rad));
	Vector2D p3 = Vect2Add(&pos, &Vect2Rota(&Vector2D_Create(+siz_x / 2, +siz_y / 2), rad));
	Vector2D p4 = Vect2Add(&pos, &Vect2Rota(&Vector2D_Create(-siz_x / 2, +siz_y / 2), rad));

	DrawQuadrangle(
		p1.x, p1.y,
		p2.x, p2.y,
		p3.x, p3.y,
		p4.x, p4.y,
		color, fill);
}