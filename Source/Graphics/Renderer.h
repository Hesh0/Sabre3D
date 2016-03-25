#pragma once

#include "3D/Mesh.h"


class Renderer
{
public:
	Renderer();
	~Renderer();
	void Render(Mesh& mesh) const;

private:
	Renderer(const Renderer& other);
	void operator=(const Renderer& other) {}
};

