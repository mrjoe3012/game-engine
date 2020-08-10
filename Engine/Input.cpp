#include "Input.h"
#include "EngineManager.h"
#include "Engine.h"
#include "Window.h"
#include "IClickable.h"

using Engine::Input;
using std::bitset;
using Engine::Maths::Vector2D;
using std::vector;
using Engine::Internal::IClickable;
using std::unique_ptr;
using Engine::Maths::Primitive;

bitset<COUNT_KEYCODES> Input::keysReleasedThisFrame = bitset<COUNT_KEYCODES>();

bitset<COUNT_KEYCODES> Input::input = bitset<COUNT_KEYCODES>();

float Input::lastLmbDown = 0.0f, Input::lastRmbDown = 0.0f, Input::lastMmbDown = 0.0f;

#define MAXIMUM_CLICK_TIME 0.2f

void Input::HandleClick(Vector2D point, KeyCode button)
{
	std::vector<IClickable*> instances = IClickable::GetInstances();
	unique_ptr<Primitive> prim;

	for (size_t i = 0; i < instances.size(); i++)
	{
		IClickable* instance = instances[i];

		if (instance->OnClick != nullptr)
		{

			prim = instance->GetWorldShape();

			if (prim)
			{
				if (prim->Contains(point))
				{
					instance->OnClick->Invoke1P((void*)&button);
				}
			}
		}

	}

}

bool Input::GetKeyReleased(std::bitset<COUNT_KEYCODES> keyCodeBits)
{	
	return ((keysReleasedThisFrame & keyCodeBits) == keyCodeBits);
}

bool Input::GetKeyHeld(std::bitset<COUNT_KEYCODES> keyCodeBits)
{
	return (input&keyCodeBits) == keyCodeBits;
}

bool Input::GetAnyKey()
{
	return input.any();
}

bool Input::GetAnyKeyReleased()
{
	return keysReleasedThisFrame.any();
}

