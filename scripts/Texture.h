#pragma once

#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#include "Behaviour.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	Texture();

	void addTexture(const char* name, bool rgba, GLenum pName = GL_TEXTURE_MIN_FILTER, int pValue = GL_LINEAR);
	void additiveTextures(const char* firtsTexture, const char* secondTexture);

	~Texture();
};

#endif