#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <time.h>
#include "raylib.h"
#include "player.hpp"
#include "ghost.h"
#include "tilemap.h"

class GameManager {
private:
	// Game settings
	bool gamePaused;
	bool gameEnded;
	bool win;
	Image playerLifesImage;
	Texture2D playerLifesTexture;

	// Player settings
	Player player {};
	Vector2 playerPos;

	Ghost _ghost;
	Tilemap _tilemap{};
	Image imTileset;
	Texture2D texTileset;

	// Private methods
	void GameManager::DrawUI();

public:
	bool GameManager::GameEnded() const;
	bool GameManager::Win() const;
	void GameManager::Init();
	void GameManager::Update();
	void GameManager::Draw();
	void GameManager::ResetGame();
};

#endif // !GAME_MANAGER_H
