#include "Collision.h"


//�~���m�̏Փ�
//(�~1�̔��a, �~2�̔��a, �~1��x���W, �~2��x���W, �~1��y���W, �~2��y���W)
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

//�l�p���m�̏Փ�
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


bool CircleColliAfterVel(Vector2D* pos1, Vector2D* pos2,
	Vector2D* vel1, Vector2D* vel2, float r1, float r2)
{
	// �������Ă��邩�ǂ���
	if (CircleCollision(r1, r2, pos1->x, pos2->x, pos1->y, pos2->y))
	{
		// �ՓˑO
		Vector2D vbefore1 = *vel1;
		Vector2D vbefore2 = *vel2;

		// �ړ���̊p�x
		Vector2D angle = Vect2Create(pos2->x - pos1->x, pos2->y - pos1->y);
		{
			// ������̃x�N�g��
			Vector2D vafter1_parallel, vafter2_parallel;
			Vector2D vafter1_vertical, vafter2_vertical;

			// ����
			Vect2Decompose(&vbefore1, &angle, &vafter1_parallel, &vafter1_vertical);
			Vect2Decompose(&vbefore2, &angle, &vafter2_parallel, &vafter2_vertical);

			// �Փˌ���������ċ��߂�
			*vel1 = Vect2Add(&vafter2_parallel, &vafter1_vertical);
			*vel2 = Vect2Add(&vafter1_parallel, &vafter2_vertical);
		}
		return true;
	}
	return false;
}

bool CircleColliAfterRotateVel(Vector2D* pos1, Vector2D* pos2,
	Vector2D* vel1, Vector2D* vel2, float r1, float r2,
	float* r_v1, float* r_v2, float m1, float m2)
{
	float e = 1.0f;	// �����W��

	if (CircleCollision(r1, r2, pos1->x, pos2->x, pos1->y, pos2->y))
	{
		// 2 �t���[�� �O�� Position
		Vector2D before_pos1 = Vect2Sub(pos1, &Vect2Add(vel1, vel1));
		Vector2D before_pos2 = Vect2Sub(pos2, &Vect2Add(vel2, vel2));

		// �ՓˑO
		Vector2D vbefore1 = *vel1;
		Vector2D vbefore2 = *vel2;

		// �ړ���̊p�x
		Vector2D angle = Vect2Create(pos2->x - pos1->x, pos2->y - pos1->y);

		{
			// ������̃x�N�g��
			Vector2D vafter1_parallel, vafter2_parallel;	// ���s
			Vector2D vafter1_vertical, vafter2_vertical;	// ����

			// ����
			Vect2Decompose(&vbefore1, &angle, &vafter1_parallel, &vafter1_vertical);
			Vect2Decompose(&vbefore2, &angle, &vafter2_parallel, &vafter2_vertical);

			// �Փˌ���������ċ��߂�

			Vector2D vafter1 = Vect2Add(&vafter2_parallel, &vafter1_vertical);
			Vector2D vafter2 = Vect2Add(&vafter1_parallel, &vafter2_vertical);
			*vel1 = vafter1;
			*vel2 = vafter2;

			*pos1 = before_pos1;
			*pos2 = before_pos2;

			float rv_temp = (-(*r_v1));
			*r_v1 = (-(*r_v2));
			*r_v2 = rv_temp;
		}
		return true;
	}


	return false;
}
