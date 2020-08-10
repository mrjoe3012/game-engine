#include "RectRenderer.h"
#include "Actor.h"

using namespace Engine::Maths;
using Engine::RectRenderer;
using Engine::Internal::Graphics;
using Engine::Actor;

RectRenderer::RectRenderer(Actor* actor, float width, float height)
	:
	Renderer(actor),
	width(width),
	height(height)
{

}

RectRenderer::RectRenderer(Actor* actor)
	:
	RectRenderer(actor, 10,10)
{

}

RectRenderer::~RectRenderer()
{

}

void RectRenderer::Render(Graphics* gfx)
{
	ID2D1SolidColorBrush* brush = nullptr;
	ID2D1HwndRenderTarget* target = gfx->GetRenderTarget();

	HRESULT res = target->CreateSolidColorBrush(D2D1::ColorF(colour.r, colour.g, colour.b, colour.a), &brush);

	if (res != S_OK)
		throw std::runtime_error("Unable to create an ID2D1SolidColorBrush!");

	D2D1::Matrix3x2F transform;
	target->GetTransform(&transform);

	D2D1::Matrix3x2F translation = D2D1::Matrix3x2F::Translation(transform.dx+actor->transform.position.x, transform.dy-actor->transform.position.y);
	D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(actor->transform.rotation, D2D1::Point2F(0,0));
	D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(D2D1::SizeF(this->scale.x, this->scale.y), D2D1::Point2F(translation.dx, translation.dy));
	target->SetTransform(rotation*translation*scale);

	target->FillRectangle(D2D1::RectF(width / -2.0f, height / -2.0f, width / 2.0f, height / 2.0f), brush);

	target->SetTransform(transform);

	brush->Release();
}

void RectRenderer::Update()
{}