void Input::Update(UINT msg, WPARAM wparam, LPARAM lparam)
{
	keysReleasedThisFrame = bitset<COUNT_KEYCODES>();

	switch (msg)
	{

	// mouse input

	case(WM_LBUTTONUP):
		keysReleasedThisFrame.set(KEYCODE_LEFTMOUSE, true);

		if (Engine::Internal::EngineManager::timer.GetTime() - lastLmbDown < MAXIMUM_CLICK_TIME)
			HandleClick(GetMousePositionInWorld(), KEYCODE_LEFTMOUSE);

		break;
	case(WM_RBUTTONUP):
		keysReleasedThisFrame.set(KEYCODE_RIGHTMOUSE, true);

		if (Engine::Internal::EngineManager::timer.GetTime() - lastRmbDown < MAXIMUM_CLICK_TIME)
			HandleClick(GetMousePositionInWorld(), KEYCODE_RIGHTMOUSE);

		break;

	case(WM_LBUTTONDOWN):
		input.set(KEYCODE_LEFTMOUSE, true);
		lastLmbDown = Engine::Internal::EngineManager::timer.GetTime();
		break;

	case(WM_MBUTTONDOWN):
		input.set(KEYCODE_MIDDLEMOUSE, true);
		lastMmbDown = Engine::Internal::EngineManager::timer.GetTime();
		break;

	case(WM_RBUTTONDOWN):
		input.set(KEYCODE_RIGHTMOUSE, true);
		lastRmbDown = Engine::Internal::EngineManager::timer.GetTime();
		break;

	case(WM_MBUTTONUP):
		keysReleasedThisFrame.set(KEYCODE_MIDDLEMOUSE, true);

		if (Engine::Internal::EngineManager::timer.GetTime() - lastMmbDown < MAXIMUM_CLICK_TIME)
			HandleClick(GetMousePositionInWorld(), KEYCODE_MIDDLEMOUSE);

		break;

	case(WM_KEYDOWN):
		switch (wparam)
		{
		// numbers 0 through 9
		case('0'): input.set(KEYCODE_0, true); break;
		case('1'): input.set(KEYCODE_1, true); break;
		case('2'): input.set(KEYCODE_2, true); break;
		case('3'): input.set(KEYCODE_3, true); break;
		case('4'): input.set(KEYCODE_4, true); break;
		case('5'): input.set(KEYCODE_5, true); break;
		case('6'): input.set(KEYCODE_6, true); break;
		case('7'): input.set(KEYCODE_7, true); break;
		case('8'): input.set(KEYCODE_8, true); break;
		case('9'): input.set(KEYCODE_9, true); break;

		// alphabet a-z

		case('A'): input.set(KEYCODE_A, true); break;
		case('B'): input.set(KEYCODE_B, true); break;
		case('C'): input.set(KEYCODE_C, true); break;
		case('D'): input.set(KEYCODE_D, true); break;
		case('E'): input.set(KEYCODE_E, true); break;
		case('F'): input.set(KEYCODE_F, true); break;
		case('G'): input.set(KEYCODE_G, true); break;
		case('H'): input.set(KEYCODE_H, true); break;
		case('I'): input.set(KEYCODE_I, true); break;
		case('J'): input.set(KEYCODE_J, true); break;
		case('K'): input.set(KEYCODE_K, true); break;
		case('L'): input.set(KEYCODE_L, true); break;
		case('M'): input.set(KEYCODE_M, true); break;
		case('N'): input.set(KEYCODE_N, true); break;
		case('O'): input.set(KEYCODE_O, true); break;
		case('P'): input.set(KEYCODE_P, true); break;
		case('Q'): input.set(KEYCODE_Q, true); break;
		case('R'): input.set(KEYCODE_R, true); break;
		case('S'): input.set(KEYCODE_S, true); break;
		case('T'): input.set(KEYCODE_T, true); break;
		case('U'): input.set(KEYCODE_U, true); break;
		case('V'): input.set(KEYCODE_V, true); break;
		case('W'): input.set(KEYCODE_W, true); break;
		case('X'): input.set(KEYCODE_X, true); break;
		case('Y'): input.set(KEYCODE_Y, true); break;
		case('Z'): input.set(KEYCODE_Z, true); break;

		// other keys
		case(VK_OEM_PERIOD): input.set(KEYCODE_PERIOD, true); input.set(KEYCODE_FULLSTOP, true); break;
		case(VK_OEM_COMMA): input.set(KEYCODE_COMMA, true); break;
		case(VK_OEM_7): input.set(KEYCODE_HASHTAG, true); break;
		case(VK_OEM_5): input.set(KEYCODE_BACKSLASH, true); break;
		case(VK_OEM_3): input.set(KEYCODE_BACKTICK, true); break;
		case(VK_OEM_2): input.set(KEYCODE_FORWARDSLASH, true); break;
		case(VK_OEM_PLUS): input.set(KEYCODE_PLUS, true); input.set(KEYCODE_NUMPADPLUS, true); break;
		case(VK_OEM_MINUS): input.set(KEYCODE_MINUS, true); input.set(KEYCODE_NUMPADMINUS, true); break;


		// arrow keys
		case(VK_UP): input.set(KEYCODE_ARROWUP, true); break;
		case(VK_RIGHT): input.set(KEYCODE_ARROWRIGHT, true); break;
		case(VK_DOWN): input.set(KEYCODE_ARROWDOWN, true); break;
		case(VK_LEFT): input.set(KEYCODE_ARROWLEFT, true); break;

		// control keys
		case(VK_RETURN): input.set(KEYCODE_RETURN, true); input.set(KEYCODE_ENTER, true); break;
		case(VK_SPACE): input.set(KEYCODE_SPACEBAR, true); break;
		case(VK_LSHIFT): input.set(KEYCODE_LEFTSHIFT, true); break;
		case(VK_LCONTROL): input.set(KEYCODE_LEFTCONTROL, true); break;
		case(VK_CONTROL): input.set(KEYCODE_LEFTCONTROL, true); input.set(KEYCODE_RIGHTCONTROL, true); break;
		case(VK_SHIFT): input.set(KEYCODE_LEFTSHIFT, true); input.set(KEYCODE_RIGHTSHIFT, true); break;
		case(VK_MENU): input.set(KEYCODE_LEFTALT, true); input.set(KEYCODE_RIGHTALT, true); break;
		case(VK_RCONTROL): input.set(KEYCODE_RIGHTCONTROL, true); break;
		case(VK_RSHIFT): input.set(KEYCODE_RIGHTSHIFT, true); break;
		case(VK_BACK): input.set(KEYCODE_BACKSPACE, true); break;
		case(VK_TAB): input.set(KEYCODE_TAB, true); break;
		case(VK_ESCAPE): input.set(KEYCODE_ESCAPE, true); break;

		// nav
		case(VK_INSERT): input.set(KEYCODE_INSERT, true); break;
		case(VK_HOME): input.set(KEYCODE_HOME, true); break;
		case(VK_PRIOR): input.set(KEYCODE_PAGEUP, true); break;
		case(VK_NEXT): input.set(KEYCODE_PAGEDOWN, true); break;
		case(VK_END): input.set(KEYCODE_END, true); break;
		case(VK_DELETE): input.set(KEYCODE_DELETE, true); break;

		// numpad
		case(VK_NUMPAD0): input.set(KEYCODE_NUMPAD0, true); break;
		case(VK_NUMPAD1): input.set(KEYCODE_NUMPAD1, true); break;
		case(VK_NUMPAD2): input.set(KEYCODE_NUMPAD2, true); break;
		case(VK_NUMPAD3): input.set(KEYCODE_NUMPAD3, true); break;
		case(VK_NUMPAD4): input.set(KEYCODE_NUMPAD4, true); break;
		case(VK_NUMPAD5): input.set(KEYCODE_NUMPAD5, true); break;
		case(VK_NUMPAD6): input.set(KEYCODE_NUMPAD6, true); break;
		case(VK_NUMPAD7): input.set(KEYCODE_NUMPAD7, true); break;
		case(VK_NUMPAD8): input.set(KEYCODE_NUMPAD8, true); break;
		case(VK_NUMPAD9): input.set(KEYCODE_NUMPAD9, true); break;
		}
		break;


	case(WM_KEYUP):
		switch (wparam)
		{
			// numbers 0 through 9
		case('0'): keysReleasedThisFrame.set(KEYCODE_0, true); break;
		case('1'): keysReleasedThisFrame.set(KEYCODE_1, true); break;
		case('2'): keysReleasedThisFrame.set(KEYCODE_2, true); break;
		case('3'): keysReleasedThisFrame.set(KEYCODE_3, true); break;
		case('4'): keysReleasedThisFrame.set(KEYCODE_4, true); break;
		case('5'): keysReleasedThisFrame.set(KEYCODE_5, true); break;
		case('6'): keysReleasedThisFrame.set(KEYCODE_6, true); break;
		case('7'): keysReleasedThisFrame.set(KEYCODE_7, true); break;
		case('8'): keysReleasedThisFrame.set(KEYCODE_8, true); break;
		case('9'): keysReleasedThisFrame.set(KEYCODE_9, true); break;

			// alphabet a-z

		case('A'): keysReleasedThisFrame.set(KEYCODE_A, true); break;
		case('B'): keysReleasedThisFrame.set(KEYCODE_B, true); break;
		case('C'): keysReleasedThisFrame.set(KEYCODE_C, true); break;
		case('D'): keysReleasedThisFrame.set(KEYCODE_D, true); break;
		case('E'): keysReleasedThisFrame.set(KEYCODE_E, true); break;
		case('F'): keysReleasedThisFrame.set(KEYCODE_F, true); break;
		case('G'): keysReleasedThisFrame.set(KEYCODE_G, true); break;
		case('H'): keysReleasedThisFrame.set(KEYCODE_H, true); break;
		case('I'): keysReleasedThisFrame.set(KEYCODE_I, true); break;
		case('J'): keysReleasedThisFrame.set(KEYCODE_J, true); break;
		case('K'): keysReleasedThisFrame.set(KEYCODE_K, true); break;
		case('L'): keysReleasedThisFrame.set(KEYCODE_L, true); break;
		case('M'): keysReleasedThisFrame.set(KEYCODE_M, true); break;
		case('N'): keysReleasedThisFrame.set(KEYCODE_N, true); break;
		case('O'): keysReleasedThisFrame.set(KEYCODE_O, true); break;
		case('P'): keysReleasedThisFrame.set(KEYCODE_P, true); break;
		case('Q'): keysReleasedThisFrame.set(KEYCODE_Q, true); break;
		case('R'): keysReleasedThisFrame.set(KEYCODE_R, true); break;
		case('S'): keysReleasedThisFrame.set(KEYCODE_S, true); break;
		case('T'): keysReleasedThisFrame.set(KEYCODE_T, true); break;
		case('U'): keysReleasedThisFrame.set(KEYCODE_U, true); break;
		case('V'): keysReleasedThisFrame.set(KEYCODE_V, true); break;
		case('W'): keysReleasedThisFrame.set(KEYCODE_W, true); break;
		case('X'): keysReleasedThisFrame.set(KEYCODE_X, true); break;
		case('Y'): keysReleasedThisFrame.set(KEYCODE_Y, true); break;
		case('Z'): keysReleasedThisFrame.set(KEYCODE_Z, true); break;

			// other keys
		case(VK_OEM_PERIOD): keysReleasedThisFrame.set(KEYCODE_PERIOD, true); keysReleasedThisFrame.set(KEYCODE_FULLSTOP, true); break;
		case(VK_OEM_COMMA): keysReleasedThisFrame.set(KEYCODE_COMMA, true); break;
		case(VK_OEM_7): keysReleasedThisFrame.set(KEYCODE_HASHTAG, true); break;
		case(VK_OEM_5): keysReleasedThisFrame.set(KEYCODE_BACKSLASH, true); break;
		case(VK_OEM_3): keysReleasedThisFrame.set(KEYCODE_BACKTICK, true); break;
		case(VK_OEM_2): keysReleasedThisFrame.set(KEYCODE_FORWARDSLASH, true); break;
		case(VK_OEM_PLUS): keysReleasedThisFrame.set(KEYCODE_PLUS, true); keysReleasedThisFrame.set(KEYCODE_NUMPADPLUS, true); break;
		case(VK_OEM_MINUS): keysReleasedThisFrame.set(KEYCODE_MINUS, true); keysReleasedThisFrame.set(KEYCODE_NUMPADMINUS, true); break;


			// arrow keys
		case(VK_UP): keysReleasedThisFrame.set(KEYCODE_ARROWUP, true); break;
		case(VK_RIGHT): keysReleasedThisFrame.set(KEYCODE_ARROWRIGHT, true); break;
		case(VK_DOWN): keysReleasedThisFrame.set(KEYCODE_ARROWDOWN, true); break;
		case(VK_LEFT): keysReleasedThisFrame.set(KEYCODE_ARROWLEFT, true); break;

			// control keys
		case(VK_RETURN): keysReleasedThisFrame.set(KEYCODE_RETURN, true); keysReleasedThisFrame.set(KEYCODE_ENTER, true); break;
		case(VK_SPACE): keysReleasedThisFrame.set(KEYCODE_SPACEBAR, true); break;
		case(VK_LSHIFT): keysReleasedThisFrame.set(KEYCODE_LEFTSHIFT, true); break;
		case(VK_LCONTROL): keysReleasedThisFrame.set(KEYCODE_LEFTCONTROL, true); break;
		case(VK_CONTROL): keysReleasedThisFrame.set(KEYCODE_LEFTCONTROL, true); keysReleasedThisFrame.set(KEYCODE_RIGHTCONTROL, true); break;
		case(VK_SHIFT): keysReleasedThisFrame.set(KEYCODE_LEFTSHIFT, true); keysReleasedThisFrame.set(KEYCODE_RIGHTSHIFT, true); break;
		case(VK_MENU): keysReleasedThisFrame.set(KEYCODE_LEFTALT, true); keysReleasedThisFrame.set(KEYCODE_RIGHTALT, true); break;
		case(VK_RCONTROL): keysReleasedThisFrame.set(KEYCODE_RIGHTCONTROL, true); break;
		case(VK_RSHIFT): keysReleasedThisFrame.set(KEYCODE_RIGHTSHIFT, true); break;
		case(VK_BACK): keysReleasedThisFrame.set(KEYCODE_BACKSPACE, true); break;
		case(VK_TAB): keysReleasedThisFrame.set(KEYCODE_TAB, true); break;
		case(VK_ESCAPE): keysReleasedThisFrame.set(KEYCODE_ESCAPE, true); break;

			// nav
		case(VK_INSERT): keysReleasedThisFrame.set(KEYCODE_INSERT, true); break;
		case(VK_HOME): keysReleasedThisFrame.set(KEYCODE_HOME, true); break;
		case(VK_PRIOR): keysReleasedThisFrame.set(KEYCODE_PAGEUP, true); break;
		case(VK_NEXT): keysReleasedThisFrame.set(KEYCODE_PAGEDOWN, true); break;
		case(VK_END): keysReleasedThisFrame.set(KEYCODE_END, true); break;
		case(VK_DELETE): keysReleasedThisFrame.set(KEYCODE_DELETE, true); break;

			// numpad
		case(VK_NUMPAD0): keysReleasedThisFrame.set(KEYCODE_NUMPAD0, true); break;
		case(VK_NUMPAD1): keysReleasedThisFrame.set(KEYCODE_NUMPAD1, true); break;
		case(VK_NUMPAD2): keysReleasedThisFrame.set(KEYCODE_NUMPAD2, true); break;
		case(VK_NUMPAD3): keysReleasedThisFrame.set(KEYCODE_NUMPAD3, true); break;
		case(VK_NUMPAD4): keysReleasedThisFrame.set(KEYCODE_NUMPAD4, true); break;
		case(VK_NUMPAD5): keysReleasedThisFrame.set(KEYCODE_NUMPAD5, true); break;
		case(VK_NUMPAD6): keysReleasedThisFrame.set(KEYCODE_NUMPAD6, true); break;
		case(VK_NUMPAD7): keysReleasedThisFrame.set(KEYCODE_NUMPAD7, true); break;
		case(VK_NUMPAD8): keysReleasedThisFrame.set(KEYCODE_NUMPAD8, true); break;
		case(VK_NUMPAD9): keysReleasedThisFrame.set(KEYCODE_NUMPAD9, true); break;
		}
		break;

	}
	input ^= keysReleasedThisFrame;

}

Vector2D Input::GetMousePositionOnScreen()
{
	// Hold a pointer to the window class of the engine's main window.
	Engine::Internal::Window* win = Engine::Internal::EngineManager::GetWindow();

	// Store the mouse's position.
	LPPOINT pos = new POINT();
	GetCursorPos(pos);

	// Get information about where the window is on the screen.
	LPRECT rect = new RECT();
	if(!GetClientRect(win->GetHandle(),rect)) throw std::runtime_error("Error getting client rect.");
	
	ScreenToClient(win->GetHandle(), pos);

	if (pos->x < rect->left) pos->x = rect->left;
	if (pos->x > rect->right) pos->x = rect->right;
	if (pos->y > rect->bottom) pos->y = rect->bottom;
	if (pos->y < rect->top) pos->y = rect->top;

	Vector2D point = Vector2D(-(win->GetWidth()/2.0f)+pos->x, (win->GetHeight()/2.0f)-pos->y);

	delete pos;
	delete rect;

	return point;
}

Vector2D Input::GetMousePositionInWorld()
{
	Vector2D screenPoint = GetMousePositionOnScreen();
	// Add the position on the screen to the position of the camera to get a point in the level.
	return Engine::EngineHelper::GetCameraPos() + screenPoint;
}