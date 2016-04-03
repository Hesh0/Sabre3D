#pragma once

#include <GL/glew.h>
#include <vector>



class Mesh
{
	enum Buffers
	{
		POSITIONS_BUFFER,
		TEXTURE_COORDS,
		INDEX_BUFFER,
		NUM_BUFFERS
	};
	
	GLuint m_VAO;
	GLuint m_VBOs[NUM_BUFFERS];
	unsigned int m_NumVertices;

public:
	Mesh(float* positions, float* texCoords, int* indices, size_t posSize, size_t texCoordsSize, size_t indicesSize);
	virtual ~Mesh();
	inline GLuint getVAO() const {return m_VAO;}
	inline GLuint getVBO() const {return m_VAO;}
	inline GLuint getNumVertices() const {return m_NumVertices;}

private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other) {}
};

