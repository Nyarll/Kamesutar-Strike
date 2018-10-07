#pragma once

#include "Vector.h"

// <Flag>
typedef short Flag;

// <Sprite>
typedef struct
{
	HGRP texture;
	Vector2D pos;
	Vector2D size;
	float rota;
	float scale;
} Sprite;

// <Color>
typedef struct
{
	int r, g, b;
} Color;



// <Game Object>
typedef struct
{
	Flag flag;				// 使用されているかどうか
	int state;				// 状態

	Sprite sprite;			// テクスチャ

	Vector2D pos;			// 中心
	Vector2D vel;			// 速度の向き
	Vector2D speed;			// 速度の大きさ

	Color color;			// 色
	float r_vel;			// 回転速度
	float rota;				// 回転
	float scale;			// 倍率
	float m;				// 質量

	Vector2D hitsize;		// 当たり判定用 / 矩形
	float r;				// 当たり判定用 / 円形

	int cnt;				// カウント用

} GameObject2D;

typedef GameObject2D Object2D;

// 回転できる DrawBox
void DrawBoxQuad(Vector2D pos, int siz_x, int siz_y, double rad, UINT color, int fill);

// 矢印
void DrawArrow(Vector2D p1, Vector2D p2, UINT color);

// <プロトタイプ宣言 / Sprite>

// スプライトの作成
Sprite Sprite_Create(HGRP* graphics_handle, Vector2D pos, Vector2D size);

// スプライトの作成 / テクスチャ無し
Sprite Sprite_CreateTextureNone(Vector2D pos, Vector2D size);

// スプライトの描画
void Sprite_DrawRotaSprite(Sprite* sprite);

// <プロトタイプ宣言 / 2D Game Object>

// 2D 用 GameObject の作成
Object2D Object2D_Create(void);

// 2D GameObject のフラグを確認する
Flag Object2D_GetFlag(Object2D* obj);

// 2D GameObject の Pos 座標更新
void Object2D_UpdatePos(Object2D* obj);

// 2D GameObject の描画
void Object2D_RenderSprite(Object2D* obj);


// <プロトタイプ宣言 / Color>

// Color データの作成
Color Color_Create(int red, int green, int blue);