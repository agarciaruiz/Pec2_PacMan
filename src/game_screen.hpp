#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#define REUSABLE_COPTERS 8

#include <iostream>
#include "screen.hpp"
#include "game_manager.h"

class GameScreen : public Screen {
private:
	GameManager* _gameManager;
public:
	void GameScreen::Init() override;
	void GameScreen::Update() override;
	void GameScreen::Draw() override;
	void GameScreen::Unload() override;
};

#endif