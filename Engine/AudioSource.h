#pragma once

#include <AudioFile.h>
#include "Component.h"

using Engine::Assets::AudioFile;

namespace Engine
{
	class Actor;
	// A component that uses the xaudio engine to play a sound.
	class AudioSource : public Component
	{
	private:
		// The audio file to play
		AudioFile* file;
		// An instance of an xaudio2 source voice.
		IXAudio2SourceVoice* pSourceVoice;

		// Keep track if the instance has had its source voice initialized.
		bool init = false;
		void Init();
		// Destroy the source voice and delete the audio file.
		void ResetInstance();
		// Use the falloff algorithm to calculate a new volume for the audio source.
		float CalculateFalloff(float volume);
		

	public:
		AudioSource(Actor* a);
		~AudioSource();

		void SetAudioFile(AudioFile* file);
		AudioFile* GetAudioFile();

		// Plays the audio
		void Play();
		// Stops the audio
		void Stop();

		void Update() override;
		// How loud the audio will play
		float volume = 1.0f;
		// The rate at which the volume falls
		// 0 for no falloff
		float falloffRate = 0.0f;
		// A global float for the minimum distance required for 
		// sound energy to begin dissipating.
		static float falloffDistance;
		// Is the audio source currently playing?
		bool IsPlaying();
		// Used for looping the audio continuously.
		bool loop = false; 
	};

}