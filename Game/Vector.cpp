#include "Vector.h"
#define _USE_MATH_DEFINES
#include <math.h>

// 2Dベクトルの作成
Vector2D Vector2D_Create(float x, float y)
{
	Vector2D v;
	v.x = x;
	v.y = y;

	return v;
}

// 2Dベクトル同士の加算
Vector2D Vect2Add(Vector2D* vec1, const Vector2D* vec2)
{
	Vector2D v = { vec1->x + vec2->x, vec1->y + vec2->y };
	return v;
}
// 2Dベクトル同士の減算
Vector2D Vect2Sub(Vector2D* vec1, const Vector2D* vec2)
{
	Vector2D v = { vec1->x - vec2->x, vec1->y - vec2->y };
	return v;
}
// 2Dベクトル同士の乗算
Vector2D Vect2Mul(Vector2D* vec1, const double num)
{
	Vector2D v = { vec1->x * num, vec1->y * num };
	return v;
}
// 2Dベクトル同士の除算
Vector2D Vect2Div(Vector2D* vec1, const double num)
{
	Vector2D v = { vec1->x / num, vec1->y / num };
	return v;
}

// 2Dベクトルの角度
float Vect2Angle(Vector2D* vec)
{
	return atan2f(vec->y, vec->x);
}
// 2Dベクトルを　num の量だけ回転させる
Vector2D Vect2Rota(Vector2D* vec, const float r)
{
	float sc = Vect2Length(*vec);
	float angle = Vect2Angle(vec);
	return Vector2D_Create(cosf(angle + r) * sc, sinf(angle + r) * sc);
}


// 2Dベクトルの長さを獲得
float Vect2Length(Vector2D vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y));
}

// 2Dベクトルの正規化
Vector2D Vect2Normalize(Vector2D vec)
{
	float len = Vect2Length(vec);
	Vector2D v;

	v.x = vec.x / len;
	v.y = vec.y / len;

	return v;
}

// 2Dベクトル同士の内積
float Vect2Dot(Vector2D v0, Vector2D vec)
{
	return ((v0.x * vec.x) + (v0.y * vec.y));
}

// 2Dベクトル同士の外積
float Vect2Cross(Vector2D v0, Vector2D vec)
{
	return ((v0.x * vec.x) - (v0.y * vec.y));
}