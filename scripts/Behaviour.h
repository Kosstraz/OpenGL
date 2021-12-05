#pragma once
#ifndef DEF_BEHAVIOUR
#define DEF_BEHAVIOUR

#include "Shaders.h"
#include "Texture.h"

class Behaviour
{
public:
	Behaviour();

	static void LoadShaders(const GLchar* vertexPath, const GLchar* fragmentPath);
	static void GetMatrix(const GLchar* name, int size, int count, float* values);
	static void GetUniform(const GLchar* name, int type, int size, float one, float two = 0.0f, float three = 0.0f, float four = 1.0f);

	static void addiTextures(const char* firtsTexture, const char* secondTexture);

	~Behaviour();
protected:
};

#endif