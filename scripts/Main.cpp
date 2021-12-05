#include "Window.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window ,int width, int height)
{
	glViewport(0, 0, width, height);
}

void MainWindow(const char* windowName = "", int width = 800, int height = 600)
{
	Window* window(0);
	GLFWwindow* glfwWindow = glfwCreateWindow(width, height, windowName, NULL, NULL);

	window->OpenWindow(glfwWindow);


	glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
}

int main()
{
	MainWindow();

	return 0;
}