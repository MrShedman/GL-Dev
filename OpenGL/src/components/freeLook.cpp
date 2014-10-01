
#include "freeLook.h"
#include "window\window.hpp"
#include "math\Matrix.h"
#include "math\Quaternion.h"
#include "math\MathHelper.h"
#include "window\Mouse.h"

void FreeLook::ProcessInput(const Event& event, float delta)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			m_window.setRawMouseInput(true);
			m_window.setMouseCursorVisible(false);
			m_window.setClippedCursor(true);
		}
	}
	else if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape || event.key.code == Keyboard::E)
		{
			m_window.setRawMouseInput(false);
			m_window.setMouseCursorVisible(true);
			m_window.setClippedCursor(false);
		}
	}
	else if (event.type == Event::MouseMotion)
	{
		GetTransform()->Rotate(Vector3f(0, 1, 0), ToRadians(event.mouseMotion.dx * m_sensitivity));

		GetTransform()->Rotate(GetTransform()->GetRot()->GetRight(), ToRadians(event.mouseMotion.dy * m_sensitivity));
	}
}