#pragma once 
#include <d2d1.h>
#include <dwrite.h>
#include <Windows.h>

namespace Engine
{
	
	namespace Internal
	{
		// A class that encapsulates direct 2d interfaces.
		class Graphics
		{
		private:
			ID2D1Factory* factory;
			ID2D1HwndRenderTarget* target;
			IDWriteFactory* dWriteFactory;
		public:
			Graphics(HWND windowHandle);
			~Graphics();

			ID2D1HwndRenderTarget* GetRenderTarget();

			IDWriteFactory* GetDWriteFactory();
			ID2D1Factory* GetD2D1Factory();
		};

	}

}