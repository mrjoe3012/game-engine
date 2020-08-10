#include "Engine.h"
#include "EngineManager.h"
#include <Physics.h>
#include "Window.h"

std::string Engine::EngineHelper::engineVersion = "1.0.0";
std::string Engine::EngineHelper::gameVersion = "1.0.0";

float Engine::EngineHelper::physicsCullingDistance = 0.0f;

double Engine::EngineHelper::GetDeltaTime()
{
	return Engine::Internal::EngineManager::timer.GetDeltaTime();
}

float Engine::EngineHelper::GetTime()
{
	return Engine::Internal::EngineManager::timer.GetTime();
}

void Engine::EngineHelper::SetCameraPos(Engine::Maths::Vector2D pos)
{
	Engine::Internal::EngineManager::cameraPos = pos;
}

Engine::Maths::Vector2D Engine::EngineHelper::GetCameraPos()
{
	return Engine::Internal::EngineManager::cameraPos;
}

void Engine::EngineHelper::Quit(int code)
{
	Engine::Internal::EngineManager::hasQuit = true;
	//Engine::Internal::EngineManager::Release();
	Engine::Internal::EngineManager::exitCode = code;
	PostQuitMessage(code);
}

void Engine::EngineHelper::ResetWindow()
{
	Engine::Internal::Window* w = Engine::Internal::EngineManager::GetWindow();
	HWND hwnd = w->GetHandle();
	float height = w->GetHeight(), width = w->GetWidth();

	SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_SHOWWINDOW);
}

void Engine::EngineHelper::SetBackgroundColour(Engine::Colour c)
{
	Engine::Internal::EngineManager::backgroundColour = c;
}

Engine::Colour Engine::EngineHelper::GetBackgroundColour()
{
	return Engine::Internal::EngineManager::backgroundColour;
}

void Engine::EngineHelper::SetTimeScale(float ts)
{
	Engine::Physics::PhysicsHandler::timeScale = ts;
}

float Engine::EngineHelper::GetTimeScale()
{
	return Engine::Physics::PhysicsHandler::timeScale;
}

Engine::Maths::Matrix<bool>& Engine::EngineHelper::GetPhysicsLayerMatrix()
{
	return Engine::Physics::PhysicsHandler::layerMatrix;
}

void Engine::EngineHelper::SetPhysicsLayer(unsigned int i, unsigned int j, bool value)
{
	// Symmetrically setting the matrix.
	GetPhysicsLayerMatrix()[i][j] = value;
	GetPhysicsLayerMatrix()[j][i] = value;
}