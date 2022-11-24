#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "raylib.h"

class SoundManager
{
private:
	SoundManager::SoundManager();
	static SoundManager* _soundManager;

	Music _music;
public:

	static SoundManager* SoundManager::GetInstance();

	void SoundManager::PlayMusic(char* musicStream);
	void SoundManager::UpdateMusic();
	void SoundManager::UnloadMusic();

	void SoundManager::PlaySoundStream(char* soundStream);
};

#endif // !SOUND_MANAGER_H
