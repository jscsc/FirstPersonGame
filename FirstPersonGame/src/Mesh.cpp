#include "Mesh.h"



Mesh::Mesh(std::vector<float> vertices, std::vector<AttribPointerConfig> configs)
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	// Buffer the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	// This is the total floats in vertex data
	unsigned int configItemsPerVertex = 0;

	for (AttribPointerConfig config : configs)
	{
		glVertexAttribPointer(config.index, config.size, config.type, config.normalized, config.stride, reinterpret_cast<void*>(config.pointerOffset));
		glEnableVertexAttribArray(config.index);
		configItemsPerVertex += config.size;
	}
	glBindVertexArray(0);

	_numOfVertices = vertices.size() / configItemsPerVertex;
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
}

void Mesh::draw()
{
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, _numOfVertices);
}
