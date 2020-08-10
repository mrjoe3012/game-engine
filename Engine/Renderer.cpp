#include "Renderer.h"

using Engine::Renderer;
using Engine::Actor;


Renderer::Renderer(Actor* a)
	:
	Component(a),
	priority(0),
	scale(1,1)
{
}

Renderer::~Renderer()
{
	
}
