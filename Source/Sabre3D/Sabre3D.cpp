#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "../Shader Handling/Shader.h"
#include "../Window/Window.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/3D/Mesh.h"
#include "../Graphics/Texture.h"

 

int main()
{
	Window window(1000, 1000 / 14 * 9, "Random");
	Renderer renderer;
	window.Init();
	GLenum shaderTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	Shader triangle(R"(Source\Shaders\Triangle)", 2, shaderTypes);
	float points[9] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	Mesh triangleMesh(points, sizeof points / sizeof points[0]);
	Texture tex(R"(Resources\dirtTexture.jpg)");
	
	triangle.CreateProgram();

	while (!window.ShouldClose()) 
	{
		window.Clear();
		triangle.Bind();
		renderer.Render(triangleMesh);
		window.Update();
	}
	_CrtDumpMemoryLeaks(); // this is supposed to report any memory leaks

	return 0;
} 