#include "EngineManager.h"
#include "Graphics.h"
#include "Window.h"
#include "Actor.h"
#include "Input.h"
#include "EngineConfig.h"

using namespace Engine::Internal;
using Engine::Input;

bool EngineManager::init = false;
bool EngineManager::hasQuit = false;

Window* EngineManager::window = nullptr;
Graphics* EngineManager::graphics = nullptr;

HPTimer EngineManager::timer = HPTimer();

Engine::Maths::Vector2D EngineManager::cameraPos = Engine::Maths::Vector2D();

Engine::Colour EngineManager::backgroundColour = Engine::Colour::white;

int EngineManager::exitCode = 0;

void EngineManager::Init(HINSTANCE hInstance, int nCmdShow)
{
	if (!init)
	{
		window = new Window(std::string(WINDOW_TITLE), WINDOW_WIDTH, WINDOW_HEIGHT, EngineManager::WindowProc, hInstance);
		ShowWindow(window->GetHandle(), nCmdShow);
		graphics = new Graphics(window->GetHandle());
		init = true;
	}
	else
	{
		throw std::runtime_error("The engine handler class has already been initialized.");
	}
}

Window* EngineManager::GetWindow()
{
	if (!init)
		throw std::runtime_error("The engine handler class has not yet been initialized.");

	return window;
}

Graphics* EngineManager::GetGraphics()
{
	if (!init)
		throw std::runtime_error("The engine handler class has not yet been initialized.");

	return graphics;
}

LRESULT CALLBACK EngineManager::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

	switch (msg)
	{
	// Process input messages within the engine.
	case(WM_DESTROY):
		PostQuitMessage(0);
		break;
	case(WM_KEYDOWN):
	case(WM_KEYUP):
	case(WM_RBUTTONDOWN):
	case(WM_RBUTTONUP):
	case(WM_MBUTTONDOWN):
	case(WM_MBUTTONUP):
	case(WM_LBUTTONDOWN):
	case(WM_LBUTTONUP):
		Input::Update(msg, wparam, lparam);
		break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}

void EngineManager::Release()
{

	auto actorList = Actor::GetActorList();

	for (size_t i = 0; i < actorList.size(); i++)
	{
		delete (actorList[i]);
	}

	delete graphics;
	delete window;
}

void EngineManager::SortRenderersByPriority(std::vector<Engine::Renderer*>& list)
{
	// Standard bubble sort implementation.
	int n = list.size();

	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place  
		for (j = 0; j < n - i - 1; j++)
			if (list[j]->priority > list[j + 1]->priority)
			{
				Renderer* r1 = list[j];
				Renderer* r2 = list[j + 1];
				list[j + 1] = r1;
				list[j] = r2;
			}
}

void EngineManager::CullPhysicsObjects(std::vector<Engine::Physics::PhysicsObject*>& objects, float maxDistance)
{
	float sqrMaxDistance = powf(maxDistance, 2.0f);
	for (auto obj : objects)
	{
		float sqrDistance = (obj->GetPosition() - cameraPos).SquareMagnitude();

		obj->enabled = sqrDistance <= sqrMaxDistance;
	}
}