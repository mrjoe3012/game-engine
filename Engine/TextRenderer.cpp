#include "TextRenderer.h"
#include "Graphics.h"
#include "EngineManager.h"
#include "Window.h"
#include "Actor.h"
#include <d2d1.h>

using Engine::TextRenderer;
using Engine::Actor;
using Engine::Actor;

TextRenderer::TextRenderer(Actor* a)
	:
	Renderer(a)
{

}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::Render(Engine::Internal::Graphics* gfx)
{
	Engine::Internal::Window* window = Engine::Internal::EngineManager::GetWindow();
	ID2D1HwndRenderTarget* target = gfx->GetRenderTarget();
	IDWriteFactory* factory = gfx->GetDWriteFactory();
	HRESULT res;

	ID2D1SolidColorBrush* fillBrush = NULL;

	res = target->CreateSolidColorBrush(D2D1::ColorF(textColour.r, textColour.g, textColour.b, textColour.a), &fillBrush);

	if (res != S_OK)
		throw std::runtime_error("Could not create an ID2D1SolidColorBrush!");

	D2D1_SIZE_F renderTargetSize = target->GetSize();

	D2D1::Matrix3x2F transform;
	target->GetTransform(&transform);

	D2D1::Matrix3x2F translation = D2D1::Matrix3x2F::Translation(transform.dx + actor->transform.position.x, transform.dy - actor->transform.position.y);
	D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(-actor->transform.rotation, D2D1::Point2F(0, 0));
	D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(D2D1::SizeF(this->scale.x, this->scale.y), D2D1::Point2F(translation.dx, translation.dy));

	target->SetTransform(rotation*translation*scale);

	IDWriteTextFormat* format = NULL;

	res = factory->CreateTextFormat(
		fontFamily.c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"", //locale
		&format
	);

	if (res != S_OK)
		throw std::runtime_error("Unable to create an IDWriteTextFormat!");

	target->DrawText(
		text.c_str(),
		text.length(),
		format,
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		fillBrush
	);

	target->SetTransform(transform);

	format->Release();

}