#pragma once

#include "SDLManager.h"


class AudioManager
{
private:
	AudioManager() = delete;
	~AudioManager() = delete;
	
public:

	static void Init();
	static void Close();

	static void PlayMusic(Mix_Music* music, int loops);
	static void PlaySoundEffect(Mix_Chunk* soundEffect, int loops);

	static void PauseMusic();
	static void ResumeMusic();

	static void PauseSoundEffect();
	static void ResumeSoundEffect();

	static void StopMusic();
	static void StopSoundEffect();

	static void SetMusicVolume(int volume);
	static void SetSoundEffectVolume(int volume);
};

