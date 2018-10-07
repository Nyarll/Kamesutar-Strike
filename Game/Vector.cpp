#include "Vector.h"

// 2Dベクトルの作成
Vector2D Vect2Create(float x, float y)
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

// 2Dベクトルの乗算
Vector2D Vect2MulVect(Vector2D* vec1, const Vector2D* vec2)
{
	Vector2D v = *vec1;
	v.x *= vec2->x;
	v.y *= vec2->y;
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

// 2Dベクトル間の角度
float Vect2Angle2(Vector2D* vec1, Vector2D* vec2)
{
	float rad = atan2(vec2->y - vec1->y, vec2->x - vec1->x);
	
	return rad;
}

// 2Dベクトルを　num の量だけ回転させる
Vector2D Vect2Rota(Vector2D* vec, const float r)
{
	float sc = Vect2Length(*vec);
	float angle = Vect2Angle(vec);
	return Vect2Create(cosf(angle + r) * sc, sinf(angle + r) * sc);
}


// 2Dベクトルの長さを獲得
float Vect2Length(Vector2D vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y));
}

// 2Dベクトルの長さの二乗
float Vect2LengthSquared(Vector2D* vec)
{
	return ((vec->x * vec->x) + (vec->y * vec->y));
}

// 2Dベクトル同士の距離
float Vect2LengthTo(Vector2D* vec, Vector2D* other)
{
	return sqrtf(Vect2LengthSquaredTo(vec, other));
}

// 2Dベクトルの距離の二乗
float Vect2LengthSquaredTo(Vector2D* vec, Vector2D* other)
{
	return (other->x - vec->x) * (other->x - vec->x) + (other->y - vec->y) * (other->y - vec->y);
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
	return (v0.x * vec.y - vec.x * v0.y);
}

// 2Dベクトルを分解
void Vect2Decompose(Vector2D* vec, Vector2D* angle, Vector2D* vec_a, Vector2D* vec_b)
{
	float angle_rota = Vect2Angle(angle);
	float vec_rota = Vect2Angle(vec);
	float diff_rota = vec_rota - angle_rota;
	float vec_length = Vect2Length(*vec);

	float vec_a_length = vec_length * cosf(diff_rota);
	float vec_b_length = vec_length * sinf(diff_rota);
	float vec_a_rota = angle_rota;
	float vec_b_rota = angle_rota + (float)M_PI_2;

	*vec_a = Vect2Create(vec_a_length * cosf(vec_a_rota), vec_a_length * sinf(vec_a_rota));
	*vec_b = Vect2Create(vec_b_length * cosf(vec_b_rota), vec_b_length * sinf(vec_b_rota));
}

// 2Dベクトルの絶対値
Vector2D Vect2AbsoluteValue(Vector2D* vec)
{
	Vector2D temp = *vec;
	if (temp.x < 0)temp.x *= -1;
	if (temp.y < 0)temp.y *= -1;
	return temp;
}

BOOL CrossPoint(Line* line1, Line* line2, Vector2D* out_cross_point)
{
	Vector2D p1 = line1->s;
	Vector2D p2 = line1->g;
	Vector2D p3 = line2->s;
	Vector2D p4 = line2->g;

	float d = (p2.x - p1.x)*(p4.y - p3.y) - (p2.y - p1.y)*(p4.x - p3.x);
	if (d == 0)
		return FALSE;
	float u = ((p3.x - p1.x)*(p4.y - p3.y) - (p3.y - p1.y)*(p4.x - p3.x)) / d;
	float v = ((p3.x - p1.x)*(p2.y - p1.y) - (p3.y - p1.y)*(p2.x - p1.x)) / d;
	if (u < 0.0 || u > 1.0)
		return FALSE;
	if (v < 0.0 || v > 1.0)
		return FALSE;
	float outx = p1.x + u * (p2.x - p1.x);
	float outy = p1.y + u * (p2.y - p1.y);
	*out_cross_point = Vect2Create(outx, outy);

	return TRUE;
}