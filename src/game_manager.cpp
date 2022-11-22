#include "game_manager.h"

bool GameManager::GameEnded() const { return gameEnded; }
bool GameManager::Win() const { return win; }
GameManager* GameManager::_gameManager = NULL;


GameManager::GameManager() {}

GameManager* GameManager::GetInstance()
{
	if (!_gameManager)
		_gameManager = new GameManager();
	return _gameManager;
}

void GameManager::Init()
{
	gamePaused = false;
	gameEnded = false;
	win = false;

	playerLifesImage = LoadImage("resources/Game/IconLifes.png");
	playerLifesTexture = LoadTextureFromImage(playerLifesImage);
	UnloadImage(playerLifesImage);
	imTileset = LoadImage("resources/TileMap/PacManTileset.png");
	texTileset = LoadTextureFromImage(imTileset);
	UnloadImage(imTileset);
	
	_tilemap = Tilemap::GetInstance();
	_tilemap->Load("resources/TileMap/tilemap.txt", "resources/TileMap/tilemap_collisions.txt", "resources/TileMap/objects.txt");
	_tilemap->Init(SCR_WIDTH, SCR_HEIGHT, 32);

	_player = Player::GetInstance();
	_player->Init();

	_ghost.Init();
}

void GameManager::Update()
{
	if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

	// Press enter or tap to change to ENDING screen
	if (!gamePaused)
	{
		if (_player->Lifes() == 0) 
		{
			gameEnded = true;
		}
		
		if(_tilemap->numOfPills == 0)
		{
			gameEnded = true;
			win = true;
		}

		// PLAYER UPDATE
		_player->Update();
		_ghost.Update();
	}
}

void GameManager::Draw()
{
	// UI DRAW
	DrawUI();

	// TILEMAP DRAW
	_tilemap->Draw(texTileset);
	
	// PLAYER DRAW
	_player->Draw();

	// GHOST DRAW
	_ghost.Draw();
}

void GameManager::DrawUI()
{
	// PAUSED GAME
	if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);

	// PLAYER LIFES 
	int offset = 50;
	int lifesPos = GetScreenWidth();
	for (int i = 0; i < _player->Lifes(); i++) 
	{
		lifesPos -= offset;
		DrawTexture(playerLifesTexture, lifesPos, 5, WHITE);
	}

	// PLAYER SCORE
	char* score = (char*)TextFormat("SCORE:    %i", _player->Score());
	DrawText(score, 20, 10, 20, GRAY);
}

void GameManager::Unload() 
{
	UnloadTexture(playerLifesTexture);
	UnloadTexture(texTileset);
	_player->Reset();
	_ghost.Reset();
}