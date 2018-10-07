//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma warning (disable:4244)

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameObject.h"
#include "Collision.h"
#include "../ScreenShot.h"
#include <math.h>



// �萔�̒�` ==============================================================
#define PLAYER_SIZE (32)

#define BLOCK_SIZE (32)
#define BLOCK_NUM (3)

#define JUMP_ACCELERATOR (2.0)

#define MAX_VEL (4.0)

#define FRICTION (0.98f)


// Kamesuta's
// �I�u�W�F�N�g�̐�
#define NUM_OBJECTS 30
// �T�E���h�̐�
#define NUM_SOUNDS 8
// �摜�̑傫��
#define IMAGE_SIZE 256


// �\���̂̒�` ============================================================
typedef struct
{
	Vector2D pos;
	Vector2D vel;
	float r;
	float m;
}Circle;

typedef struct
{
	Sprite sprite_front;
	Sprite sprite_back;
	Vector2D pos;
	Vector2D vel;
	Color color;
	float rota;
	float scale;
	float r_vel;
	float m;
	Vector2D hitsize;
} KameObject;

// �O���[�o���ϐ��̒�` ====================================================
Vector2D mouse;
Vector2D circle_pos;

Vector2D box_pos;
float box_angle;

char key[256];
char key_old[256];

Circle c[2];

// Kamesuta's
int g_input_state;

// �I�u�W�F�N�g�̑O�i
HGRP g_texture_front;
// �I�u�W�F�N�g�̔w�i
HGRP g_texture_back;

// �I�u�W�F�N�g
KameObject g_objects[NUM_OBJECTS];

// ���܂ɂȂ�T�E���h
HSND g_sounds[NUM_SOUNDS];
// �K����T�E���h
HSND g_sound_hit;

int mouse_input;
Vector2D mpoint1;
short strike;


// 3
Vector2D pos1, pos2;
Circle locus;
static const float sc_left = (float)(SCREEN_CENTER_X / 2);
static const float sc_right = (float)(sc_left * 3);
static const float sc_top = (float)(SCREEN_CENTER_Y / 2);
static const float sc_bottom = (float)(sc_top * 3);

typedef enum
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	VIEW_LINE_MAX
}ViewLine;

// �v���g�^�C�v�錾 ========================================================

void InitializeGame(void);  // �Q�[���̏���������
void UpdateGame(void);      // �Q�[���̍X�V����
void RenderGame(void);      // �Q�[���̕`�揈��
void FinalizeGame(void);    // �Q�[���̏I������

void Update1(void);
void Render1(void);

void Update2(void);
void Render2(void);

// Kamesuta�n
void InitKame(void);
void UpdateKame(void);
void RenderKame(void);

void UpdateKamesutarStrike(void);
void RenderKamesutarStrike(void);

// �֐��̒�` ==============================================================

void InitKame(void)
{
	// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
	g_texture_front = LoadGraph("Resources\\Textures\\ObjFront.png");
	g_texture_back = LoadGraph("Resources\\Textures\\ObjBack.png");

	// �T�E���h�ǂݍ���
	g_sound_hit = LoadSoundMem("Resources\\Audio\\hit1.ogg");
	for (int i = 0; i < NUM_SOUNDS; i++)
	{
		char str[50];
		sprintf_s(str, "Resources\\Audio\\kick%d.ogg", i + 1);
		g_sounds[i] = LoadSoundMem(str);
	}

	// �I�u�W�F�N�g������
	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		// �|�C���^�ɑ��
		KameObject *obj = &g_objects[i];

		obj->sprite_front = Sprite_Create(&g_texture_front, { 0,0 }, { IMAGE_SIZE, IMAGE_SIZE });
		obj->sprite_back = Sprite_Create(&g_texture_back, { 0,0 }, { IMAGE_SIZE, IMAGE_SIZE });

		obj->pos = { (float)GetRand(SCREEN_WIDTH), (float)GetRand(SCREEN_HEIGHT) };
		obj->vel = { 0,0 };
		obj->color = { GetRand(255), GetRand(255), GetRand(255) };
		obj->r_vel = 0;	// NEW !!
		obj->rota = 0;
		obj->scale = (GetRand(100) / 100.f + .5f)*.25f;
		obj->hitsize = { (IMAGE_SIZE - 20)*obj->scale , (IMAGE_SIZE - 20)*obj->scale };

		if (obj->hitsize.x < 10)
			obj->m = obj->hitsize.x;
		else
			obj->m = obj->hitsize.x / 10;
	}

	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		KameObject *obj = &g_objects[i];
		for (int j = 0; j < NUM_OBJECTS; j++)
		{
			KameObject *obj2 = &g_objects[j];

			if (i != j)
			{
				while (1)
				{
					if (CircleCollision(obj->hitsize.x / 2, obj2->hitsize.x / 2, obj->pos.x, obj2->pos.x, obj->pos.y, obj2->pos.y))
					{
						obj2->pos = { (float)GetRand(SCREEN_WIDTH), (float)GetRand(SCREEN_HEIGHT) };
					}
					else
					{
						break;
					}
				}
			}
		}
	}

	strike = FALSE;
}

