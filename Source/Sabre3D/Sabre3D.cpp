
#include "Sabre3Dstd.h"
#include "../Shader Handling/Shader.h"
#include "../Window/Window.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/3D/Mesh.h"
#include "../Graphics/Texture.h"
#include "../Math/S3DVectors/Vector.h"



int main()
{
	// places _CrtDumpMemoryLeaks() at every exit point in the program.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Logger::Init();

	Window window(1000, 1000 / 14 * 9, "Random");
	Renderer renderer;
	
	window.Init();
	
	std::string msg("OpenGL vendor: ");
	S3D_LOG("INFO", msg + reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	msg = "Renderer: ";
	S3D_LOG("INFO", msg + reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

	GLenum shaderTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	std::string file(R"(Source\Shaders\Triangle)");
	Shader triangle(file, 2, shaderTypes);
	float points[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, +0.5f, 0.0f,
		+0.5f, +0.5f, 0.0f,
		
		+0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		+0.5f, +0.5f, 0.0f
	};
	
	float texCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	Mesh triangleMesh(points, texCoords, indices, _arrlen(points), _arrlen(texCoords), _arrlen(indices));
	Texture tex(R"(Resources\dirtTexture.jpg)");
	
	triangle.CreateProgram();

	while (!window.ShouldClose()) 
	{
		window.Clear();
		triangle.Bind();
		tex.Bind(0);
		renderer.Render(triangleMesh);
		window.Update();
	}
	Logger::Destroy();
	
	_CrtDumpMemoryLeaks(); // this is supposed to report any memory leaks

	return 0;
} 