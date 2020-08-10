#pragma once
#include <Windows.h>
#include "KeyCodes.h"
#include <bitset>
#include <Maths.h>

namespace Engine
{
	// Holds information about key presses and mouse states.
	static class Input
	{

	private:
		static std::bitset<COUNT_KEYCODES> keysReleasedThisFrame;
		static std::bitset<COUNT_KEYCODES> input;

		static float lastLmbDown, lastRmbDown, lastMmbDown;

		static void HandleClick(Vector2D point, KeyCode button);
	public:
		// Returns true if a certain key is down.
		static bool GetKeyHeld(std::bitset<COUNT_KEYCODES>);
		// Returns true if a certain key was released on that frame.
		static bool GetKeyReleased(std::bitset<COUNT_KEYCODES>);
		// Returns true if any key is down
		static bool GetAnyKey();
		// Returns true if any key was released on this frame.
		static bool GetAnyKeyReleased();

		// Called from the window procedure and updates the input information.
		static void Update(UINT,WPARAM,LPARAM);

		// Returns the mouse position on the window.
		static Maths::Vector2D GetMousePositionOnScreen();
		// Returns the mouse position as a position in the world.
		static Maths::Vector2D GetMousePositionInWorld();
	};
}