void Init3(void)
{
	pos1 = Vect2Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	pos2 = Vect2Create((SCREEN_CENTER_X / 2), (SCREEN_CENTER_X / 2));

	locus.pos = pos1;
	locus.r = Vect2Length(pos2);
}

// �Q�[���̏���������
void InitializeGame(void)
{
	/*circle_pos = Vect2Create(100, 0);
	box_pos = Vect2Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	box_angle = 0;

	c[0].pos = { 60, 60 };	c[1].pos = { SCREEN_RIGHT - 60, SCREEN_BOTTOM - 60 };
	c[0].vel = { 5,1 };		c[1].vel = { -3,-2 };
	c[0].r = 30;			c[1].r = 50;
	c[0].m = 3;				c[1].m = 5;*/

	//InitKame();

	Init3();
}

void Update1(void)
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
void Render1(void)
{
	UINT color = 0xffff0000;
	UINT b_color = 0xffff00ff;
	Vector2D cpos = Vect2Add(&mouse, &circle_pos);


	Vector2D m_p = Vect2Sub(&cpos, &box_pos);
	Vector2D temp = Vect2Add(&box_pos, &Vect2Rota(&m_p, -box_angle));


	static char name[256] = { 0 };

	if (BoxCollision(temp.x, temp.y, 3, 3, box_pos.x, box_pos.y, 120, 120))
	{
		b_color = 0xff0000ff;
	}

	DrawBoxQuad(box_pos, 120, 120, box_angle, b_color, TRUE);

	DrawLine(mouse.x, mouse.y, mouse.x + circle_pos.x, mouse.y + circle_pos.y, color);
	DrawCircle(cpos.x, cpos.y, 3, color);

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

void Update2(void)
{
	// �~�P�Ɖ~�Q���Փ˂����ꍇ�A�݂��� Position �̍ŒZ�������̑��x�x�N�g���ŗ����
	//CalcParticleColliAfterPos(&c[0].pos, &c[1].pos, &c[0].vel, &c[1].vel, c[0].r, c[1].r);
	CircleColliAfterVel(&c[0].pos, &c[1].pos, &c[0].vel, &c[1].vel, c[0].r, c[1].r);

	for (int i = 0; i < 2; i++)
	{
		Vector2D temp = c[i].pos;

		c[i].pos = Vect2Add(&c[i].pos, &c[i].vel);

		if ((c[i].pos.x - c[i].r < SCREEN_LEFT) || (c[i].pos.x + c[i].r > SCREEN_RIGHT))
		{
			c[i].vel.x *= (-1);
			c[i].pos = temp;
		}
		if ((c[i].pos.y - c[i].r < SCREEN_TOP) || (c[i].pos.y + c[i].r > SCREEN_BOTTOM))
		{
			c[i].vel.y *= (-1);
			c[i].pos = temp;
		}
	}
}
void Render2(void)
{
	int i;

	for (i = 0; i < 2; i++)
	{
		DrawCircle((int)c[i].pos.x, (int)c[i].pos.y, (int)c[i].r, COLOR_RED);
	}
}

void UpdateKame(void)
{
	// �}�E�X�̍��W�擾
	int m_x, m_y;
	GetMousePoint(&m_x, &m_y);

	// ���͂��擾
	g_input_state = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �I�u�W�F�N�g�X�V����
	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		// �|�C���^�ɑ��
		KameObject *obj = &g_objects[i];

		// ���W�X�V
		{
			obj->pos.x += obj->vel.x;
			obj->pos.y += obj->vel.y;
		}

		// �����蔻��
		{
			// Kame ���m�̓����蔻��
			{
				for (int j = 0; j < NUM_OBJECTS; j++)
				{
					if (i != j)
					{
						KameObject* obj2 = &g_objects[j];
						float hit1 = obj->hitsize.x / 2;
						float hit2 = obj2->hitsize.x / 2;
						//if (CircleColliAfterVel(&obj->pos, &obj2->pos, &obj->vel, &obj2->vel, hit1, hit2))
						if (CircleColliAfterRotateVel(&obj->pos, &obj2->pos, &obj->vel, &obj2->vel,
							hit1, hit2, &obj->r_vel, &obj2->r_vel, obj->m, obj2->m))
						{
							// ���ʉ���炷
							PlaySoundMem(g_sound_hit, DX_PLAYTYPE_BACK);
							if (GetRand(10) == 0)
								// ���܂ɕʂ̉���������
								PlaySoundMem(g_sounds[GetRand(NUM_SOUNDS - 1)], DX_PLAYTYPE_BACK);
						}
					}
				}
			}

			// �I�u�W�F�N�g�ɑ΂��Ă̕ǂ̈ʒu
			float padding_left = SCREEN_LEFT + obj->hitsize.x / 2;
			float padding_right = SCREEN_RIGHT - obj->hitsize.x / 2;
			float padding_top = SCREEN_TOP + obj->hitsize.y / 2;
			float padding_bottom = SCREEN_BOTTOM - obj->hitsize.y / 2;

			// �͈͂𒴂�����
			if (obj->pos.x < padding_left || padding_right <= obj->pos.x)
			{
				// ���ʉ���炷
				PlaySoundMem(g_sound_hit, DX_PLAYTYPE_BACK);
				if (GetRand(10) == 0)
					// ���܂ɕʂ̉���������
					PlaySoundMem(g_sounds[GetRand(NUM_SOUNDS - 1)], DX_PLAYTYPE_BACK);
				// ���x�𔽑΂ɂ���
				obj->vel.x *= -1;
			}
			if (obj->pos.y < padding_top || padding_bottom <= obj->pos.y)
			{
				// ���ʉ���炷
				PlaySoundMem(g_sound_hit, DX_PLAYTYPE_BACK);
				if (GetRand(10) == 0)
					// ���܂ɕʂ̉���������
					PlaySoundMem(g_sounds[GetRand(NUM_SOUNDS - 1)], DX_PLAYTYPE_BACK);
				// ���x�𔽑΂ɂ���
				obj->vel.y *= -1;
			}
			// �͂ݏo���C��
			obj->pos.x = ClampF(obj->pos.x, padding_left, padding_right);
			obj->pos.y = ClampF(obj->pos.y, padding_top, padding_bottom);
		}

		// �J�[�\���̕���������
		{
			//obj->rota = -atan2f(obj->pos.x - m_x, obj->pos.y - m_y);
		}
		{
			obj->rota += obj->r_vel;
		}
	}
}
void RenderKame(void)
{
	// �w�i�𔒂œh��
	SetDrawBright(255, 255, 255);
	DrawBox(SCREEN_LEFT, SCREEN_TOP, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_WHITE, TRUE);

	// �I�u�W�F�N�g�`�揈��
	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		// �|�C���^�ɑ��
		KameObject *obj = &g_objects[i];

		// �I�u�W�F�N�g�w�i(�R�E��)�̐F���w��
		SetDrawBright(obj->color.r, obj->color.g, obj->color.b);
		// �I�u�W�F�N�g�w�i�`��
		DrawRectRotaGraph(
			(int)obj->pos.x, (int)obj->pos.y,
			(int)obj->sprite_back.pos.x, (int)obj->sprite_back.pos.y,
			(int)obj->sprite_back.size.x, (int)obj->sprite_back.size.y,
			obj->scale,
			(double)obj->rota,
			obj->sprite_back.texture,
			TRUE
		);

		SetDrawBright(255, 255, 255);
		// �I�u�W�F�N�g�O�i�`��
		DrawRectRotaGraph(
			(int)obj->pos.x, (int)obj->pos.y,
			(int)obj->sprite_front.pos.x, (int)obj->sprite_front.pos.y,
			(int)obj->sprite_front.size.x, (int)obj->sprite_front.size.y,
			obj->scale,
			(double)obj->rota,
			obj->sprite_front.texture,
			TRUE
		);
	}
}

