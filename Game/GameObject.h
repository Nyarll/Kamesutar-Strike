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
	Flag flag;				// �g�p����Ă��邩�ǂ���
	int state;				// ���

	Sprite sprite;			// �e�N�X�`��

	Vector2D pos;			// ���S
	Vector2D vel;			// ���x�̌���
	Vector2D speed;			// ���x�̑傫��

	Color color;			// �F
	float r_vel;			// ��]���x
	float rota;				// ��]
	float scale;			// �{��
	float m;				// ����

	Vector2D hitsize;		// �����蔻��p / ��`
	float r;				// �����蔻��p / �~�`

	int cnt;				// �J�E���g�p

} GameObject2D;

typedef GameObject2D Object2D;

// ��]�ł��� DrawBox
void DrawBoxQuad(Vector2D pos, int siz_x, int siz_y, double rad, UINT color, int fill);

// ���
void DrawArrow(Vector2D p1, Vector2D p2, UINT color);

// <�v���g�^�C�v�錾 / Sprite>

// �X�v���C�g�̍쐬
Sprite Sprite_Create(HGRP* graphics_handle, Vector2D pos, Vector2D size);

// �X�v���C�g�̍쐬 / �e�N�X�`������
Sprite Sprite_CreateTextureNone(Vector2D pos, Vector2D size);

// �X�v���C�g�̕`��
void Sprite_DrawRotaSprite(Sprite* sprite);

// <�v���g�^�C�v�錾 / 2D Game Object>

// 2D �p GameObject �̍쐬
Object2D Object2D_Create(void);

// 2D GameObject �̃t���O���m�F����
Flag Object2D_GetFlag(Object2D* obj);

// 2D GameObject �� Pos ���W�X�V
void Object2D_UpdatePos(Object2D* obj);

// 2D GameObject �̕`��
void Object2D_RenderSprite(Object2D* obj);


// <�v���g�^�C�v�錾 / Color>

// Color �f�[�^�̍쐬
Color Color_Create(int red, int green, int blue);