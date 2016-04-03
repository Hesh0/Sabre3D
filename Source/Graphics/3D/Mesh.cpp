#include <stdio.h>

#include "Mesh.h"



Mesh::Mesh(float * positions, float * texCoords, int * indices, size_t posSize, size_t texCoordsSize, size_t indicesSize)
	: m_NumVertices{posSize / 3}
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(NUM_BUFFERS, m_VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[POSITIONS_BUFFER]);
	
	// make VBO 1 have the position data for the mesh.
	glBufferData(GL_ARRAY_BUFFER, posSize * sizeof(float), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	// make VBO 2 have the texture coordinates data.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[TEXTURE_COORDS]);
	glBufferData(GL_ARRAY_BUFFER, texCoordsSize * sizeof(float), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(1);

	// make VBO 3 have the index data.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBOs[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(int), indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(NUM_BUFFERS, m_VBOs);
}
