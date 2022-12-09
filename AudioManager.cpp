#include "AudioManager.h"

void AudioManager::Init()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void AudioManager::Close()
{
	Mix_CloseAudio();
}

void AudioManager::PlayMusic(Mix_Music* music, int loops)
{
	Mix_PlayMusic(music, loops);
}

void AudioManager::PlaySoundEffect(Mix_Chunk* soundEffect, int loops)
{
	Mix_PlayChannel(-1, soundEffect, loops);
}

void AudioManager::PauseMusic()
{
	Mix_PauseMusic();
}

void AudioManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

void AudioManager::PauseSoundEffect()
{
	Mix_Pause(-1);
}

void AudioManager::ResumeSoundEffect()
{
	Mix_Resume(-1);
}

void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}

void AudioManager::StopSoundEffect()
{
	Mix_HaltChannel(-1);
}

void AudioManager::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void AudioManager::SetSoundEffectVolume(int volume)
{
	Mix_Volume(-1, volume);
}
