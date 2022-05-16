#include "Window.h"

void Window::Init(int x, int y, int width, int height)
{
	isRunning = true;
	this->width = width;
	this->height = height;
	//Init glfw
	glewExperimental = true;
	glfwInit();

	//Init opengl
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Create window
	window = glfwCreateWindow(width, height, "Homegrown", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window);

	//Init glew
	glewExperimental = true;
	glewInit();
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glfwSwapInterval(0);
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.34, 0.38, 0.62, 1.0);
}

void Window::Update()
{
	glfwSwapBuffers(window);
}
