#include "Shaders.h"

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define W_FLOAT 0
#define W_DOUBLE 1
#define W_INT 2
#define W_UINT 3
#define W_FLOATV 4

Shaders::Shaders(const GLchar* vertexPath, const GLchar* fragmentPath) : ID(0)
{
	//récupérer le code depuis le filePath//
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	//peuvent envoyer des exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//ouverture des fichiers:
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//lecture des fichiers et place le contenu dans des flux:
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//fermeture des fichiers:
		vShaderFile.close();
		fShaderFile.close();
		//convertion en string:
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//Compilation des shaders//
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader:
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// erreurs de compilation:
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILE\n" << infoLog << std::endl;
	}

	// fragment Shader:
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILE\n" << infoLog << std::endl;
	}

	// program Shader:
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// erreurs de compilation:
	glGetProgramiv(ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILE\n" << infoLog << std::endl;
	}
	//supprime les shaders nouvellement liés (qui ne sont donc plus nécessaire):
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shaders::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shaders::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shaders::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shaders::setMatrix(const GLchar* name, int size, int count, float* values)
{
	int uniformfLocation = glGetUniformLocation(ID, name);
	if (size == 2)
		glUniformMatrix2fv(uniformfLocation, count, GL_FALSE, values);
	if (size == 3)
		glUniformMatrix3fv(uniformfLocation, count, GL_FALSE, values);
	if (size == 4)
		glUniformMatrix4fv(uniformfLocation, count, GL_FALSE, values);
}

void Shaders::setUniform(const GLchar* name, int type, int size, float one, float two, float three, float four)
{
	int uniformLocation = glGetUniformLocation(ID, name);
	if (type == W_FLOAT)
	{
		if (size == 1)
			glUniform1f(uniformLocation, one);
		if (size == 2)
			glUniform2f(uniformLocation, one, two);
		if (size == 3)
			glUniform3f(uniformLocation, one, two, three);
		if (size == 4)
			glUniform4f(uniformLocation, one, two, three, four);
	}
	if (type == W_DOUBLE)
	{
		if (size == 1)
			glUniform1d(uniformLocation, (double)one);
		if (size == 2)
			glUniform2d(uniformLocation, (double)one, (double)two);
		if (size == 3)
			glUniform3d(uniformLocation, (double)one, (double)two, (double)three);
		if (size == 4)
			glUniform4d(uniformLocation, (double)one, (double)two, (double)three, (double)four);
	}
	if (type == W_INT)
	{
		if (size == 1)
			glUniform1i(uniformLocation, (int)one);
		if (size == 2)
			glUniform2i(uniformLocation, (int)one, (int)two);
		if (size == 3)
			glUniform3i(uniformLocation, (int)one, (int)two, (int)three);
		if (size == 4)
			glUniform4i(uniformLocation, (int)one, (int)two, (int)three, (int)four);
	}
	if (type == W_UINT)
	{
		if (size == 1)
			glUniform1ui(uniformLocation, (unsigned int)one);
		if (size == 2)
			glUniform2ui(uniformLocation, (unsigned int)one, (unsigned int)two);
		if (size == 3)
			glUniform3ui(uniformLocation, (unsigned int)one, (unsigned int)two, (unsigned int)three);
		if (size == 4)
			glUniform4ui(uniformLocation, (unsigned int)one, (unsigned int)two, (unsigned int)three, (unsigned int)four);
	}
}

void Shaders::use()
{
	glUseProgram(ID);
}

Shaders::~Shaders()
{}