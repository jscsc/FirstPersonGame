#include "Mesh.h"



Mesh::Mesh(std::vector<float> vertices)
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	// Buffer the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);


	// TODO: Generalize fields and functions 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0); 			  
	glBindVertexArray(0);
	// TODO: figure out from params
	_numOfVertices = 3;
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
