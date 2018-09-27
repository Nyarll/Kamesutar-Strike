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

// 2Dベクトルの作成
Vector2D Vector2D_Create(float x, float y);

// 2Dベクトル同士の加算
Vector2D Vect2Add(Vector2D* vec1, const Vector2D* vec2);
// 2Dベクトル同士の減算
Vector2D Vect2Sub(Vector2D* vec1, const Vector2D* vec2);
//2Dベクトルの乗算
Vector2D Vect2Mul(Vector2D* vec1, const double num);
//2Dベクトルの除算
Vector2D Vect2Div(Vector2D* vec1, const double num);

// 2Dベクトルの角度
float Vect2Angle(Vector2D* vec);
// 2Dベクトルを num の量回転させる
Vector2D Vect2Rota(Vector2D* vec, const float r);

// 2Dベクトルの長さを獲得
float Vect2Length(Vector2D vec);
// 2Dベクトルの正規化
Vector2D Vect2Normalize(Vector2D vec);
// 2Dベクトル同士の内積
float Vect2Dot(Vector2D v0, Vector2D vec);
// 2Dベクトル同士の外積
float Vect2Cross(Vector2D v0, Vector2D vec);

