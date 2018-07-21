


#include "../Sabre3D/Sabre3Dstd.h"

#include "Window.h"
#include "../Utilities/Utilities.h"




Window::Window(unsigned int width, unsigned int  height, const char* title)
	: m_Width{width}, m_Height{height}, m_Title{title}, m_Window{nullptr}
{}

Window::~Window()
{
#if defined(DX12CONTEXT)
#else
	glfwDestroyWindow(m_Window);
	glfwTerminate();
#endif
}

#ifdef DX12CONTEXT
void Window::Init(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX windowClass = {0};
	LPCTSTR winTitle(m_Title);
	
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW; // if window size adjusted redraw
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance; // gets the HINSTANCE
	windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW); // standard arrow cursor.
	windowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = "Sabre3D";
	windowClass.hIconSm = nullptr;
	RegisterClassEx(&windowClass);

	m_Window = CreateWindow(windowClass.lpszClassName, winTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height, nullptr, nullptr, hInstance, nullptr);
	if (!m_Window) 
	{
		std::string errMsg = Utilities::GetLastErrorAsString();
		S3D_FATAL("Failed to create Window" + errMsg);
	}
	InitDirect3DContext();
}

void Window::Loop()
{
	ShowWindow(m_Window, SW_SHOWNORMAL);
	UpdateWindow(m_Window);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

LRESULT CALLBACK Window::WindowProc(HWND windowHandle, UINT msg, WPARAM wparam, LPARAM lparam) 
{
	switch (msg)
	{
	case WM_PAINT:
		// Code to deal with drawing the client area
		break;
	case WM_LBUTTONDOWN:
		// Code to deal with the left mouse button being pressed
		break;
	case WM_LBUTTONUP:
		// Code to deal with the left mouse button being released
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		// Code to deal with a window being destroyed
		break;
	default:
		// Code to handle any other messages
		break;
	}
	return DefWindowProc(windowHandle, msg, wparam, lparam);
}

bool Window::InitDirect3DContext()
{
	ID3D12Device* device;
	HRESULT hr;
	IDXGIFactory1* dxgiFactory;

	hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
	if (FAILED(hr))
		return false;
	IDXGIAdapter1* adapter;
	int adapterIndex = 0;
	bool adapterFound = false;

	while (dxgiFactory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			++adapterIndex;
			continue;
		}
		hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr);
		if (SUCCEEDED(hr))
		{
			adapterFound = true;
			break;
		}
		++adapterIndex;
	}

	if (adapterFound)
	{
		
		hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
	}
	
	if (FAILED(hr))
	{
		S3D_ERROR("Could not intialize Direct3D 12");
		return false;
	}
}


#else
void Window::Init()
{
	S3D_LOG("INFO", "OpenGLInit called");
	if (!glfwInit() == GL_TRUE)
		S3D_FATAL("Failed to initialize GLFW");

	// set some hints before creating the window.
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // set it to a 4.3 profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // profile with all deprecated funtionality removed.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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

void Window::OpenGLClear() const
{
	const GLfloat red[] = { 0.5f, 0.0f, 0.2f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, red);
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER);
}

void Window::OpenGLUpdate() const
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

int Window::OpenGLShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}


#endif
