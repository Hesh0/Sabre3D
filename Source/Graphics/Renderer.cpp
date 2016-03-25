#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Render(Mesh& mesh) const
{
	glBindVertexArray(mesh.getVAO());
	glDrawArrays(GL_TRIANGLES, 0, mesh.getNumVertices());
	glBindVertexArray(0);
}
