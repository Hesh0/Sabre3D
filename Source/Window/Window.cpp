#include <GL/glew.h> 
#define GLFW_INCLUDE_GLU
#include "Window.h"
#include <stdio.h>
#include <stdlib.h>



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
	{
		fprintf(stderr, "Failed to initialize GLFW.");
		exit(EXIT_FAILURE);
	}

	// set some hints before creating the window.
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
	// if window failed to create terminate.
	if (!m_Window)
	{
		fprintf(stderr, "Error initializing window.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_Window);
	glewExperimental = GL_TRUE;
	
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Error Initializing glew.");
		exit(EXIT_FAILURE);
	}
}

void Window::Clear() const
{
	const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, red);
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER);
}

void Window::Update() const
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}