void UpdateKamesutarStrike(void)
{
	mouse_input = GetMouseInput();
	static int m_input_old = 0;
	// �}�E�X�̍��W�擾
	int m_x, m_y;
	GetMousePoint(&m_x, &m_y);
	mouse = Vect2Create((float)m_x, (float)m_y);

	static Vector2D power = Vect2Create(0, 0);

	if ((MOUSE_INPUT_LEFT == mouse_input) && (m_input_old == 0))
	{
		mpoint1 = mouse;
	}

	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		KameObject* obj = &g_objects[i];

		if (CircleCollision(1, obj->hitsize.x / 2, mpoint1.x, obj->pos.x, mpoint1.y, obj->pos.y))
		{
			float rad = Vect2Angle(&Vect2Sub(&obj->pos, &mouse));
			if ((MOUSE_INPUT_LEFT == mouse_input) && (m_input_old == MOUSE_INPUT_LEFT))
			{
				power = Vect2Sub(&Vect2Add(&mpoint1, &Vect2Sub(&mpoint1, &mouse)), &mouse);
			}
			else if ((0 == mouse_input) && (m_input_old == MOUSE_INPUT_LEFT))
			{
				obj->vel = Vect2Div(&power, 5.0);
				obj->r_vel = rad;
				power = Vect2Create(0, 0);
			}
		}

		{
			obj->vel = Vect2Mul(&obj->vel, FRICTION);
			obj->r_vel *= FRICTION;
			Vector2D temp = Vect2AbsoluteValue(&obj->vel);
			if (temp.x < 0.1f)obj->vel.x = 0.0f;
			if (temp.y < 0.1f)obj->vel.y = 0.0f;

			obj->pos = Vect2Add(&obj->pos, &obj->vel);
			obj->rota += obj->r_vel;
		}

		{
			// �I�u�W�F�N�g�ɑ΂��Ă̕ǂ̈ʒu
			float padding_left = SCREEN_LEFT + obj->hitsize.x / 2;
			float padding_right = SCREEN_RIGHT - obj->hitsize.x / 2;
			float padding_top = SCREEN_TOP + obj->hitsize.y / 2;
			float padding_bottom = SCREEN_BOTTOM - obj->hitsize.y / 2;

			// �͈͂𒴂�����
			if (obj->pos.x < padding_left || padding_right <= obj->pos.x)
			{
				// ���ʉ���炷
				PlaySoundMem(g_sound_hit, DX_PLAYTYPE_BACK);
				if (GetRand(10) == 0)
					// ���܂ɕʂ̉���������
					PlaySoundMem(g_sounds[GetRand(NUM_SOUNDS - 1)], DX_PLAYTYPE_BACK);
				// ���x�𔽑΂ɂ���
				obj->vel.x *= -1;
			}
			if (obj->pos.y < padding_top || padding_bottom <= obj->pos.y)
			{
				// ���ʉ���炷
				PlaySoundMem(g_sound_hit, DX_PLAYTYPE_BACK);
				if (GetRand(10) == 0)
					// ���܂ɕʂ̉���������
					PlaySoundMem(g_sounds[GetRand(NUM_SOUNDS - 1)], DX_PLAYTYPE_BACK);
				// ���x�𔽑΂ɂ���
				obj->vel.y *= -1;
			}
			// �͂ݏo���C��
			obj->pos.x = ClampF(obj->pos.x, padding_left, padding_right);
			obj->pos.y = ClampF(obj->pos.y, padding_top, padding_bottom);
		}

		// Kame ���m�̓����蔻��
		{
			for (int j = 0; j < NUM_OBJECTS; j++)
			{
				if (i != j)
				{
					KameObject* obj2 = &g_objects[j];
					float hit1 = obj->hitsize.x / 2;
					float hit2 = obj2->hitsize.x / 2;
					//if (CircleColliAfterVel(&obj->pos, &obj2->pos, &obj->vel, &obj2->vel, hit1, hit2))
					if (CircleColliAfterRotateVel(&obj->pos, &obj2->pos, &obj->vel, &obj2->vel,
						hit1, hit2, &obj->r_vel, &obj2->r_vel, obj->m, obj2->m))
					{
						// ���ʉ���炷
						PlaySoundMem(g_sound_hit, DX_PLAYTYPE_BACK);
						if (GetRand(10) == 0)
							// ���܂ɕʂ̉���������
							PlaySoundMem(g_sounds[GetRand(NUM_SOUNDS - 1)], DX_PLAYTYPE_BACK);
					}
				}
			}
		}
	}

	m_input_old = GetMouseInput();
}
void RenderKamesutarStrike(void)
{
	// �w�i�𔒂œh��
	SetDrawBright(255, 255, 255);
	DrawBox(SCREEN_LEFT, SCREEN_TOP, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_WHITE, TRUE);

	// �I�u�W�F�N�g�`�揈��
	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		// �|�C���^�ɑ��
		KameObject *obj = &g_objects[i];

		// �I�u�W�F�N�g�w�i(�R�E��)�̐F���w��
		SetDrawBright(obj->color.r, obj->color.g, obj->color.b);
		obj->sprite_back.pos = obj->pos;
		obj->sprite_back.size = obj->hitsize;
		obj->sprite_back.scale = obj->scale;
		obj->sprite_back.rota = obj->rota;
		// �I�u�W�F�N�g�w�i�`��
		Sprite_DrawRotaSprite(&obj->sprite_back);

		SetDrawBright(255, 255, 255);
		obj->sprite_front.pos = obj->pos;
		obj->sprite_front.size = obj->hitsize;
		obj->sprite_front.scale = obj->scale;
		obj->sprite_front.rota = obj->rota;
		// �I�u�W�F�N�g�O�i�`��
		Sprite_DrawRotaSprite(&obj->sprite_front);

		if ((mouse_input == MOUSE_INPUT_LEFT))
		{
			DrawCircle(mpoint1.x, mpoint1.y, 5, COLOR_RED);
			DrawArrow(Vect2Add(&mpoint1, &Vect2Sub(&mpoint1, &mouse)), mouse, COLOR_RED);
		}
	}
}

