#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Types.h"

namespace Graphics
{
	class Window
	{
	public:
		Window(u16 width, u16 height, const char* title);
		GLFWwindow* id() const { return id_; }
		u16 width() const { return width_; }
		u16 height() const { return height_; }
		~Window();
	
	private:
		GLFWwindow* id_;
		u16 width_;
		u16 height_;
	};
}