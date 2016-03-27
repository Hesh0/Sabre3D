#pragma once

#include <GL/glew.h>
#include <vector>



class Mesh
{
	GLuint m_VAO;
	GLuint m_VBO;
	unsigned int m_NumVertices;

public:
	Mesh(float* positions, size_t size);
	virtual ~Mesh();
	inline GLuint getVAO() const {return m_VAO;}
	inline GLuint getVBO() const {return m_VAO;}
	inline GLuint getNumVertices() const {return m_NumVertices;}

private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other) {}
};

