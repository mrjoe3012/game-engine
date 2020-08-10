#define USING_ENGINE using namespace Engine; using namespace Engine::Events; using namespace Engine::Assets; using namespace Engine::Maths;

#pragma once
#include "Actor.h"
#include "Level.h"
#include "GameScript.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include "LineCollider.h"
#include "Input.h"
#include "AnimationSet.h"
#include "Colour.h"
#include <string>
#include <Matrix.h>

namespace Engine
{
	// Helper class for common engine functionality.
	// Wraps some methods from the internal EngineManager.
	static class EngineHelper
	{
	public:
		// The engine's version.
		static std::string engineVersion;
		// The game's version.
		static std::string gameVersion;
		// Time elapsed since last frame in seconds.
		static double GetDeltaTime();
		// Time elapsed since game startup
		static float GetTime();

		// Set and get the camera's position
		static void SetCameraPos(Maths::Vector2D);
		static Maths::Vector2D GetCameraPos();

		static void SetBackgroundColour(Colour c);
		static Colour GetBackgroundColour();

		// Terminate the program
		static void Quit(int code);

		// Restore the window to its original size
		static void ResetWindow();
		// Get physics timescale
		static float GetTimeScale();
		// Set physics timescale
		static void SetTimeScale(float ts);

		static float physicsCullingDistance;

		static Engine::Maths::Matrix<bool>& GetPhysicsLayerMatrix();
		static void SetPhysicsLayer(unsigned int i, unsigned int j, bool value);
	};
}