#pragma once

#ifndef DEF_SHADERS
#define DEF_SHADERS

#include "Behaviour.h"
#include "Window.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shaders
{
public:
	Shaders(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);

	void setMatrix(const GLchar* name, int size, int count, float* values);
	void setUniform(const GLchar* name, int type, int size, float one, float two = 0.0f, float three = 0.0f, float four = 1.0f);

	~Shaders();

private:
	unsigned int ID;	//programme ID
};

#endif