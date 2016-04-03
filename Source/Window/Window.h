#pragma once

#include <GLFW\glfw3.h>


class Window
{
	const unsigned int m_Width;
	const unsigned int m_Height;
	const char* m_Title;
	GLFWwindow* m_Window;
 
public:
	Window(unsigned int width, unsigned int  height, const char* title);
	~Window();
	void Init();
	void Clear() const;
	void Update() const;
	int ShouldClose() const;
};

 