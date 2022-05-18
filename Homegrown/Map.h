#pragma once
#include "Tile.h"
#include "GameObject.h"

#define MAP_SIZE 64

class Map
{
public:
	void Init();
	void Update();
	Tile tileList[MAP_SIZE][MAP_SIZE];
	GameObject activeTileObject;
	GameObject mapObject;
	Tile* activeTile;
};

