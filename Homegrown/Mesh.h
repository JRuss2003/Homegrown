#pragma once
#include <gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>
#include <gtx/quaternion.hpp>
class Mesh
{
public:
	void Init(float x, float y, float z);
	void AddIndex(int index);
	void LoadFromMemory(GLfloat* vertexData, GLfloat* uvData, GLfloat* normalData, int dataLength);
	void LoadFromFile(std::string path);
	void Unload();
	void Update(glm::vec3* parentPos);
	void MoveTo(float x, float y, float z, glm::vec3* parentPos);
	void RotateTo(float angle, float meshangle);
	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec2> uvData;
	std::vector<glm::vec3> normalData;
	std::vector<unsigned int> indices;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;
	GLuint* targetShader;
	glm::mat4 model;
	glm::mat4 mvp;
	glm::quat angleQuat;
};

