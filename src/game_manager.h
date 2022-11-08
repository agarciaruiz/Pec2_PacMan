#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <time.h>
#include "raylib.h"
#include "player.hpp"
#include "bullet.h"
#include "enemy_manager.h"
#include "tilemap.h"

class GameManager {
private:
	// Game settings
	bool gamePaused;
	Image playerLifesImage;
	Texture2D playerLifesTexture;

	// Player settings
	Player player {};
	Vector2 playerPos;

	EnemyManager _enemyManager{};
	Tilemap _tilemap{};
	Image imTileset;
	Texture2D texTileset;

	// Private methods
	void GameManager::DrawUI();

public:
	EnemyManager EnemyManager() const;
	void GameManager::Init();
	void GameManager::Update();
	void GameManager::Draw();
	void GameManager::ResetGame();
};

#endif // !GAME_MANAGER_H
