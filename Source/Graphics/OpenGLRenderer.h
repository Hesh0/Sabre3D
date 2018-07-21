#pragma once

#include "3D/Mesh.h"


class OpenGLRenderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();
	void Render(Mesh& mesh) const;

private:
	OpenGLRenderer(const OpenGLRenderer& other);
	void operator=(const OpenGLRenderer& other) {}
};

