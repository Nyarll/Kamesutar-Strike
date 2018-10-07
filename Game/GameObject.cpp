#include "GameObject.h"

// 回転可能な DrawBox
void DrawBoxQuad(Vector2D pos, int siz_x, int siz_y, double rad, UINT color, int fill)
{
	Vector2D p1;
	p1 = Vect2Add(&pos, &Vect2Rota(&Vect2Create(-siz_x / 2, -siz_y / 2), rad));
	Vector2D p2;
	p2 = Vect2Add(&pos, &Vect2Rota(&Vect2Create(+siz_x / 2, -siz_y / 2), rad));
	Vector2D p3;
	p3 = Vect2Add(&pos, &Vect2Rota(&Vect2Create(+siz_x / 2, +siz_y / 2), rad));
	Vector2D p4;
	p4 = Vect2Add(&pos, &Vect2Rota(&Vect2Create(-siz_x / 2, +siz_y / 2), rad));

	DrawQuadrangle(
		p1.x, p1.y,
		p2.x, p2.y,
		p3.x, p3.y,
		p4.x, p4.y,
		color, fill);
}

// 矢印
void DrawArrow(Vector2D p1, Vector2D p2, UINT color)
{
	float rad = Vect2Angle(&Vect2Sub(&p2, &p1));
	float deg = RAD_TO_DEG(rad);
	Vector2D temp;
	DrawLine(p1.x, p1.y, p2.x, p2.y, color, 2);
	temp = Vect2Add(&p1, &Vect2Rota(&Vect2Create(60, 30), rad));
	DrawLine(p1.x, p1.y, temp.x, temp.y, color, 2);
	temp = Vect2Add(&p1, &Vect2Rota(&Vect2Create(60, -30), rad));
	DrawLine(p1.x, p1.y, temp.x, temp.y, color, 2);

}

// スプライトの作成
Sprite Sprite_Create(HGRP* graphics_handle, Vector2D pos, Vector2D size)
{
	Sprite sprite;
	
	if (*graphics_handle == NOT_FOUND_TEXTURE)
	{
		*graphics_handle = MakeScreen(size.x, size.y);
		SetDrawScreen(*graphics_handle);
		
		DrawBox(0, 0, size.x, size.y, 0xffff00ff, TRUE);
		DrawBox(size.x / 2, 0, size.x, size.y / 2, 0xff000000, TRUE);
		DrawBox(0, size.y / 2, size.x / 2, size.y, 0xff000000, TRUE);

		DrawCircle(size.x / 2, size.y / 2, size.x / 2, 0xffff0000, FALSE,5);

		SetDrawScreen(DX_SCREEN_BACK);
	}
	

	sprite.texture = *graphics_handle;
	sprite.pos = pos;
	sprite.size = size;
	sprite.rota = 0.0;
	sprite.scale = 1.0f;

	return sprite;
}

// スプライトの作成 / テクスチャ無し
Sprite Sprite_CreateTextureNone(Vector2D pos, Vector2D size)
{
	int gh = TEXTURE_NONE;
	return Sprite_Create(&gh, pos, size);
}


// スプライトの描画
void Sprite_DrawRotaSprite(Sprite* sprite)
{
	DrawRotaGraph(sprite->pos.x, sprite->pos.y, sprite->scale, sprite->rota, sprite->texture, TRUE);
}

// 2D 用 GameObject の作成
Object2D Object2D_Create(void)
{
	Object2D obj;

	obj.flag = FALSE;
	obj.state = 0;

	obj.sprite.pos = Vect2Create(0.0f, 0.0f);
	obj.sprite.size = Vect2Create(0.0f, 0.0f);
	obj.sprite.texture = NOT_FOUND_TEXTURE;

	obj.pos = Vect2Create(0.0f, 0.0f);
	obj.vel = Vect2Create(0.0f, 0.0f);
	obj.speed = Vect2Create(0.0f, 0.0f);

	obj.color = Color_Create(0, 0, 0);

	obj.r_vel = 0.0f;
	obj.rota = 0.0f;
	obj.scale = 0.0f;
	obj.m = 0.0f;

	obj.hitsize = Vect2Create(0.0f, 0.0f);
	obj.r = 0.0f;

	obj.cnt = 0;

	return obj;
}

// 2D GameObject のフラグを確認する
Flag Object2D_GetFlag(Object2D* obj)
{
	return obj->flag;
}

// 2D GameObject の Pos 座標更新
void Object2D_UpdatePos(Object2D* obj)
{
	obj->pos = Vect2Add(&obj->pos, &Vect2MulVect(&obj->speed, &obj->vel));
}

// 2D GameObject の描画
void Object2D_RenderSprite(Object2D* obj)
{
	Sprite_DrawRotaSprite(&obj->sprite);
}

// Color データの作成
Color Color_Create(int red, int green, int blue)
{
	Color color;
	color.r = red;
	color.g = green;
	color.b = blue;

	return color;
}
