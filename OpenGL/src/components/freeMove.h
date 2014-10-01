#pragma once

#include "math\Vector.h"
#include "core\entityComponent.h"

class FreeMove : public EntityComponent
{
public:
	FreeMove(float speed = 10.0f) :
		m_speed(speed)
	{}

	virtual void Update(float delta);

private:
	void Move(const Vector3f& direction, float amt);

	float m_speed;
};