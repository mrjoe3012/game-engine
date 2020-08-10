#pragma once
#include <Windows.h>
#include <string>

namespace Engine
{
	namespace Internal
	{
		// Used to create a window. Wraps the win32 methods for creating a window and stores its handle.
		class Window
		{
		private:
			// handle of the window
			HWND handle;
			// the size of the window
			int width, height;

		public:
			Window(std::string title, int width, int height, WNDPROC windowProc, HINSTANCE hInstance);
			~Window();

			HWND GetHandle();

			int GetWidth() { return width; }
			int GetHeight() { return height; }

		};

	}
}