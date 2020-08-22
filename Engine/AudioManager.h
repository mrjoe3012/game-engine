#ifdef USE_AUDIOMANAGER_DEFINES
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

#pragma once
#include <xaudio2.h>

namespace Engine
{
	namespace Internal
	{
		// Encapsulates the intialization of the xaudio2 engine.
		static class AudioManager
		{
		private:
			// Pointers to xaudio interfaces.
			static IXAudio2* pXAudio2;
			static IXAudio2MasteringVoice* pMasterVoice;

		public:
			// Initialize the engine.
			static void Init();

			// Boilerplate chunk reading.
			static HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
			static HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);

			static IXAudio2* GetXAudio() { return pXAudio2; }
		};

	}
}