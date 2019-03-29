#include "AudioManager.h"

bool AudioManager::isOn = true;
bool AudioManager::isPossible = true;
char* AudioManager::currentSound;

FMOD_RESULT AudioManager::result;
FMOD_SYSTEM* AudioManager::audioSystem;
FMOD_SOUND* AudioManager::music;
FMOD_CHANNEL* AudioManager::musicChannel;

AudioManager::AudioManager()
{

}


AudioManager::~AudioManager()
{
	/*delete currentSound;
	delete audioSystem;
	delete music;
	delete musicChannel;*/
}

void AudioManager::InitSound()
{
	result = FMOD_System_Create(&audioSystem);

	if (result != FMOD_OK)
	{
		isPossible = false;
		std::cout << "FMOD ERROR " << result << " " << FMOD_ErrorString(result);
	}

	if (isPossible == true)
	{
		result = FMOD_System_Init(audioSystem, 10, FMOD_INIT_NORMAL, 0);
	}

	if (result != FMOD_OK)
	{
		isPossible = false;
		std::cout << "FMOD ERROR " << result << " " << FMOD_ErrorString(result);
	}

	if (isPossible == true)
	{
		FMOD_Channel_SetVolume(musicChannel, 0.0f);
	}
}

void AudioManager::SetVolume(float volume)
{
	if (isPossible && isOn && volume >= 0.0f && volume <= 1.0f)
	{
		FMOD_Channel_SetVolume(musicChannel, volume);
	}
}

void AudioManager::LoadFile(const char * file)
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

void AudioManager::UnloadFile()
{
	if (isPossible == true)
	{
		result = FMOD_Sound_Release(music);
	}
}

void AudioManager::Play(bool paused)
{
	if (isPossible && isOn == true)
	{
		result = FMOD_System_PlaySound(audioSystem, music, FMOD_DEFAULT, paused, &musicChannel);
		FMOD_Channel_SetMode(musicChannel,FMOD_LOOP_NORMAL);
	}
}

bool AudioManager::getSound()
{
	return isOn;
}

void AudioManager::setPause(bool pause)
{
	FMOD_Channel_SetPaused(musicChannel, pause);
}

void AudioManager::setSound(bool sound)
{
	isOn = sound;
}

void AudioManager::toggleSound()
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

void AudioManager::togglePause()
{
	FMOD_BOOL h;
	FMOD_Channel_GetPaused(musicChannel, &h);
	FMOD_Channel_SetPaused(musicChannel, !h);
}



