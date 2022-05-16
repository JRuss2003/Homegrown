#pragma once
#include "ObjectManager.h"
#include "Map.h"

class Game
{
public:
	Game();
	void GameLoop();
	Map map;
};
