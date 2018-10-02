#pragma once

#include "Vector.h"

BOOL CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
BOOL BoxCollision(double x1, double y1, double size_x1, double size_y1, double x2, double y2, double size_x2, double size_y2);
BOOL LineCollision(double line_a1, double line_a2, double line_b1, double line_b2);

bool CalcParticleColliAfterPos(Vector2D* pos1, Vector2D* pos2, Vector2D* vel1, Vector2D* vel2,
	float r1, float r2);