#include "EventProcessor.h"
#include "Game.h"
#include "Clock.h"
#include "Camera.h"
#include "Window.h"
#include <cmath>
#include <iostream>
void EventProcessor::PollEvents()
{
	glfwPollEvents();
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		Window::Get()->isRunning = false;
	}
	if(glfwWindowShouldClose(Window::Get()->window) == 1)
		Window::Get()->isRunning = false;
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_W) == GLFW_PRESS) {
		Camera::Get()->camX += cos(Camera::Get()->angle) * Clock::Get()->deltaTime * 6.0;
		Camera::Get()->camZ += sin(Camera::Get()->angle) * Clock::Get()->deltaTime * 6.0;
	}																					   
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_S) == GLFW_PRESS) {					   
		Camera::Get()->camX -= cos(Camera::Get()->angle) * Clock::Get()->deltaTime * 6.0;
		Camera::Get()->camZ -= sin(Camera::Get()->angle) * Clock::Get()->deltaTime * 6.0;
	}																					   
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_A) == GLFW_PRESS) {					   
		Camera::Get()->camZ -= cos(Camera::Get()->angle) * Clock::Get()->deltaTime * 6.0;
		Camera::Get()->camX += sin(Camera::Get()->angle) * Clock::Get()->deltaTime * 6.0;
	}																					   
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_D) == GLFW_PRESS) {					   
		Camera::Get()->camZ += cos(Camera::Get()->angle) * Clock::Get()->deltaTime * 6.0;
		Camera::Get()->camX -= sin(Camera::Get()->angle) * Clock::Get()->deltaTime * 6.0;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_SPACE) == GLFW_PRESS && Camera::Get()->cameraWidthMax > 10.0f) {
		Camera::Get()->cameraWidthMax -= (float)(Window::Get()->width / 2.0f) * Clock::Get()->deltaTime / 80.0f;
		Camera::Get()->cameraWidthMin += (float)(Window::Get()->width / 2.0f) * Clock::Get()->deltaTime / 80.0f;
		Camera::Get()->cameraHeightMax -= (float)(Window::Get()->height / 2.0f) * Clock::Get()->deltaTime / 80.0f;
		Camera::Get()->cameraHeightMin += (float)(Window::Get()->height / 2.0f) * Clock::Get()->deltaTime / 80.0f;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && Camera::Get()->cameraWidthMax < (float)(Window::Get()->width / 4) / 2.0f) {
		Camera::Get()->cameraWidthMax += (float)(Window::Get()->width / 2.0f) * Clock::Get()->deltaTime / 80.0f;
		Camera::Get()->cameraWidthMin -= (float)(Window::Get()->width / 2.0f) * Clock::Get()->deltaTime / 80.0f;
		Camera::Get()->cameraHeightMax += (float)(Window::Get()->height / 2.0f) * Clock::Get()->deltaTime / 80.0f;
		Camera::Get()->cameraHeightMin -= (float)(Window::Get()->height / 2.0f) * Clock::Get()->deltaTime / 80.0f;
	}
}
