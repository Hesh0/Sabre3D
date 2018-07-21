#include "OpenGLRenderer.h"



OpenGLRenderer::OpenGLRenderer() {}

OpenGLRenderer::~OpenGLRenderer() {}

void OpenGLRenderer::Render(Mesh& mesh) const
{
	glBindVertexArray(mesh.getVAO());
	// glDrawElements(GL_TRIANGLES, mesh.getNumVertices(), GL_UNSIGNED_INT, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, mesh.getNumVertices());
	glBindVertexArray(0);
}
