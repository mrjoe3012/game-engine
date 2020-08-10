#include "Graphics.h"
#include <stdexcept>

using Engine::Internal::Graphics;

Graphics::Graphics(HWND handle)
	:
	factory(NULL),
	target(NULL)
{
	// Direct2d initialization.
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK)
		throw std::runtime_error("Unable to create a D2D1Factory!");

	RECT rect;
	GetClientRect(handle, &rect);

	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(handle, D2D1::SizeU(rect.right, rect.bottom)), &target);
	if (res != S_OK)
		throw std::runtime_error("Unable to create a D2D1RenderTarget!");

	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&dWriteFactory));

	if (res != S_OK)
		throw std::runtime_error("Unable to create a DWrite factory!");
}

Graphics::~Graphics()
{
	// Releasing resources.
	factory->Release();
	dWriteFactory->Release();
	target->Release();
}

ID2D1HwndRenderTarget* Graphics::GetRenderTarget()
{
	return target;
}

ID2D1Factory* Graphics::GetD2D1Factory()
{
	return factory;
}

IDWriteFactory* Graphics::GetDWriteFactory()
{
	return dWriteFactory;
}