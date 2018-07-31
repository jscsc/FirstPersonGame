#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

struct AttribPointerConfig
{
	// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
	GLuint index;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	GLvoid * pointerOffset;
};

class Mesh
{

private:

	GLuint _VAO = 0;
	GLuint _VBO = 0;

	GLint _numOfVertices;

public:

	Mesh(std::vector<float> vertices, std::vector<AttribPointerConfig> configs);

	virtual ~Mesh();

	void draw();
};

