#pragma once
#include <string>
#include <xaudio2.h>

namespace Engine
{
	namespace Assets
	{
		// Used to store audio from a wav file on the disk.
		class AudioFile
		{
		private:
			// The path to the audio file
			std::string path;
			// xaudio buffers
			WAVEFORMATEXTENSIBLE wfx = { 0 };
			XAUDIO2_BUFFER buffer = { 0 };
			// reads the file at the path and stores information inside of the buffers
			HRESULT ReadFile();

			AudioFile();
		public:
			AudioFile(std::string path);
			AudioFile(AudioFile&);
			~AudioFile();

			WAVEFORMATEXTENSIBLE GetWFX() { return wfx; }
			XAUDIO2_BUFFER GetBuffer() { return buffer; }
		};
	}
}