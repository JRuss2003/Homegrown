#pragma once
#include <GL/glew.h>
#include "GameObject.h"

#define GRASS 0
#define WATER 1

class Tile
{
public:
	int x, y;
	int ID;
};

extern GLfloat flatTileVertex[18];
extern GLfloat tileVertex[108];
extern GLfloat tileUv[72];
extern GLfloat tileNormal[108];