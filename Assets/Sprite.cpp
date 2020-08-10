#include "Sprite.h"
#include <EngineManager.h>
#include <Graphics.h>

using std::wstring;
using Engine::Assets::Sprite;
using Engine::Internal::EngineManager;

Sprite::Sprite()
	:
	path(L""),
	bitmap(NULL)
{

}

Sprite::Sprite(Sprite& s)
{
	// Copy over the path
	this->path = s.path;
	// If s has a bitmap loaded, copy the bitmap info to this instance.
	if (s.bitmap)
	{
		float dpix, dpiy;
		auto size = s.bitmap->GetSize();
		s.bitmap->GetDpi(&dpix, &dpiy);
		HRESULT res;
		res = EngineManager::GetGraphics()->GetRenderTarget()->CreateBitmap(D2D1::SizeU(size.width, size.height), D2D1::BitmapProperties(s.bitmap->GetPixelFormat(), dpix, dpiy), &bitmap);

		if (res != S_OK)
			throw std::runtime_error("Unable to create an ID2D1Bitmap.");

		res = bitmap->CopyFromBitmap(&D2D1::Point2U(0,0), s.bitmap, &D2D1::RectU(0,0,size.width, size.height));

	}
}

Sprite::Sprite(wstring filename)
	:
	path(filename),
	bitmap(NULL)
{
	// Load the bitmap from the provided filename
	ReadImage();
}

Sprite::~Sprite()
{
	if (bitmap && !shared)
		bitmap->Release();
}

void Sprite::ReadImage()
{

	HRESULT res;
	// Create a factory to create a decoder.
	IWICImagingFactory* factory = NULL;

	res = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&factory);

	if (res != S_OK)
		throw std::runtime_error("Unable to create an IWICImagingFactory!");
	// Use the decoder to get a frame.
	IWICBitmapDecoder* decoder = NULL;

	res = factory->CreateDecoderFromFilename(path.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);

	if (res != S_OK)
		throw std::runtime_error("Unable to create an IWICBitmapDecoder! Perhaps the path is incorrect.");
	// Use the frame with the converter to get an ID2D1Bitmap
	IWICBitmapFrameDecode* frame = NULL;
	res = decoder->GetFrame(0, &frame);

	if (res != S_OK)
		throw std::runtime_error("Unable to get a decoded frame from the IWICBitmapDecoder!");

	IWICFormatConverter* converter = NULL;
	res = factory->CreateFormatConverter(&converter);
	
	if (res != S_OK)
		throw std::runtime_error("Unable to create an IWICFormatConverter!");


	res = converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);

	if (res != S_OK)
		throw std::runtime_error("Unable intialize an IWICFormatConverter!");

	unsigned int width = 0, height = 0;

	res = converter->GetSize(&width, &height);

	if (res != S_OK)
		throw std::runtime_error("Unable to get size of bitmap from the IWICFormatConverter!");
	// Create the bitmap with the render target.
	res = EngineManager::GetGraphics()->GetRenderTarget()->CreateBitmapFromWicBitmap(converter, NULL, &bitmap);

	if (res != S_OK)
		throw std::runtime_error("Unable to create an ID2D1Bitmap from the IWICBitmap.");

	// Free memory
	factory->Release();
	decoder->Release();
	frame->Release();
	converter->Release();

}

ID2D1Bitmap* Sprite::GetBitmap()
{
	if (!bitmap)
		ReadImage();

	return bitmap;
}

void Sprite::SetPath(wstring path)
{

	if (bitmap)
		bitmap->Release();


	this->path = path;
	ReadImage();
}

wstring Sprite::GetPath()
{
	return this->path;
}

void Sprite::operator delete(void* ptr)
{
	Sprite* s = (Sprite*)ptr;

	if(!s->shared)
		free(ptr);
}