#include "Renderer.h"



Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Render(Mesh& mesh) const
{
	glBindVertexArray(mesh.getVAO());
	glDrawElements(GL_TRIANGLES, mesh.getNumVertices(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
