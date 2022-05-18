#pragma once
#include "ObjectManager.h"
#include "Scene.h"
#include "Building.h"

class Game
{
public:
	Game();
	void GameLoop();
	Scene scene;
	Building building;
};
