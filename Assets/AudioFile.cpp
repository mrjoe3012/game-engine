#include "AudioFile.h"
#define USE_AUDIOMANAGER_DEFINES
#include <AudioManager.h>

using Engine::Assets::AudioFile;
using Engine::Internal::AudioManager;
using std::string;

AudioFile::AudioFile()
{
}

AudioFile::AudioFile(string path)
	:
	path(path)
{
	ReadFile();
}

AudioFile::AudioFile(AudioFile& f)
{
	this->path = f.path;
	this->buffer = f.buffer;
	this->wfx = f.wfx;
}

AudioFile::~AudioFile()
{
	
}
// Boilerplate xaudio code for reading a file into xaudio structures
HRESULT AudioFile::ReadFile()
{
	TCHAR * strFileName = (TCHAR*)path.c_str();

	// Open the file
	HANDLE hFile = CreateFile(
		strFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return HRESULT_FROM_WIN32(GetLastError());

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	AudioManager::FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	AudioManager::ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE)
		return S_FALSE;

	AudioManager::FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	AudioManager::ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	AudioManager::FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	AudioManager::ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
	// Default loop from begin to end
	buffer.LoopBegin = 0;
	buffer.LoopLength = buffer.PlayLength;
}