#pragma once
#include <fmodinc/fmod.hpp>
#include <fmodinc/fmod_errors.h>
#include <fmodinc/fmod.h>
#include <iostream>
#include <string>


using namespace FMOD;
using namespace std;

class MusicManager
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
	MusicManager();
	~MusicManager();

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

