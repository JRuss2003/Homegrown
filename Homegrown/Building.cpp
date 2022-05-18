#include "Building.h"
#include "Textures.h"
#include "ObjectManager.h"

void Building::Create(int x, int z)
{
	ObjectManager::Get()->Add(&buildingObject);
	
	buildingObject.CreateObject(x, 4, z, &Textures::Get()->Active_Tile, "GameData/Models/tree.obj");
}
