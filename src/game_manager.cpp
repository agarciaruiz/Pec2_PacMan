#include "game_manager.h"

EnemyManager GameManager::EnemyManager() const { return _enemyManager; }

void GameManager::Init()
{
	gamePaused = false;

	imTileset = LoadImage("resources/TileMap/PacManTileset.png");
	texTileset = LoadTextureFromImage(imTileset);
	UnloadImage(imTileset);

	// PASS TXT FILES
	_tilemap.Load("resources/TileMap/tilemap.txt", "resources/TileMap/tilemap_collisions.txt");
	_tilemap.Init(SCR_WIDTH, SCR_HEIGHT, 20);
	/*playerPos = Vector2{SCR_WIDTH / 2 , SCR_HEIGHT};
	player.Init(playerPos);
	_enemyManager.Init();*/
}

void GameManager::Update()
{
	if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

	// Press enter or tap to change to ENDING screen
	if (!gamePaused)
	{
		//UpdateTime();
		//player.Update(_enemyManager.Helicopters(), _enemyManager.Troopers());
		//_enemyManager.Update();
	}
}

void GameManager::Draw()
{
	DrawUI();
	_tilemap.Draw(texTileset);
	//player.Draw();
	//_enemyManager.Draw();
}

void GameManager::DrawUI()
{
	if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);

	// REPLACE BY PLAYER LIFES
	/*char* numLanded = (char*)TextFormat("LANDED TROOPERS: %i", _enemyManager.LandedTroopers());
	DrawText(numLanded, 20, 30, 20, GRAY);*/

	char* score = (char*)TextFormat("SCORE: %i", player.Score());
	DrawText(score, 20, 50, 20, GRAY);
}

void GameManager::ResetGame() 
{
	/*gameSecs = 0;
	gameMins = 0;
	gameHours = 0;

	player.Reset();
	_enemyManager.Reset();*/
}