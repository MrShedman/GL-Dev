#pragma once

#include "entity.h"
#include "coreEngine.h"
#include "components\physicsEngineComponent.h"

class Game
{
public:
	Game() {}
	virtual ~Game() {}

	virtual void Init(Window& window) {}

	void ProcessInput(const Event& event, float delta);

	void Update(float delta);

	void clear(RenderingEngine* renderingEngine, float r, float g, float b, float a);
	void Render(RenderingEngine* renderingEngine);
	
	inline void SetEngine(CoreEngine* engine) { m_root.SetEngine(engine); }
protected:
	void AddToScene(Entity* child) { m_root.AddChild(child); }
private:
	Game(Game& game) {}
	void operator=(Game& game) {}

	Entity       m_root;
};