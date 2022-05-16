#pragma once
#include <GL/glew.h>

class Tile
{
public:
	bool isSelected;
};

extern GLfloat tileVertex[108];
extern GLfloat tileUv[72];
extern GLfloat tileNormal[108];