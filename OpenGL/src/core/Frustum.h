#pragma once

#include "physics\plane.h"
#include "math\Matrix.h"

class BoundingSphere;
class AABB;

class Frustum
{
public:
	Frustum(const Matrix4f& matrix);

	Frustum(const Frustum& rhs)
	{
		for (unsigned int i = 0; i < 6; i++)
		{
			p[i] = rhs.p[i];
		}
	}

#undef FAR
#undef  NEAR
	enum Type
	{
		NEAR  = 0,
		FAR   = 1,
		LEFT  = 2,
		RIGHT = 3,
		UP    = 4,
		DOWN  = 5
	};

	bool pointIntersection(const Vector3f& point);
	bool SphereIntersection(const BoundingSphere& sphere);
	bool cubeIntersection(const AABB& cube);
	bool cubeIntersection(const BoundingSphere& sphere);
	Plane p[6];
};