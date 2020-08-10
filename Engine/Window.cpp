#include "Window.h"

using Engine::Internal::Window;

using std::string;

Window::Window(string title, int width, int height, WNDPROC windowProc, HINSTANCE hInstance)
	:
	width(width),
	height(height)
{
	// Initializing the window with a basic style.
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = windowProc;
	windowClass.lpszClassName = title.c_str();
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect = { 0,0,width,height };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	this->handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, 1, 1, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
}

Window::~Window()
{
	
}

HWND Window::GetHandle()
{
	return handle;
}