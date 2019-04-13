#include "AudioManager.h"

bool AudioManager::isOn = true;
bool AudioManager::isPossible = true;
char* AudioManager::currentSound;
FMOD_RESULT AudioManager::result;

FMOD_SYSTEM* AudioManager::audioSystemBG;
FMOD_SOUND* AudioManager::bgSound;
FMOD_CHANNEL* AudioManager::bgChannel;

FMOD_SYSTEM* AudioManager::audioSystemEffect;
FMOD_SOUND* AudioManager::effectSound;
FMOD_CHANNEL* AudioManager::effectChannel;

AudioManager::AudioManager()
{

}


AudioManager::~AudioManager()
{

}

/// Background Channel Functions
void AudioManager::InitSoundBG()
{
	result = FMOD_System_Create(&audioSystemBG);

	if (result != FMOD_OK)
	{
		isPossible = false;
		std::cout << "FMOD ERROR " << result << " " << FMOD_ErrorString(result);
	}

	if (isPossible == true)
	{
		result = FMOD_System_Init(audioSystemBG, 10, FMOD_INIT_NORMAL, 0);
	}

	if (result != FMOD_OK)
	{
		isPossible = false;
		std::cout << "FMOD ERROR " << result << " " << FMOD_ErrorString(result);
	}

	if (isPossible == true)
	{
		FMOD_Channel_SetVolume(bgChannel, 0.0f);
	}
}

void AudioManager::LoadBGFile(const char * file)
{
	currentSound = (char*)file;

	if (isPossible && isOn == true)
	{
		result = FMOD_Sound_Release(bgSound);
		result = FMOD_System_CreateStream(audioSystemBG, currentSound, FMOD_DEFAULT, 0, &bgSound);

		if (result != FMOD_OK)
		{
			isPossible = false;
		}
	}
}

void AudioManager::SetVolume(float volume)
{
	if (isPossible && isOn && volume >= 0.0f && volume <= 1.0f)
	{
		FMOD_Channel_SetVolume(bgChannel, volume);
	}
}

void AudioManager::Play()
{
	if (isPossible && isOn == true)
	{
#ifndef FMODEX
		result = FMOD_System_PlaySound(audioSystemBG, bgSound, FMOD_DEFAULT, false, &bgChannel);
#else
		result = FMOD_System_PlaySound(audioSystemBG, FMOD_CHANNELINDEX::FMOD_CHANNEL_FREE, bgSound, false, &bgChannel);
#endif
		FMOD_Channel_SetMode(bgChannel, FMOD_LOOP_NORMAL);
	}
}

bool AudioManager::getSound()
{
	return isOn;
}

void AudioManager::setPause(bool pause)
{
	FMOD_Channel_SetPaused(bgChannel, pause);
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
		LoadBGFile(currentSound);
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
	FMOD_Channel_GetPaused(bgChannel, &h);
	FMOD_Channel_SetPaused(bgChannel, !h);
}
///


/// Effect Channel Functions
void AudioManager::InitSoundEffect()
{
	result = FMOD_System_Create(&audioSystemEffect);

	if (result != FMOD_OK)
	{
		isPossible = false;
		std::cout << "FMOD ERROR " << result << " " << FMOD_ErrorString(result);
	}

	if (isPossible == true)
	{
		result = FMOD_System_Init(audioSystemEffect, 10, FMOD_INIT_NORMAL, 0);
	}

	if (result != FMOD_OK)
	{
		isPossible = false;
		std::cout << "FMOD ERROR " << result << " " << FMOD_ErrorString(result);
	}

	if (isPossible == true)
	{
		FMOD_Channel_SetVolume(effectChannel, 0.0f);
	}
}

void AudioManager::LoadEffectFile(const char * file)
{
	currentSound = (char*)file;

	if (isPossible && isOn == true)
	{
		result = FMOD_Sound_Release(effectSound);
		result = FMOD_System_CreateStream(audioSystemEffect, currentSound, FMOD_DEFAULT, 0, &effectSound);

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
		result = FMOD_Sound_Release(effectSound);
	}
}

void AudioManager::PlayEffect()
{
	if (isPossible && isOn == true)
	{
#ifndef FMODEX
		result = FMOD_System_PlaySound(audioSystemEffect, effectSound, FMOD_DEFAULT, false, &effectChannel);
#else
		result = FMOD_System_PlaySound(audioSystemEffect, FMOD_CHANNELINDEX::FMOD_CHANNEL_FREE, effectSound, false, &effectChannel);
#endif
		FMOD_Channel_SetMode(effectChannel, FMOD_LOOP_OFF);
	}
}
///
