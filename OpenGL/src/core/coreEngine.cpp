
#include "coreEngine.h"
#include "window/window.hpp"
#include "game.h"
#include "SystemInfo.h"
#include <iostream>

CoreEngine::CoreEngine(unsigned int frameRate, Window* window, RenderingEngine* renderingEngine, Game* game) :
	m_isRunning(false),
	m_window(window),
	m_renderingEngine(renderingEngine),
	m_game(game)
{
	m_window->setFramerateLimit(frameRate);

	//We're telling the game about this engine so it can send the engine any information it needs
	//to the various subsystems.
	m_game->SetEngine(this);

	//Game is initialized here because this is the point where all rendering systems
	//are initialized, and so creating meshes/textures/etc. will not fail due
	//to missing context.
	m_game->Init(*m_window);
}

void CoreEngine::Start()
{
	if(m_isRunning)
	{
		return;
	}
		
	m_isRunning = true;

	const Time timePerFrame = seconds(1.0f / 60.0f);

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	CpuInfo cpu;

	while(m_isRunning)
	{
		Time dt;
		dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			Event event;

			while (m_window->pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					Stop();
				}

				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Return && event.key.alt)
					{
						if (m_window->isFullscreen())
						{
							m_window->switchToWindowed(VideoMode(1280, 720), Style::Default , true);
						}
						else
						{
							m_window->switchToFullscreen(VideoMode::getFullscreenModes()[0]);
						}
					}
					if (event.key.code == Keyboard::F)
					{
						m_window->setDragDropAllowed(!m_window->isDragDropAllowed());
					}
				}
				if (event.type == Event::FileDrop)
				{
					std::cout << "Number of files: " << event.fileDrop.fileCount << std::endl;
					std::cout << "Position: " << event.fileDrop.x << ", " << event.fileDrop.y << std::endl;

					for (int i = 0; i < event.fileDrop.fileCount; ++i)
					{
						std::cout << "File " << i << ": " << event.fileDrop.files[i] << std::endl;
					}
				}
			
				m_renderingEngine->ProcessInput(event);
				m_game->ProcessInput(event, timePerFrame.asSeconds());
			}

			m_game->Update(timePerFrame.asSeconds());
			cpu.getUsage();
		}

		m_game->clear(m_renderingEngine, 120.f, 200.f, 255.f, 255.f);
		m_game->Render(m_renderingEngine);
		m_window->display();
	}
}

void CoreEngine::Stop()
{
	m_isRunning = false;
}

