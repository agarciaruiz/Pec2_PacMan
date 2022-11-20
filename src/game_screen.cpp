#include "game_screen.hpp"

// Private methods
void GameScreen::ResetScreen()
{
	_gameManager->ResetGame();
	delete(_gameManager);
}

void GameScreen::Init()
{
	_gameManager = GameManager::GetInstance();
	framesCounter = 0;
	finishScreen = 0;
}

void GameScreen::Update()
{
	_gameManager->Update();
	// TO DO -> CHANGE TEXT ON WIN CONDITION
	// Game end condition
	if (_gameManager->GameEnded())
			finishScreen = 5;
}

void GameScreen::Draw()
{
	_gameManager->Draw();
}

void GameScreen::Unload()
{
	ResetScreen();
}