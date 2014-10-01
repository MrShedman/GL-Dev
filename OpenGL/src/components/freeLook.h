#pragma once

#include "core\entityComponent.h"
#include "math\Vector.h"

class FreeLook : public EntityComponent
{
public:
	FreeLook(const Vector2f& windowCenter,Window& window, float sensitivity = 0.5f) :
		m_sensitivity(sensitivity),
		m_mouseLocked(false),
		m_windowCenter(windowCenter),
		m_window(window)
	{}
	
	virtual void ProcessInput(const Event& event, float delta);
protected:
private:
	float    m_sensitivity;
	bool     m_mouseLocked;
	Vector2f m_windowCenter;
	Window&  m_window;
};