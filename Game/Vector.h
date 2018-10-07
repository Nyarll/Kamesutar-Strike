#pragma once

#include "Define.h"

// 2D �x�N�g��
typedef struct
{
	float x, y;
}Vector2D;

// 3D �x�N�g��
typedef struct
{
	float x, y, z;
}Vector3D;

// <Line>
typedef struct
{
	Vector2D s;
	Vector2D g;
}Line;

typedef Vector2D Point2D;
typedef Vector3D Point3D;

// 2D�x�N�g���̍쐬
Vector2D Vect2Create(float x, float y);

// 2D�x�N�g�����m�̉��Z
Vector2D Vect2Add(Vector2D* vec1, const Vector2D* vec2);
// 2D�x�N�g�����m�̌��Z
Vector2D Vect2Sub(Vector2D* vec1, const Vector2D* vec2);
// 2D�x�N�g���̏�Z (�萔�{)
Vector2D Vect2Mul(Vector2D* vec1, const double num);
// 2D�x�N�g���̏�Z
Vector2D Vect2MulVect(Vector2D* vec1, const Vector2D* vec2);
// 2D�x�N�g���̏��Z
Vector2D Vect2Div(Vector2D* vec1, const double num);

// 2D�x�N�g���̊p�x
float Vect2Angle(Vector2D* vec);
// 2D�x�N�g���Ԃ̊p�x
float Vect2Angle2(Vector2D* vec1, Vector2D* vec2);
// 2D�x�N�g���� num �̗ʉ�]������
Vector2D Vect2Rota(Vector2D* vec, const float r);

// 2D�x�N�g���̒������l��
float Vect2Length(Vector2D vec);
// 2D�x�N�g���̒����̓��
float Vect2LengthSquared(Vector2D* vec);
// 2D�x�N�g�����m�̋���
float Vect2LengthTo(Vector2D* vec, Vector2D* other);
// 2D�x�N�g���̋����̓��
float Vect2LengthSquaredTo(Vector2D* vec, Vector2D* other);
// 2D�x�N�g���̐��K��
Vector2D Vect2Normalize(Vector2D vec);
// 2D�x�N�g�����m�̓���
float Vect2Dot(Vector2D v0, Vector2D vec);
// 2D�x�N�g�����m�̊O��
float Vect2Cross(Vector2D v0, Vector2D vec);
// 2D�x�N�g���𕪉�
void Vect2Decompose(Vector2D* vec, Vector2D* angle, Vector2D* vec_a, Vector2D* vec_b);
// 2D�x�N�g���̐�Βl
Vector2D Vect2AbsoluteValue(Vector2D* vec);
// 2�̐���(����)�̌�_
BOOL CrossPoint(Line* line1, Line* line2, Vector2D* out_cross_point);