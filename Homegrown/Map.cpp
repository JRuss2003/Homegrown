#include "Map.h"
#include "Textures.h"
#include "ObjectManager.h"
#include "Game.h"
#include "Camera.h"

void Map::Init()
{
	GameObject mapObject;
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
	ObjectManager::Get()->Add(mapObject);
	ObjectManager::Get()->objectQueue[ObjectManager::Get()->objectQueue.size() - 1].CreateObjectFromMemory(0, 0, 0, &Textures::Get()->tileset, &vertexData[0], &uvData[0], &normalData[0], vertexData.size() / 3);
	GameObject activeTile;
	ObjectManager::Get()->Add(activeTile);
	ObjectManager::Get()->objectQueue[ObjectManager::Get()->objectQueue.size() - 1].CreateObjectFromMemory(0, 2, 0, &Textures::Get()->Active_Tile, tileVertex, tileUv, tileNormal, 36);
	this->activeTileObject = &ObjectManager::Get()->objectQueue[ObjectManager::Get()->objectQueue.size() - 1];
	this->activeTileObject->position.x = 40.0f;
	this->activeTileObject->position.z = 20.0f;
}

void Map::Update()
{
	//I love while true and nobody will ever stop me from using it no matter how 'bad' they say it is :)
	while (true) {
		Camera::Get()->raySource += Camera::Get()->rayVector / glm::vec1(80.0f);
		if (Camera::Get()->raySource.y < 1.0f) {
			activeTileObject->position.x = (int)((Camera::Get()->raySource.x + 1.0f) / 2.0f) * 2;
			activeTileObject->position.y = (int)(Camera::Get()->raySource.y / 2.0f) * 2;
			activeTileObject->position.z = (int)((Camera::Get()->raySource.z + 1.0f) / 2.0f) * 2;
			activeTileObject->position.y += 0.05;
			break;
		}
	}

	for (int x = 0; x < MAP_SIZE; x++) {
		for (int z = 0; z < MAP_SIZE; z++) {
			if (tileList[x][z].isSelected == true) {
				if(activeTile != nullptr)
					activeTile->isSelected = false;
				activeTile = &tileList[x][z];
				activeTileObject->position.x = x * 2.0f;
				activeTileObject->position.z = z * 2.0f;
			}
		}
	}
}
