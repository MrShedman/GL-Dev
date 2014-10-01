
#include "game.h"

#include "rendering/renderingEngine.h"

void Game::ProcessInput(const Event& event, float delta)
{
	m_root.ProcessInputAll(event, delta);
}

void Game::Update(float delta)
{
	m_root.UpdateAll(delta);
}

void Game::clear(RenderingEngine* renderingEngine, float r, float g, float b, float a)
{
	renderingEngine->clear(r, g, b, a);
}

void Game::Render(RenderingEngine* renderingEngine)
{
	renderingEngine->Render(m_root);
}
