#pragma once

#define __PI (3.141592653589793238)
#define DEG_TO_RAD(DEG)	((DEG) * (__PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / __PI))

typedef struct
{
	float x, y;
}Vector2D;

typedef struct
{
	float x, y, z;
}Vector3D;

typedef Vector2D Point2D;
typedef Vector3D Point3D;

// 2D�x�N�g���̍쐬
Vector2D Vector2D_Create(float x, float y);

// 2D�x�N�g�����m�̉��Z
Vector2D Vect2Add(Vector2D* vec1, const Vector2D* vec2);
// 2D�x�N�g�����m�̌��Z
Vector2D Vect2Sub(Vector2D* vec1, const Vector2D* vec2);
//2D�x�N�g���̏�Z
Vector2D Vect2Mul(Vector2D* vec1, const double num);
//2D�x�N�g���̏��Z
Vector2D Vect2Div(Vector2D* vec1, const double num);

// 2D�x�N�g���̊p�x
float Vect2Angle(Vector2D* vec);
// 2D�x�N�g���� num �̗ʉ�]������
Vector2D Vect2Rota(Vector2D* vec, const float r);

// 2D�x�N�g���̒������l��
float Vect2Length(Vector2D vec);
// 2D�x�N�g���̐��K��
Vector2D Vect2Normalize(Vector2D vec);
// 2D�x�N�g�����m�̓���
float Vect2Dot(Vector2D v0, Vector2D vec);
// 2D�x�N�g�����m�̊O��
float Vect2Cross(Vector2D v0, Vector2D vec);

