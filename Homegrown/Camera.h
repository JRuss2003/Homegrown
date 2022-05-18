#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	void Init();
	void Update();
	static Camera* Get() { static Camera camera; return &camera; }
	GLuint MatrixID;
	glm::mat4 projection;
	glm::mat4 view;
	float camX;
	float camY;
	float camZ;
	float angle;
	float angleY;
	float whRatio;
	float cameraWidthMin, cameraWidthMax, cameraHeightMin, cameraHeightMax;
	//Mouse-picking
	glm::vec3 worldUp;
	glm::vec3 camDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 raySource;
	glm::vec3 rotationSource;
	glm::vec3 rayDirection;
	glm::vec3 camTarget;
	glm::vec3 rayVector;
	double mouseX;
	double mouseY;
};
