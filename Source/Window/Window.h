#pragma once

#include <GLFW\glfw3.h>
#include "../Sabre3D/Sabre3Dstd.h"


class Window
{
	const unsigned int m_Width;
	const unsigned int m_Height;
	const char* m_Title;
	
#ifdef OPENGLCONTEXT
	GLFWwindow* m_Window;
#else
	HWND m_Window;
#endif
 
public:
	Window(unsigned int width, unsigned int  height, const char* title);
	~Window();
	
	

#ifdef DX12CONTEXT
	void Init(HINSTANCE hInstance, int nCmdShow);
	void Loop();
private:
	static LRESULT CALLBACK WindowProc(HWND windowHandle, UINT msg, WPARAM wparam, LPARAM lparam);
	// bool D312CompatDevice() const;
	bool InitDirect3DContext();
#else
	void Init();
	void OpenGLClear() const;
	void OpenGLUpdate() const;
	int OpenGLShouldClose() const;
#endif // 


	
	
};

 