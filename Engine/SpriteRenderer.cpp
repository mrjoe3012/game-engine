#include "SpriteRenderer.h"
#include "Actor.h"

using Engine::SpriteRenderer;
using Engine::Internal::Graphics;
using Engine::Assets::Sprite;
using Engine::Actor;

SpriteRenderer::SpriteRenderer(Actor* actor)
	:
	sprite(nullptr),
	Renderer(actor)
{

}

SpriteRenderer::~SpriteRenderer()
{
	if (sprite)
		delete sprite;
}

Sprite* SpriteRenderer::GetSprite()
{
	return sprite;
}

void SpriteRenderer::SetSprite(Sprite* sprite)
{
	if (this->sprite)
		delete this->sprite;

	this->sprite = sprite;
}

void SpriteRenderer::Render(Graphics* gfx)
{
	if (sprite)
	{
		ID2D1HwndRenderTarget* target = gfx->GetRenderTarget();

		ID2D1Bitmap* bmp = sprite->GetBitmap();

		D2D1::Matrix3x2F transform;
		target->GetTransform(&transform);

		D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(actor->transform.rotation, D2D1::Point2F(transform.dx + actor->transform.position.x, transform.dy - actor->transform.position.y));
		D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(D2D1::SizeF(this->scale.x, this->scale.y), D2D1::Point2F(transform.dx + actor->transform.position.x, transform.dy - actor->transform.position.y));

		target->SetTransform(rotation*scale);

		auto size = bmp->GetSize();

		auto sourceRect = D2D1::RectF(0, 0, bmp->GetSize().width, bmp->GetSize().height);
		auto rect = D2D1::RectF(transform.dx+actor->transform.position.x - (bmp->GetSize().width / 2.0f), transform.dy-actor->transform.position.y + (bmp->GetSize().height / 2.0f), transform.dx+actor->transform.position.x + (bmp->GetSize().width / 2.0f), transform.dy-actor->transform.position.y - (bmp->GetSize().height / 2.0f));
		target->DrawBitmap(bmp, rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, sourceRect);

		target->SetTransform(transform);
	}
}

void SpriteRenderer::Update()
{

}