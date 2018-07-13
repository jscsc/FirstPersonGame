#include "Shader.h"
#include <iostream>

Shader::Shader(std::string vertexSrc, std::string fragmentSrc)
{
	// COMPILE VERTEX SHADER
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	// Second arg is number of strings you can pass it, 4th arg is an array of those string lengths.
	const char* vertShaderSource_cstr = vertexSrc.c_str();
	glShaderSource(vertexShaderID, 1, &vertShaderSource_cstr, nullptr);
	glCompileShader(vertexShaderID);

	GLint vertexCompileSuccess = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vertexCompileSuccess);
	if (!vertexCompileSuccess)
	{
		char log[512];
		glGetShaderInfoLog(vertexShaderID, 512, NULL, log);
		std::cerr << "vertex shader compile fail" << log << std::endl;
	}

	// COMPILE FRAGMENT SHADER
	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragShaderSource_cstr = fragmentSrc.c_str();
	glShaderSource(fragShaderID, 1, &fragShaderSource_cstr, nullptr);
	glCompileShader(fragShaderID);

	// Check success of fragment shader compilation
	GLint fragShaderSuccess = 0;
	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &fragShaderSuccess);
	if (!fragShaderSuccess)
	{
		char log[512];
		glGetShaderInfoLog(fragShaderID, 512, nullptr, log);
		std::cerr << "frag shader failed to compile\n" << log << std::endl;
	}

	// LINK SHADERS INTO SHADER PROGRAM
	_shaderProgramID = glCreateProgram();
	glAttachShader(_shaderProgramID, vertexShaderID);
	glAttachShader(_shaderProgramID, fragShaderID);
	glLinkProgram(_shaderProgramID);

	// Test linking of shader program
	GLint shaderLinkSuccess = 0;
	glGetProgramiv(_shaderProgramID, GL_LINK_STATUS, &shaderLinkSuccess);
	if (!shaderLinkSuccess)
	{
		char infoLog[512]; // Not recycling logs for example readability
		glGetProgramInfoLog(_shaderProgramID, 512, nullptr, infoLog);
		std::cerr << "failed to link shaders in shader program\n" << infoLog << std::endl;
	}

	// Delete shader objects since we've already linked them into the shader program
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragShaderID);

	// Shader program is ready to be used!
}

Shader::~Shader()
{
	glDeleteProgram(_shaderProgramID);
}

void Shader::bind(bool activate /*= true*/)
{
	if (activate)
	{
		glUseProgram(_shaderProgramID);
	}
	else
	{
		glUseProgram(0);
	}
}
