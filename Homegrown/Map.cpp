#include "Map.h"
#include "Textures.h"
#include "ObjectManager.h"
#include "Game.h"
#include "Camera.h"

void Map::Init()
{
	//Create map object and add pass it to the manager.
	mapObject.position.x = 0.0f;
	mapObject.position.y = 0.0f;
	mapObject.position.z = 0.0f;
	std::vector<GLfloat> vertexData;
	std::vector<GLfloat> uvData;
	std::vector<GLfloat> normalData;
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int z = 0; z < MAP_SIZE; z++) {
			for (int i = 0; i < 36; i++) {
				vertexData.push_back(tileVertex[i * 3] + float(x) * 2);
				vertexData.push_back(tileVertex[i * 3 + 1]);
				vertexData.push_back(tileVertex[i * 3 + 2] + float(z) * 2);
				uvData.push_back(tileUv[i * 2]);
				uvData.push_back(tileUv[i * 2 + 1]);
				normalData.push_back(tileNormal[i * 3]);
				normalData.push_back(tileNormal[i * 3 + 1]);
				normalData.push_back(tileNormal[i * 3 + 2]);
			}
		}
	}
	ObjectManager::Get()->Add(&mapObject);
	mapObject.CreateObjectFromMemory(0, 0, 0, &Textures::Get()->tileset, &vertexData[0], &uvData[0], &normalData[0], vertexData.size() / 3);
	//Create active tile object and pass it to the manager.
	ObjectManager::Get()->Add(&activeTileObject);
	activeTileObject.CreateObjectFromMemory(0, 2, 0, &Textures::Get()->Active_Tile, flatTileVertex, tileUv, tileNormal, 6);
	
}

void Map::Update()
{
	//I love while true and nobody will ever stop me from using it no matter how 'bad' they say it is :)
	//Cast a ray from the mouse cursor to get set the activeTile.
	while (true) {
		Camera::Get()->raySource += Camera::Get()->rayVector / glm::vec1(80.0f);
		if (Camera::Get()->raySource.y < 1.0f && Camera::Get()->raySource.y > -1.0f && Camera::Get()->raySource.x > 0.0f && Camera::Get()->raySource.x < (MAP_SIZE - 1) * 2.0f && Camera::Get()->raySource.z > 0.0f && Camera::Get()->raySource.z < (MAP_SIZE - 1) * 2.0f) {
			activeTileObject.position.x = (int)((Camera::Get()->raySource.x + 1.0f) / 2.0f) * 2;
			activeTileObject.position.y = (int)(Camera::Get()->raySource.y / 2.0f) * 2;
			activeTileObject.position.z = (int)((Camera::Get()->raySource.z + 1.0f) / 2.0f) * 2;
			activeTileObject.position.y += 0.05;
			activeTile = &tileList[(int)Camera::Get()->raySource.x][(int)Camera::Get()->raySource.z];
			break;
		}
		else if (Camera::Get()->raySource.y < -1.0f) {
			break;
		}
	}

}
