
#include "freeMove.h"
#include "math\Matrix.h"
#include "math\Quaternion.h"

void FreeMove::Update(float delta)
{
	float mult = 1.0f;

	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		mult = 3.0f;
	}

	float movAmt = m_speed * delta * mult;

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		Move(Vector3f(0, 1, 0), movAmt);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		Move(GetTransform()->GetRot()->GetForward(), movAmt);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		Move(GetTransform()->GetRot()->GetBack(), movAmt);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		Move(GetTransform()->GetRot()->GetLeft(), movAmt);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		Move(GetTransform()->GetRot()->GetRight(), movAmt);
	}
}

void FreeMove::Move(const Vector3f& direction, float amt)
{
	GetTransform()->Move(direction * amt);
}