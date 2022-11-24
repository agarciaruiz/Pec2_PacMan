#include "sound_manager.h"

SoundManager* SoundManager::_soundManager = NULL;

SoundManager::SoundManager(){}

SoundManager* SoundManager::GetInstance() 
{
	if (_soundManager == NULL)
		_soundManager = new SoundManager();
	return _soundManager;
}

void SoundManager::PlayMusic(char* musicStream) {
	_music = LoadMusicStream(musicStream);
	SetMusicVolume(_music, 1.0f);
	PlayMusicStream(_music);
}

void SoundManager::UpdateMusic() {
	UpdateMusicStream(_music);
}

void SoundManager::UnloadMusic() {
	UnloadMusicStream(_music);
}

void SoundManager::PlaySoundStream(char* soundStream) {
	Sound sound = LoadSound(soundStream);
	PlaySound(sound);
	//UnloadSound(sound);
}