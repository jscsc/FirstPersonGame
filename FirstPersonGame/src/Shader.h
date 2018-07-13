#pragma once

#include <string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Shader
{

private:

	GLuint _shaderProgramID;

public:

	Shader(std::string vertexSrc, std::string fragmentSrc);

	~Shader();

	void bind(bool activate = true);

};