#include <GL/glew.h> 
#include "../Sabre3D/Sabre3Dstd.h"
#include "Window.h"



Window::Window(unsigned int width, unsigned int  height, const char* title)
	: m_Width{width}, m_Height{height}, m_Title{title}, m_Window{nullptr}
{}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Init() 
{
	if (!glfwInit() == GL_TRUE)
		S3D_FATAL("Failed to initialize GLFW");
		
	// set some hints before creating the window.
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
	// if window failed to create terminate.
	if (!m_Window)
	{
		glfwTerminate();
		S3D_FATAL("Error initializing window");
	}
	glfwMakeContextCurrent(m_Window);
	glewExperimental = GL_TRUE;
	
	if (glewInit() != GLEW_OK)
		S3D_FATAL("Error Initializing glew.");
}

void Window::Clear() const
{
	const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	// glClearBufferfv(GL_COLOR, 0, red);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER);
}

void Window::Update() const
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

int Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}