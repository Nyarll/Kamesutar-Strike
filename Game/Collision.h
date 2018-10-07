#pragma once
#include "GameObject.h"

BOOL CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
BOOL BoxCollision(double x1, double y1, double size_x1, double size_y1, double x2, double y2, double size_x2, double size_y2);

// �~�Q���Փ˂�����A���ꂼ��� Position ����̍ŒZ�������̃x�N�g���Œ��˕Ԃ�
bool CircleColliAfterVel(Vector2D* pos1, Vector2D* pos2, Vector2D* vel1, Vector2D* vel2,
	float r1, float r2);

// �~����Փ˂�����A�����ɋ߂������ŗ����
bool CircleColliAfterRotateVel(Vector2D* pos1, Vector2D* pos2,
	Vector2D* vel1, Vector2D* vel2, float r1, float r2,
	float* r_v1, float* r_v2, float m1, float m2);