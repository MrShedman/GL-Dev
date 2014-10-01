#pragma once

#include "rendering/renderingEngine.h"

class Game;

//This is the central part of the game engine. It's purpose is to manage interaction 
//between the various sub-engines (such as the rendering and physics engines) and the game itself.
class CoreEngine
{
public:
	CoreEngine(unsigned int frameRate, Window* window, RenderingEngine* renderingEngine, Game* game);
	
	void Start(); //Starts running the game; contains central game loop.
	void Stop();  //Stops running the game, and disables all subsystems.
	
	inline RenderingEngine* GetRenderingEngine() { return m_renderingEngine; }
protected:
private:
	bool             m_isRunning;       //Whether or not the engine is running
	Window*          m_window;          //Used to display the game
	RenderingEngine* m_renderingEngine; //Used to render the game. Stored as pointer so the user can pass in a derived class.
	Game*            m_game;            //The game itself. Stored as pointer so the user can pass in a derived class.
};