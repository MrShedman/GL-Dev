#pragma once

#include "math\Vector.h"
#include "boundingSphere.h"

/**
 * The Plane class represents an infinitely large plane that can be used as
 * a collider in a physics engine.
 */
class Plane
{
public:

	Plane() :
		m_normal(Vector3f()),
		m_distance(0.f)
	{}

	/** 
	 * Creates a Plane in a usable state.
	 * 
	 * @param normal   The "up" direction from the plane's surface.
	 * @param distance The distance to the plane from the world origin 
	 *                   along the normal
	 */
	Plane(const Vector3f& normal, float distance) :
		m_normal(normal.Normalized()),
		m_distance(distance / normal.Length()) {}

	Plane& Plane::operator=(Plane rhs)
	{
		m_normal = rhs.m_normal;
		m_distance = rhs.m_distance;
		return *this;
	}

	/**
	 * Creates an equivalent plane with a normal at unit length and distance
	 * adjusted accordingly.
	 */
	Plane Normalized() const;

	/**
	 * Computes information about if this Plane intersects a Sphere.
	 *
	 * @param other The Sphere that's being tested for intersection with this
	 *                Plane.
	 */
	IntersectData IntersectSphere(const BoundingSphere& other) const;

	inline const Vector3f& GetNormal() const { return m_normal; }
	inline float GetDistance()         const { return m_distance; }

	/** Performs a Unit Test of this class */
	static void Test();
private:
	/** The "up" direction from the plane's surface. */
	Vector3f m_normal;
	/** The distance to the plane from the world origin along the normal */
	float    m_distance;
};