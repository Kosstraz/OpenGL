#include "Behaviour.h"

Behaviour::Behaviour()
{}

void Behaviour::LoadShaders(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	Shaders s(vertexPath, fragmentPath);
	s.use();
}

void Behaviour::addiTextures(const char* firtsTexture, const char* secondTexture)
{
	//Texture t;
	//t.additiveTextures(firtsTexture, secondTexture);
}

void Behaviour::GetMatrix(const GLchar* name, int size, int count, float* values)
{

}

void Behaviour::GetUniform(const GLchar* name, int type, int size, float one, float two, float three, float four)
{

}

Behaviour::~Behaviour()
{}