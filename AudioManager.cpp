#include "AudioManager.h"

void AudioManager::PlayMusic(Mix_Music* music, int loops)
{
	Mix_PlayMusic(music, loops);
}

void AudioManager::PlaySoundEffect(Mix_Chunk* soundEffect, int loops)
{
	Mix_PlayChannel(-1, soundEffect, loops);
}
