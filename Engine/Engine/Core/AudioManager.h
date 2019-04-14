#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#ifndef FMODEX
#include <fmodinc/fmod.hpp>
#include <fmodinc/fmod_errors.h>
#include <fmodinc/fmod.h>
#else
#include <fmodex/fmod.hpp>
#include <fmodex/fmod_errors.h>
#include <fmodex/fmod.h>
#endif

#include <iostream>
#include <boost/container/string.hpp>

using namespace FMOD;

class AudioManager
{

private:
	// Variables for Background Sound System
	static FMOD_SYSTEM* audioSystemBG;
	static FMOD_SOUND* bgSound;
	static FMOD_CHANNEL* bgChannel;

	// Variables for Effect Sound System
	static FMOD_SYSTEM* audioSystemEffect;
	static FMOD_SOUND* effectSound;
	static FMOD_CHANNEL* effectChannel;

	static FMOD_RESULT result;
	static bool isOn;
	static bool isPossible;
	static char * currentSound;
public:
	AudioManager();
	~AudioManager();

	static void InitSoundBG();
	static void SetVolume(float volume);
	static void LoadBGFile(const char* file);
	static void Play();
	static bool getSound();

	static void setPause(bool pause);
	static void setSound(bool sound);

	static void toggleSound();
	static void togglePause();

	static void InitSoundEffect();
	static void LoadEffectFile(const char* file);
	static void UnloadFile();
	static void PlayEffect();
};
#endif // AUDIOMANAGER_H

