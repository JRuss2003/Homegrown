#include "Textures.h"
#include "RenderEngine.h"

void Textures::Load()
{
	tileset = RenderEngine::Get()->LoadTexture("GameData/Textures/grass.bmp");
	Active_Tile = RenderEngine::Get()->LoadTexture("GameData/Textures/Active_Tile.bmp");
}
