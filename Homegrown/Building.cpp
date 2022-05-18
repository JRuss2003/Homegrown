#include "Building.h"
#include "Textures.h"
#include "ObjectManager.h"

void Building::Create(int x, int z)
{
	ObjectManager::Get()->Add(&buildingObject);
	
	buildingObject.CreateObject(x, 1, z, &Textures::Get()->road_tex, "GameData/Models/road_1.obj");
}
