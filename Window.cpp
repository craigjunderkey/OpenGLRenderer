#include "Window.h"

using namespace Graphics;

Window::Window(u16 width, u16 height, const char* title)
	: width_(width), height_(height)
{
	if (glfwInit() == GLFW_FALSE)
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	this->id_ = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(this->id_);

	if (glewInit() != GLEW_OK)
		exit(EXIT_FAILURE);

	glfwSwapInterval(1);
}

Window::~Window()
{
	glfwDestroyWindow(this->id_);
	glfwTerminate();
}