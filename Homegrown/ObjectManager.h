#pragma once
#include "GameObject.h"
#include "GL/glew.h"
#include <vector>

class ObjectManager
{
public:
	static ObjectManager* Get() { static ObjectManager objectManager; return &objectManager; };
	std::vector<GameObject> objectQueue;
	void Add(GameObject targetObject);
	void Update();
};

