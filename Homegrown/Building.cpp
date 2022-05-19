#include "Building.h"
#include "Textures.h"
#include "ObjectManager.h"

void Building::Create(int x, int z)
{
	ObjectManager::Get()->Add(&buildingObject);
	
	buildingObject.CreateObject(x, 10, z, &Textures::Get()->road_tex, "GameData/Models/tree.obj");
}
