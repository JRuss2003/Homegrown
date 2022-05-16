#include "Textures.h"
#include "RenderEngine.h"

void Textures::Load()
{
	tileset = RenderEngine::Get()->LoadTexture("GameData/Textures/grass.bmp");
	stoneTex = RenderEngine::Get()->LoadTexture("GameData/Textures/cloth.bmp");
	house_1 = RenderEngine::Get()->LoadTexture("GameData/Textures/Room_1.bmp");
	tree_1 = RenderEngine::Get()->LoadTexture("GameData/Textures/tree.bmp");
	Active_Tile = RenderEngine::Get()->LoadTexture("GameData/Textures/Active_Tile.bmp");
}
