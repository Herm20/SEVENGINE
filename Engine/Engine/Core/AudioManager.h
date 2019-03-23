#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <fmodinc/fmod.hpp>
#include <fmodinc/fmod_errors.h>
#include <fmodinc/fmod.h>
#include <iostream>
#include <string>

using namespace FMOD;

class AudioManager
{

private:
	static FMOD_SYSTEM* audioSystem;
	static FMOD_SOUND* music;
	static FMOD_CHANNEL* musicChannel;
	static FMOD_RESULT result;

	static bool isOn;
	static bool isPossible;
	static char * currentSound;
public:
	AudioManager();
	~AudioManager();

	static void InitSound();

	static void SetVolume(float volume);
	static void LoadFile(const char* file);
	static void UnloadFile();
	static void Play(bool paused = false);

	static bool getSound();

	static void setPause(bool pause);
	static void setSound(bool sound);

	static void toggleSound();
	static void togglePause();
};
#endif // AUDIOMANAGER_H


