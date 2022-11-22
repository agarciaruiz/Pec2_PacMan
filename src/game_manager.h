#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <time.h>
#include "raylib.h"
#include "player.hpp"
#include "ghost.h"
#include "tilemap.h"

class GameManager {
private:

	// Singleton
	GameManager::GameManager();
	static GameManager* _gameManager;

	// Game settings
	bool gamePaused;
	bool gameEnded;
	bool win;
	Image playerLifesImage;
	Texture2D playerLifesTexture;

	// Player settings
	Player* _player;
	Tilemap* _tilemap;

	Ghost _ghost;
	Image imTileset;
	Texture2D texTileset;

	// Private methods
	void GameManager::DrawUI();

public:

	bool GameManager::GameEnded() const;
	bool GameManager::Win() const;

	static GameManager* GameManager::GetInstance();
	void GameManager::Init();
	void GameManager::Update();
	void GameManager::Draw();
	void GameManager::Unload();
};

#endif // !GAME_MANAGER_H
