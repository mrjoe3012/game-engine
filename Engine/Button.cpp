#include "Button.h"
#include "Actor.h"

using Engine::Button;
using std::unique_ptr;
using Engine::Maths::Rect;
using Engine::Actor;

Button::Button(Actor* a)
	:
	Component(a)
{

}

Button::~Button()
{

}

unique_ptr<Primitive> Button::GetWorldShape()
{
	return unique_ptr<Primitive>(new Rect(actor->transform.position, width, height));
}