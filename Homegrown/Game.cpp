#include "Game.h"
#include "Window.h"
#include "RenderEngine.h"
#include "Textures.h"
#include "Clock.h"
#include "EventProcessor.h"

Game::Game()
{
	Window::Get()->Init(10, 10, 1920, 1080);
	glGenVertexArrays(1, &RenderEngine::Get()->VertexArrayID);
	RenderEngine::Get()->LoadShaders("GameData/shaders/light.vs", "GameData/shaders/light.fs");
	RenderEngine::Get()->LoadShaders("GameData/shaders/light_source.vs", "GameData/shaders/light_source.fs");
	Textures::Get()->Load();
	Camera::Get()->Init();
	map.Init();
	
	glUseProgram(RenderEngine::Get()->shaderIDs[1]);
	GameLoop();
}

void Game::GameLoop()
{
	while(Window::Get()->isRunning) {
		Clock::Get()->Tick();
		EventProcessor::Get()->PollEvents();
		Camera::Get()->Update();
		map.Update();
		Window::Get()->Clear();
		ObjectManager::Get()->Update();
		Window::Get()->Update();
	}
}
