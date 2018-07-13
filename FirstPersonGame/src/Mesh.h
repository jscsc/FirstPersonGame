#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class Mesh
{

private:

	GLuint _VAO = 0;
	GLuint _VBO = 0;

	GLint _numOfVertices;

public:

	Mesh(std::vector<float> vertices);

	virtual ~Mesh();

	void draw();
};

