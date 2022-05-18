#pragma once
#include <GL/glew.h>
#include "GameObject.h"

class Tile
{
public:
	int x, y;
};

extern GLfloat flatTileVertex[18];
extern GLfloat tileVertex[108];
extern GLfloat tileUv[72];
extern GLfloat tileNormal[108];