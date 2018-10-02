
#include "Collision.h"
#include <math.h>

//円同士の衝突
//(円1の半径, 円2の半径, 円1のx座標, 円2のx座標, 円1のy座標, 円2のy座標)
BOOL CircleCollision(double c1, double c2, double cx1, double cx2,
	double cy1, double cy2)
{
	double hlength = c1 + c2;
	double xlength = cx1 - cx2;
	double ylength = cy1 - cy2;

	if (hlength * hlength >= xlength * xlength + ylength * ylength)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//四角同士の衝突
//(box1_pos_x, box1_pos_y, box1_size_x, box1_size_y, box2_pos_x, box2_pos_y, box2_size_x, box2_size_y)
BOOL BoxCollision(double x1, double y1, double size_x1, double size_y1,
	double x2, double y2, double size_x2, double size_y2)
{
	double ax1 = x1 - size_x1 / 2, ax2 = x1 + size_x1 / 2;
	double ay1 = y1 - size_y1 / 2, ay2 = y1 + size_y1 / 2;

	double bx1 = x2 - size_x2 / 2, bx2 = x2 + size_x2 / 2;
	double by1 = y2 - size_y2 / 2, by2 = y2 + size_y2 / 2;

	DrawBox(ax1, ay1, ax2, ay2, COLOR_RED, FALSE);
	DrawBox(bx1, by1, bx2, by2, COLOR_RED, FALSE);

	if ((bx1 < ax2) && (by2 > ay1) && (by1 < ay2) && (ax1 < bx2))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// 線分の衝突
// a1	b1
// |	
// |	|
// |	|
// |
// a2	b2
BOOL LineCollision(double line_a1, double line_a2, double line_b1, double line_b2)
{
	if ((line_a1 < line_b1) && (line_a2 > line_b2))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool CalcParticleColliAfterPos(Vector2D* pos1,Vector2D* pos2,Vector2D* vel1, Vector2D* vel2,
	float r1, float r2)
{
	Vector2D p1p2 = Vect2Sub(pos2, pos1);	// パーティクル１とパーティクル２の最短距離のベクトル
	Vector2D C = Vect2Normalize(p1p2);		// p1p2 ベクトルを正規化したベクトル
	float len = sqrt(p1p2.x * p1p2.x + p1p2.y * p1p2.y);
	float distance = (r1 + r2) - len;
	float vlen1, vlen2;

	vlen1 = Vect2Length(*vel1);	vlen2 = Vect2Length(*vel2);

	*vel2 = Vect2Mul(&C, (double)vlen2);
	*vel1 = Vect2Mul(&Vect2Mul(&C,(-1)), (double)vlen1);
	
	return true;
}