#include "Frustum.h"
#include "math\Vector.h"
#include "physics\boundingSphere.h"
#include "physics\aabb.h"
#include <iostream>

Frustum::Frustum(const Matrix4f& m)
{
	Vector3f right = Vector3f(m[0][3] - m[0][0], m[1][3] - m[1][0], m[2][3] - m[2][0]);

	p[RIGHT] = Plane(right, m[3][3] - m[3][0]);

	Vector3f left = Vector3f(m[0][3] + m[0][0], m[1][3] + m[1][0], m[2][3] + m[2][0]);

	p[LEFT] = Plane(left, m[3][3] + m[3][0]);

	Vector3f down = Vector3f(m[0][3] + m[0][1], m[1][3] + m[1][1], m[2][3] + m[2][1]);

	p[DOWN] = Plane(down, m[3][3] + m[3][1]);

	Vector3f up = Vector3f(m[0][3] - m[0][1], m[1][3] - m[1][1], m[2][3] - m[2][1]);

	p[UP] = Plane(up, m[3][3] - m[3][1]);

	Vector3f far = Vector3f(m[0][3] - m[0][2], m[1][3] - m[1][2], m[2][3] - m[2][2]);

	p[FAR] = Plane(far, m[3][3] - m[3][2]);

	Vector3f near = Vector3f(m[0][3] + m[0][2], m[1][3] + m[1][2], m[2][3] + m[2][2]);

	p[NEAR] = Plane(near, m[3][3] + m[3][2]);
}

bool Frustum::pointIntersection(const Vector3f& point)
{
	for(int i = 0; i < 6; i++ )
    {
		if (point.Dot(p[i].GetNormal()) + p[i].GetDistance() <= 0)
		{
			// The point was behind a side, so it ISN'T in the frustum
            return false;
        }
    }

	return true;
}

bool Frustum::SphereIntersection(const BoundingSphere& sphere)
{
	Vector3f centre = sphere.GetCenter();
	float radius = sphere.GetRadius();

	// Loop through each plane that comprises the frustum.
	for (int i = 0; i < 6; i++)
	{
		if (centre.Dot(p[i].GetNormal()) + p[i].GetDistance() + radius <= 0)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::cubeIntersection(const AABB& cube)
{
	/*Vector3f centre = sphere.GetCenter();
	float radius = sphere.GetRadius();

	// Loop through each plane that comprises the frustum.
	for (int i = 0; i < 6; i++)
	{
		if (centre.Dot(p[i].GetNormal()) + p[i].GetDistance() + radius <= 0)
		{
			return false;
		}
	}
	*/
	return true;
}

bool Frustum::cubeIntersection(const BoundingSphere& sphere)
{
	Vector3f centre = sphere.GetCenter();
	float radius = sphere.GetRadius();

	float maxX = centre.x + radius;
	float minX = centre.x - radius;

	float maxY = centre.y + radius;
	float minY = centre.y - radius;
	
	float maxZ = centre.z + radius;
	float minZ = centre.z - radius;

	for (int i = 0; i < 6; i++)
	{
		if (pointIntersection(Vector3f(maxX, maxY, maxZ)))
		{
			continue;
		}
		if (pointIntersection(Vector3f(maxX, maxY, minZ)))
		{
			continue;
		}
		if (pointIntersection(Vector3f(maxX, minY, maxZ)))
		{
			continue;
		}
		if (pointIntersection(Vector3f(maxX, minY, minZ)))
		{
			continue;
		}
		if (pointIntersection(Vector3f(minX, maxY, maxZ)))
		{
			continue;
		}
		if (pointIntersection(Vector3f(minX, maxY, minZ)))
		{
			continue;
		}
		if (pointIntersection(Vector3f(minX, minY, maxZ)))
		{
			continue;
		}
		if (pointIntersection(Vector3f(minX, minY, minZ)))
		{
			continue;
		}

		return false;
	}

	return true;
}
