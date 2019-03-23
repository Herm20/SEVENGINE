#include "MusicManager.h"

bool MusicManager::isOn = true;
bool MusicManager::isPossible = true;
char* MusicManager::currentSound;

FMOD_RESULT MusicManager::result;
FMOD_SYSTEM* MusicManager::audioSystem;
FMOD_SOUND* MusicManager::music;
FMOD_CHANNEL* MusicManager::musicChannel;

MusicManager::MusicManager()
{


}


MusicManager::~MusicManager()
{
}

void MusicManager::InitSound()
{
	result = FMOD_System_Create(&audioSystem);

	if (result != FMOD_OK)
	{
		isPossible = false;
		cout << "FMOD ERROR " << result << " " << FMOD_ErrorString(result);
	}

	if (isPossible == true)
	{
		result = FMOD_System_Init(audioSystem, 10, FMOD_INIT_NORMAL, 0);
	}

	if (result != FMOD_OK)
	{
		isPossible = false;
		cout << "FMOD ERROR " << result << " " << FMOD_ErrorString(result);
	}

	if (isPossible == true)
	{
		FMOD_Channel_SetVolume(musicChannel, 0.0f);
	}
}

void MusicManager::SetVolume(float volume)
{
	if (isPossible && isOn && volume >= 0.0f && volume <= 1.0f)
	{
		FMOD_Channel_SetVolume(musicChannel, volume);
	}
}

void MusicManager::LoadFile(const char * file)
{
	currentSound = (char*)file;

	if (isPossible && isOn == true)
	{
		result = FMOD_Sound_Release(music);
		result = FMOD_System_CreateStream(audioSystem, currentSound, FMOD_DEFAULT, 0, &music);

		if (result != FMOD_OK)
		{
			isPossible = false;
		}
	}
}

void MusicManager::UnloadFile()
{
	if (isPossible == true)
	{
		result = FMOD_Sound_Release(music);
	}
}

void MusicManager::Play(bool paused)
{
	if (isPossible && isOn == true)
	{
		result = FMOD_System_PlaySound(audioSystem, music, FMOD_DEFAULT, paused, &musicChannel);
		FMOD_Channel_SetMode(musicChannel,FMOD_LOOP_NORMAL);
	}
}

bool MusicManager::getSound()
{
	return isOn;
}

void MusicManager::setPause(bool pause)
{
	FMOD_Channel_SetPaused(musicChannel, pause);
}

void MusicManager::setSound(bool sound)
{
	isOn = sound;
}

void MusicManager::toggleSound()
{
	isOn = !isOn;

	if (isOn == true)
	{
		LoadFile(currentSound);
		Play();
	}

	if (isOn == false)
	{
		UnloadFile();
	}
}

void MusicManager::togglePause()
{
	FMOD_BOOL h;
	FMOD_Channel_GetPaused(musicChannel, &h);
	FMOD_Channel_SetPaused(musicChannel, !h);
}



