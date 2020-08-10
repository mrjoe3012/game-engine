#include "AudioSource.h"
#include "AudioManager.h"
#include "EngineManager.h"
#include "Actor.h"

using Engine::AudioSource;
using Engine::Assets::AudioFile;
using Engine::Internal::AudioManager;
using Engine::Actor;

float AudioSource::falloffDistance = 200.0f;

AudioSource::AudioSource(Actor* a)
	:
	Component(a),
	file(nullptr),
	pSourceVoice(nullptr)
{
}

AudioSource::~AudioSource()
{
	if (file)
		delete file;
}

AudioFile* AudioSource::GetAudioFile()
{
	return file;
}

void AudioSource::SetAudioFile(AudioFile* file)
{
	// Reset the instance.
	if (this->file)
		ResetInstance();
	// Set file pointer
	this->file = file;
	// Mark the instance for reinitialization
	init = false;
}

void AudioSource::Play()
{
	if (!init)
		Init();

	XAUDIO2_BUFFER* buffer = &file->GetBuffer();

	if (loop)
		buffer->LoopCount = XAUDIO2_LOOP_INFINITE;
	else
		buffer->LoopCount = 0;

	pSourceVoice->SubmitSourceBuffer(buffer);

	pSourceVoice->Start(0);
}

void AudioSource::Stop()
{
	if (init)
		pSourceVoice->Stop();
}

void AudioSource::Init()
{
	// create a new source voice using the file's buffer information as a paremeter.
	AudioManager::GetXAudio()->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&file->GetWFX());
	// mark the class as initialized.
	init = true;
}

void AudioSource::ResetInstance()
{
	// Destroy the xaudio resource
	pSourceVoice->DestroyVoice();
	pSourceVoice = NULL;
	// delete the file
	delete file;
	file = nullptr;
}

float AudioSource::CalculateFalloff(float volume)
{
	// Calculate the distance from the main camera.
	float distanceFromCamera = (Engine::Internal::EngineManager::cameraPos - actor->transform.position).Magnitude();
	// Calculate the distance after the minimum falloff distance.
	float fDistance = distanceFromCamera - falloffDistance;
	if (fDistance < 0) fDistance = 0.0f;

	// Calculate the absolute value of the falloff rate.
	float fRate = abs(falloffRate)/100.0f;
	// Calculate a new volume using the falloff rate as the gradient.
	float newVolume = (-fRate * fDistance) + volume;
	if (newVolume < 0.0f) newVolume = 0.0f;
	// Return the new volume.
	return newVolume;
}

void AudioSource::Update()
{
	if (pSourceVoice)
	{
		float v = CalculateFalloff(volume);
		pSourceVoice->SetVolume(v);
	}
}

bool AudioSource::IsPlaying()
{
	if (pSourceVoice)
	{
		// Get the state of the voice.
		XAUDIO2_VOICE_STATE state = {};
		pSourceVoice->GetState(&state);
		// If there are buffers queued, then the source is playing.
		return state.BuffersQueued > 0;
	}
	return false;
}