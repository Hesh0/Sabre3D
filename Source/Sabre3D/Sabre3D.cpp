#include "Sabre3Dstd.h"
#include "../Shader Handling/Shader.h"
#include "../Window/Window.h"
#include "../Graphics/OpenGLRenderer.h"
#include "../Graphics/3D/Mesh.h"
#include "../Graphics/Texture.h"
#include "../Math/S3DVectors/Vector.h"
#include "../Math/Mat4.h"


template <unsigned int N> struct Fib
{
	enum
	{
		Val = Fib<N - 1>::Val + Fib<N - 2>::Val
	};
};

template <> struct Fib <0> { enum { Val = 0 }; };
template <> struct Fib <1> { enum { Val = 1 }; };

#define TFib(n) Fib<(n)>::Val


#if defined(OPENGLCONTEXT)
int main()
{
	
#if 0
	// printf("PI is %f\n", PI);

	std::cout << TFib(45) << std::endl;
	
	Mat4 mat1 = S3DMath::IdentityMatrix();
	/*printf("Should be [1.00, 0.00, 0.00, 0.00]" 
		   "		  [0.00, 1.00, 0.00, 0.00]" 
		   "		  [0.00, 0.00, 1.00, 0.00]"
		   "		  [0.00, 0.00, 0.00, 1.00] is "); */
	std::cout << mat1 << std::endl; 
	Mat4 mat2 = S3DMath::ScalingMatrix(2, 2, 2);
	/*printf("Should be [2.00, 0.00, 0.00, 0.00]"
		   "		  [0.00, 2.00, 0.00, 0.00] "
		   "		  [0.00, 0.00, 2.00, 0.00]"
		   "		  [0.00, 0.00, 0.00, 1.00] is "); */
	std::cout << mat2 << std::endl;
	/*printf("Should be [1.00, 0.00, 0.00, 2.00]"
			"			[0.00, 1.00, 0.00, 2.00]"
			"			[0.00, 0.00, 1.00, 2.00]"
			"			[0.00, 0.00, 0.00, 1.00] is "); */
	Mat4 mat3 = S3DMath::TranslationMatrix(2, 2, 2);
	std::cout << mat3 << std::endl;
	float mat0[] = {
		2, 3, 4, 4,
		7, 4, 3, 9,
		1, 4, 5, 10,
		11, 45, 17, 21
	};
	/*printf("Should be [2.00, 3.00, 4.00, 4.00]"
		   "		  [7.00, 4.00, 3.00, 9.00] "
		   "		  [1.00, 4.00, 5.00, 10.00]"
	
		   "		  [11.00, 45.00, 17.00, 21.00] is ");*/
	

	Mat4 mat40 = S3DMath::ArbitraryMatrix(&mat0);
	std::cout << mat40 << std::endl;
	printf("mat1 * mat40 ");
	mat1 *= mat40;
	std::cout << "should be " << mat40 << "is " << mat1 << std::endl;
	Vec4 vec(1.0f, 2.0f, 3.0f);
	printf("Should be [1.00, 2.00, 3.00, 1.00] is ");
	std::cout << vec << std::endl;
	printf("After multiplication by identity matrix ");
	printf("Should be [1.00, 2.00, 3.00, 1.00] is ");
	vec = S3DMath::IdentityMatrix() * vec;
	std::cout << vec << std::endl;
	printf("Scaling Matrix with vector test:\n");
	printf("Should be [2, 4, 6, 1] is ");
	vec = S3DMath::ScalingMatrix(2, 2, 2) * vec;
	std::cout << vec << std::endl;


	Mat4 rotation = S3DMath::RotateXAxis(90);
	Mat4 rotation1 = S3DMath::RotateYAxis(90);
	Mat4 rotation2 = S3DMath::RotateZAxis(90);
	Mat4 rotation3 = S3DMath::ArbitraryRotation(Vec3(1, 0, 0), 90);
	Mat4 scale = S3DMath::ArbitraryScaleMatrix(Vec3(1, 0, 0), 2);
	Mat4 projection = S3DMath::OrthoProjectionMat(Vec3(1, 0, 0));

	printf("Rotation matrices:\n\n");

	std::cout << rotation << std::endl;
	std::cout << rotation1 << std::endl;
	std::cout << rotation2 << std::endl;
	std::cout << rotation3 << std::endl;
	std::cout << scale << std::endl;
	std::cout << projection << std::endl;


	//float pi = acos(-1.0f);

	float r = S3DMath::PI / 4.0f;
	printf("r is %f\n", r);
	printf("cos90 = %f, cos0 = %f\n", -std::cos(r), std::cos(0));
	printf("sin90 = %.2f sin0 = %f\n", std::sin((90.0f / 180) * S3DMath::PI), std::sin(0));

	Vec2 v1(2, 3);
	Vec3 v2(2, 3, 4);
	Vec4 v3(2, 3, 4, 5);

	printf("%s, %s, %s\n", v1.ToString(), v2.ToString(), v3.ToString()); 
#endif


	// places _CrtDumpMemoryLeaks() at every exit point in the program.
 	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Logger::Init();

	Window window(1000, 1000 / 14 * 9, "Random");
	window.Init();
	OpenGLRenderer renderer;


	GLint major, minor;
	std::string msg("OpenGL vendor: ");
	S3D_LOG("INFO", msg + reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	msg = "Renderer: ";
	S3D_LOG("INFO", msg + reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	msg = "OpenGL Version: ";
	S3D_LOG("INFO", msg + std::to_string(major) + "."+ std::to_string(minor));
	msg = "GLSL Version: ";
	S3D_LOG("INFO", msg + reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION))); 

	GLenum triShaderTypes[] = {GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_FRAGMENT_SHADER};
	// GLenum shaderTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	// Shader cube(R"(Source\Shaders\Cube)", 2, shaderTypes);
	Shader triShader(R"(Source\Shaders\Triangle)", triShaderTypes, _arrlen(triShaderTypes));

	float points[] = {
		+0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		+0.5f, +0.5f, 0.0f
	};
	
	
	/*float points[18] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, +0.5f, 0.0f,
		+0.5f, +0.5f, 0.0f,
		
		+0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		+0.5f, +0.5f, 0.0f
	};
	
	float texCoords[8] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	int indices[6] = {
		0, 1, 2,
		2, 3, 0
	}; */

	/* float points[] = {
		-0.25f,-0.25f,-0.25f, // triangle 1 : begin
		-0.25f,-0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f, // triangle 1 : end
		 0.25f, 0.25f,-0.25f, // triangle 2 : begin
		-0.25f,-0.25f,-0.25f,
		-0.25f, 0.25f,-0.25f, // triangle 2 : end
		 0.25f,-0.25f, 0.25f,
		-0.25f,-0.25f,-0.25f,
		 0.25f,-0.25f,-0.25f,
		 0.25f, 0.25f,-0.25f,
		 0.25f,-0.25f,-0.25f,
		-0.25f,-0.25f,-0.25f,
		-0.25f,-0.25f,-0.25f,
		-0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f,-0.25f,
		 0.25f,-0.25f, 0.25f,
		-0.25f,-0.25f, 0.25f,
		-0.25f,-0.25f,-0.25f,
		-0.25f, 0.25f, 0.25f,
		-0.25f,-0.25f, 0.25f,
		 0.25f,-0.25f, 0.25f,
		 0.25f, 0.25f, 0.25f,
		 0.25f,-0.25f,-0.25f,
		 0.25f, 0.25f,-0.25f,
		 0.25f,-0.25f,-0.25f,
		 0.25f, 0.25f, 0.25f,
		 0.25f,-0.25f, 0.25f,
		 0.25f, 0.25f, 0.25f,
		 0.25f, 0.25f,-0.25f,
		-0.25f, 0.25f,-0.25f,
		 0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f,-0.25f,
		-0.25f, 0.25f, 0.25f,
		 0.25f, 0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f,
		 0.25f,-0.25f, 0.25f
	}; */



	// Mesh mesh(points, texCoords, indices, _arrlen(points), _arrlen(texCoords), _arrlen(indices));
	// Mesh cubem(points, _arrlen(points)); 
	Mesh triangle(points, _arrlen(points));
	
	

	//Texture tex(R"(Resources\dirtTexture.jpg)");
	
	// shader.CreateProgram();
	// cube.CreateProgram();
	triShader.CreateProgram();
	

	 while (!window.OpenGLShouldClose()) 
	{
		window.OpenGLClear();
		// shader.Bind();
		// cube.Bind();
		triShader.Bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
		
		// tex.Bind(0);
		renderer.Render(triangle);
		window.OpenGLUpdate();
	} 
	
	_CrtDumpMemoryLeaks(); // This is supposed to report any memory leaks to stderr before termination.
	Logger::Destroy();

	return 0;
} 
#endif

#if defined(DX12CONTEXT)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Logger::Init();
	S3D_LOG("INFO", "Shit Started");
	Window window(1000, 1000 / 14 * 9, "Random");
	window.Init(hInstance, nCmdShow);

	while (true)
		window.Loop();
	
	Logger::Destroy();

	return 0;

}
#endif