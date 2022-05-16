#pragma once
#include "GL/glew.h"

class Textures
{
public:
	GLuint tileset;
	GLuint stoneTex;
	GLuint house_1;
	GLuint tree_1;
	GLuint Active_Tile;
	void Load();
	static Textures* Get() { static Textures textures; return &textures; }
};
