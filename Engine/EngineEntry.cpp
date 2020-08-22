#include "EngineManager.h"
#include "Window.h"
#include "Graphics.h"
#include <exception>
#include <fstream>
#include "Engine.h"
#include "EngineConfig.h"
#include "AudioManager.h"

// The engine's entry point and main loop.

using namespace Engine;
using namespace Engine::Maths;

using namespace Engine::Internal;

#define ENGINE EngineManager
#define WINDOW ENGINE::GetWindow()
#define GRAPHICS ENGINE::GetGraphics()

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Initialize the internal engine manager.
	EngineManager::Init(hInstance, nCmdShow);
	EngineManager::backgroundColour = DEFAULT_BACKGROUND_COLOUR;
	// Initialize the audio engine (xaudio)
	AudioManager::Init();

	Engine::Physics::PhysicsHandler::layerCount = PHYSICS_LAYER_COUNT;

	// Initialize physics
	Engine::Physics::PhysicsHandler::Initialize();

	// Load the initial level defined in the engine config header.
	Level::LoadLevel<INITIAL_LEVEL>();

	// Store a window message.
	MSG msg;
	msg.message = WM_NULL;

	try
	{

		while (msg.message != WM_QUIT)
		{
			// If a message is in the queue, dispatch it.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				DispatchMessage(&msg);
			}
			// Main engine loop
			else
			{
				// Cull physics object
				std::vector<Engine::Physics::PhysicsObject*> physicsObjects = Engine::Physics::PhysicsHandler::GetPhysicsObjects();

				if (EngineHelper::physicsCullingDistance != 0.0f)
				{
					EngineHelper::physicsCullingDistance = abs(EngineHelper::physicsCullingDistance);
					EngineManager::CullPhysicsObjects(physicsObjects, EngineHelper::physicsCullingDistance);
				}

				// Update the engine's internal hp timer.
				EngineManager::timer.Update();
				// Perform a physics step with the delta time.
				Physics::PhysicsHandler::PhysicsStep(EngineManager::timer.GetDeltaTime());
				// Update the level
				Level::UpdateCall();
				// Update the actors
				Actor::Update();

				if (EngineManager::hasQuit)
				{
					Level::QuitCall(EngineManager::exitCode);
					return EngineManager::exitCode;
				}
				// Store a list with pointers to the instantiated renderer components
				std::vector<Renderer*> renderers;
				// Store a list with pointers to debug draws.
				std::vector<IDebugDrawable*> debugDraws = IDebugDrawable::GetInstances();

				for (Actor* actor : Actor::GetActorList())
				{
					Renderer* r = nullptr;
					r = actor->GetComponent<Renderer>();
					if (r)
						renderers.push_back(r);

				}
				// Begin direct 2d drawing.
				GRAPHICS->GetRenderTarget()->BeginDraw();
				GRAPHICS->GetRenderTarget()->Clear(D2D1::ColorF(EngineManager::backgroundColour.r, EngineManager::backgroundColour.b, EngineManager::backgroundColour.g, EngineManager::backgroundColour.a));
				// Set the transform to the camera position.
				GRAPHICS->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(-EngineManager::cameraPos.x + (WINDOW->GetWidth() / 2.0f), EngineManager::cameraPos.y + WINDOW->GetHeight() / 2.0f));
				// Bubble sort to sort renderers by priority.
				EngineManager::SortRenderersByPriority(renderers);

				for (Renderer* r : renderers)
				{
					if (r->enabled)
						r->Render(GRAPHICS);
				}
				if (DEBUG)
				{
					for (IDebugDrawable* r : debugDraws)
					{
						if (r->drawDebug)
							r->DrawDebug(GRAPHICS);
					}
				}
				GRAPHICS->GetRenderTarget()->EndDraw();
				// Update input with null to reset the stored input information.
				Input::Update(0, 0, 0);
			}

		}

	}
	catch (std::exception e)
	{
		MessageBox(NULL, e.what(), "Unhandled Exception", MB_OK);
	}
	catch (std::runtime_error e)
	{
		MessageBox(NULL, e.what(), "Unhandled runtime error", MB_OK);
	}

	Level::QuitCall(EngineManager::exitCode);
	return EngineManager::exitCode;
}