void Update3(void)
{

}
void Render3(void)
{
	int mx, my;
	GetMousePoint(&mx, &my);
	mouse.x = (float)mx;	mouse.y = (float)my;

	DrawBox(0, 0, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_WHITE, TRUE);

	Vector2D temp = mouse;//Vect2Add(&pos1, &pos2);

	DrawCircle(pos1.x, pos1.y, 6, COLOR_BLUE, TRUE);
	DrawCircle(temp.x, temp.y, 6, COLOR_BLUE, TRUE);
	DrawLine(pos1.x, pos1.y, temp.x, temp.y, COLOR_BLUE);

	Line pline;
	pline.s = pos1;	pline.g = temp;
	Line line[4];
	line[TOP].s = Vect2Create(sc_left, sc_top);			line[TOP].g = Vect2Create(sc_right, sc_top);
	line[BOTTOM].s = Vect2Create(sc_left, sc_bottom);	line[BOTTOM].g = Vect2Create(sc_right, sc_bottom);
	line[LEFT].s = Vect2Create(sc_left, sc_top);		line[LEFT].g = Vect2Create(sc_left, sc_bottom);
	line[RIGHT].s = Vect2Create(sc_right, sc_top);		line[RIGHT].g = Vect2Create(sc_right, sc_bottom);

	for (int i = 0; i < VIEW_LINE_MAX; i++)
	{
		Vector2D cross_pos = Vect2Create(0, 0);
		float t1 = 0;

		Vector2D v1n = Vect2Mul(&Vect2Normalize(Vect2Sub(&temp, &pos1)), t1);
		if (CrossPoint(&pline, &line[i], &cross_pos))
		{
			DrawCircle(cross_pos.x, cross_pos.y, 6, COLOR_BLACK);
			DrawFormatString(0, 0, COLOR_GREEN, "cross pos : x = %3.2f", cross_pos.x);
			DrawFormatString(0, 20, COLOR_GREEN, "cross pos : y = %3.2f", cross_pos.y);
		}
	}

	DrawCircle(locus.pos.x, locus.pos.y, locus.r, COLOR_RED, FALSE);
	DrawBox(sc_left, sc_top, sc_right, sc_bottom, COLOR_RED, FALSE);

}

// �Q�[���̍X�V����
void UpdateGame(void)
{
	//Update2();
	//UpdateKame();
	//UpdateKamesutarStrike();
	Update3();
}

// �Q�[���̕`�揈��
void RenderGame(void)
{
	//Render2();
	//RenderKame();
	//RenderKamesutarStrike();
	Render3();
}

// �Q�[���̏I������
void FinalizeGame(void)
{

}


// �ȉ��I���W�i���֐� --------------------------------------------------



