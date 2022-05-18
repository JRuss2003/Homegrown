#include "Game.h"
#include "Window.h"
#include "RenderEngine.h"
#include "Textures.h"
#include "Clock.h"
#include "EventProcessor.h"

Game::Game()
{
	Window::Get()->Init(10, 10, 1024, 768);
	RenderEngine::Get()->Init();
	RenderEngine::Get()->LoadShaders("GameData/shaders/light.vs", "GameData/shaders/light.fs");
	RenderEngine::Get()->LoadShaders("GameData/shaders/light_source.vs", "GameData/shaders/light_source.fs");
	Textures::Get()->Load();
	Camera::Get()->Init();
	scene.Create();
	building.Create(10, 30);
	building2.Create(12, 30);
	GameLoop();
}

void Game::GameLoop()
{
	while(Window::Get()->isRunning) {
		Clock::Get()->Tick();
		EventProcessor::Get()->PollEvents();
		Camera::Get()->Update();
		scene.Update();
		Window::Get()->Clear();
		ObjectManager::Get()->Update();
		Window::Get()->Update();
	}
}
