#pragma once

#ifndef DEF_WINDOW
#define DEF_WINDOW

#include "Behaviour.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	void BackgroundColor(float r, float g, float b, float a);

	bool GetInput(GLFWwindow* window, int key, int action, bool infoLog);
	void CloseWindow(GLFWwindow* window, int key);
	int OpenWindow(GLFWwindow* window, const char* windowName = "OpenGL - Window");

	void BuildTriangle(GLFWwindow* window);

	~Window();
};

#endif