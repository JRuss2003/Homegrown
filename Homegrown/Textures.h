#pragma once
#include "GL/glew.h"

class Textures
{
public:
	GLuint tileset;
	GLuint Active_Tile;
	void Load();
	static Textures* Get() { static Textures textures; return &textures; }
};
