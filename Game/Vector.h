#pragma once

#define __PI (3.141592653589793238)
#define DEG_TO_RAD(DEG)	((DEG) * (__PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / __PI))

// 2D ベクトル
typedef struct
{
	float x, y;
}Vector2D;

// 3D ベクトル
typedef struct
{
	float x, y, z;
}Vector3D;

typedef Vector2D Point2D;
typedef Vector3D Point3D;

// 2Dベクトルの作成
Vector2D Vect2Create(float x, float y);

// 2Dベクトル同士の加算
Vector2D Vect2Add(Vector2D* vec1, const Vector2D* vec2);
// 2Dベクトル同士の減算
Vector2D Vect2Sub(Vector2D* vec1, const Vector2D* vec2);
// 2Dベクトルの乗算 (定数倍)
Vector2D Vect2Mul(Vector2D* vec1, const double num);
// 2Dベクトルの除算
Vector2D Vect2Div(Vector2D* vec1, const double num);

// 2Dベクトルの角度
float Vect2Angle(Vector2D* vec);
// 2Dベクトルを num の量回転させる
Vector2D Vect2Rota(Vector2D* vec, const float r);

// 2Dベクトルの長さを獲得
float Vect2Length(Vector2D vec);
// 2Dベクトルの長さの二乗
float Vect2LengthSquared(Vector2D* vec);
// 2Dベクトル同士の距離
float Vect2LengthTo(Vector2D* vec, Vector2D* other);
// 2Dベクトルの距離の二乗
float Vect2LengthSquaredTo(Vector2D* vec, Vector2D* other);
// 2Dベクトルの正規化
Vector2D Vect2Normalize(Vector2D vec);
// 2Dベクトル同士の内積
float Vect2Dot(Vector2D v0, Vector2D vec);
// 2Dベクトル同士の外積
float Vect2Cross(Vector2D v0, Vector2D vec);
// 2Dベクトルを分解
void Vect2Decompose(Vector2D* vec, Vector2D* angle, Vector2D* vec_a, Vector2D* vec_b);
// 2Dベクトルの絶対値
Vector2D Vect2AbsoluteValue(Vector2D* vec);