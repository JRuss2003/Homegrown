#include "Camera.h"
#include "Window.h"
#include "RenderEngine.h"
#include "Clock.h"

void Camera::Init()
{
	camX = 0.0f;
	camY = 128.0f;
	camZ = 0.0f;
	angleY = -0.61540309;
	angle = -0.785398;
	camTarget = glm::vec3(camX + cos(angle), camY + tan(angleY), camZ + sin(angle));
	cameraWidthMin = -(float)(Window::Get()->width / 2) / 4.0f;
	cameraWidthMax = (float)(Window::Get()->width / 2) / 4.0f;
	cameraHeightMin = -(float)(Window::Get()->height / 2) / 4.0f;
	cameraHeightMax = (float)(Window::Get()->height / 2) / 4.0f;
	projection = glm::orthoRH(cameraWidthMin, cameraWidthMax, cameraHeightMin, cameraHeightMax, -1000.0f, 1000.0f);
	view = glm::lookAt(glm::vec3(camX, camY, camZ), camTarget, glm::vec3(0.0, 1.0, 0.0));
	MatrixID = glGetUniformLocation(RenderEngine::Get()->shaderIDs[0], "MVP");
	//Mouse-picking
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	camDirection = glm::normalize(camTarget - glm::vec3(camX, camY, camZ));
	cameraRight = glm::normalize(glm::cross(camDirection, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, camDirection));
	raySource = glm::vec3(camX, camY, camZ) + cameraRight + cameraUp;
	rayDirection = camDirection;
}

void Camera::Update()
{
	camTarget = glm::vec3(camX + cos(angle), camY + tan(angleY), camZ + sin(angle));
	projection = glm::orthoRH(cameraWidthMin, cameraWidthMax, cameraHeightMin, cameraHeightMax, -1000.0f, 1000.0f);
	view = glm::lookAt(glm::vec3(camX, camY, camZ), camTarget, glm::vec3(0.0, 1.0, 0.0));
	//Mouse-picking
	rayVector = glm::vec3(cos(angle),tan(angleY),sin(angle));
	glfwGetCursorPos(Window::Get()->window, &mouseX, &mouseY);
	mouseX = +(2.0f * mouseX / Window::Get()->width - 1) * ((cameraWidthMax * 2) / 2);
	mouseY = -(2.0f * mouseY / Window::Get()->height - 1) * ((cameraHeightMax * 2) / 2);
	camDirection = glm::normalize(camTarget - glm::vec3(camX, camY, camZ));
	cameraRight = glm::normalize(glm::cross(camDirection, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, camDirection));
	raySource = glm::vec3(camX, camY, camZ) + cameraRight  * glm::vec1(mouseX) + cameraUp * glm::vec1(mouseY);
	rayDirection = camDirection;
}

