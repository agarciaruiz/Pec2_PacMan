#ifndef ENDINGSCREEN_H
#define ENDING_H
#include "screen.hpp"
#include "game_manager.h"

class EndingScreen : public Screen {
private:
public:
	void EndingScreen::Init() override;
	void EndingScreen::Update() override;
	void EndingScreen::Draw() override;
};

#endif