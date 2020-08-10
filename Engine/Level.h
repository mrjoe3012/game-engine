#pragma once
#include <type_traits>

namespace Engine
{
	// Abstract class. Custom levels inherit from this class and can then be loaded by the engine.
	class Level
	{
	private:
		static void ResetEnvironment();
		static Level* loadedLevel;
	public:
		static Level& GetLevelInstance() { return *loadedLevel; }

		// Called when the level is loaded.
		virtual void OnLoad() {}
		// Called when the level is unloaded.
		virtual void OnUnload() {}
		// Called each frame.
		virtual void Update() {}
		// Called on application quit
		virtual void OnQuit(int code) {}

		static void UpdateCall();
		static void QuitCall(int code);
		// Loads an instance of the level type.
		template<typename T>
		static void LoadLevel()
		{
			static_assert(std::is_base_of<Level, T>::value, "typename T must be of type level.");
			static_assert(!std::is_same<Level, T>::value, "typename T cannot be of abstract type \"level\"");

			if (loadedLevel)
			{
				loadedLevel->OnUnload();
				delete loadedLevel;
			}

			T* t = new T();

			loadedLevel = (Level*)(t);
			ResetEnvironment();
			loadedLevel->OnLoad();
		}

	};
}