#include "EllipseRenderer.h"
#include "Graphics.h"
#include "Actor.h"

using Engine::EllipseRenderer;
using Engine::Actor;
using Engine::Internal::Graphics;

EllipseRenderer::EllipseRenderer(Actor* actor)
	:
	EllipseRenderer(actor,10,10)
{

}

EllipseRenderer::EllipseRenderer(Actor* actor, float radiusX, float radiusY)
	:
	Renderer(actor),
	radiusX(radiusX),
	radiusY(radiusY)
{

}

EllipseRenderer::~EllipseRenderer()
{

}

void EllipseRenderer::Render(Engine::Internal::Graphics* gfx)
{

	ID2D1HwndRenderTarget* target = gfx->GetRenderTarget();
	ID2D1SolidColorBrush* brush = NULL;

	D2D1::Matrix3x2F transform;
	target->GetTransform(&transform);

	D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(-actor->transform.rotation, D2D1::Point2F(transform.dx+actor->transform.position.x, transform.dy-actor->transform.position.y));

	target->CreateSolidColorBrush(D2D1::ColorF(colour.r, colour.g, colour.b, colour.a), &brush);

	target->SetTransform(rotation);

	target->FillEllipse(D2D1::Ellipse(D2D1::Point2F(transform.dx+actor->transform.position.x, transform.dy-actor->transform.position.y), radiusX, radiusY), brush);

	target->SetTransform(transform);

	brush->Release();
}
