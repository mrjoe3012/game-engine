#pragma once

#include <wincodec.h>
#include <d2d1.h>
#include <string>

namespace Engine
{
	namespace Assets
	{
		// Used to store an image from disk.
		class Sprite
		{
		private:
			// The bitmap loaded from the file
			ID2D1Bitmap* bitmap;
			// Reads the bitmap from the path
			void ReadImage();
			// The path to the image
			std::wstring path;

		public:
			Sprite(std::wstring filename);
			// Copy constructor
			Sprite(Sprite&);
			Sprite();
			~Sprite();
			// Changes the path and updates the bitmap
			void SetPath(std::wstring path);
			std::wstring GetPath();

			ID2D1Bitmap* GetBitmap();

			// Signals to the instance that the sprite is shared and that it should not be deleted as multiple objects depend on it.
			bool shared = false; 

			void operator delete(void* ptr);
		};

	}
}