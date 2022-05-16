#pragma once
#include "Mesh.h"
#include "glm.hpp"
#include "GL/glew.h"
#include <vector>
#include <string>

class GameObject
{
public:
	void CreateObject(int x, int y, int z, GLuint* texture, std::string modelPath);
	void CreateObjectFromMemory(int x, int y, int z, GLuint* texture, GLfloat* vertexData, GLfloat* uvData, GLfloat* normalData, int dataLength);
	void Update();
	void Destroy();
	Mesh mesh;
	glm::vec3 position;
	GLuint* targetTexture;
	float angle, angleY;
	bool isLightSource;
};

