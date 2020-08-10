#pragma once
#include <Windows.h>
#include <HPTimer.h>
#include "Colour.h"
#include <Maths.h>
#include <vector>
#include "Transform.h"
#include <Physics.h>

namespace Engine
{
	class Renderer;

	namespace Internal
	{
		class Graphics;
		class Window;
		// Internal engine helper class.
		static class EngineManager
		{

		private:
			static bool init;
			// Pointer to graphics and window class.
			static Graphics* graphics;
			static Window* window;
			// The window procedure for the game window.
			static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
		public:
			// Initializing the engine.
			static void Init(HINSTANCE hInstance, int nCmdShow);
			// Free memory before exiting the application. (not necessary)
			static void Release();
			// Bubble sort to sort renderers by priority.
			static void SortRenderersByPriority(std::vector<Engine::Renderer*>& list);
			// Cull out physics objects for performance
			static void CullPhysicsObjects(std::vector<Engine::Physics::PhysicsObject*>& objects, float maxDistance);
			static Graphics* GetGraphics();
			static Window* GetWindow();
			// Internal timer for time keeping between frames.
			static HPTimer timer;
			// Store a virtual 'camera' center.
			static Engine::Maths::Vector2D cameraPos;
			static Engine::Colour backgroundColour;

			static int exitCode;

			static bool hasQuit;
		};
	}
}