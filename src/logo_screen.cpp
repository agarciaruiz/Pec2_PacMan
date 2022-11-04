#include "logo_screen.hpp"

void LogoScreen::Init()
{
	finishScreen = 0;
	framesCounter = 0;
	lettersCount = 0;

	logoPositionX = GetScreenWidth() / 2 - 128;
	logoPositionY = GetScreenHeight() / 2 - 128;

	topSideRecWidth = 16;
	leftSideRecHeight = 16;
	bottomSideRecWidth = 16;
	rightSideRecHeight = 16;

	alpha = 1.0f;

	texLogo = LoadTexture("resources/Menu/uoc.png");
}

void LogoScreen::Update()
{
	framesCounter++;

	if (framesCounter > 180)
	{
		finishScreen = 2;
		framesCounter = 0;      // Reset counter... will be used later...
	}
}

void LogoScreen::Draw()
{
	DrawTexture(texLogo, SCR_WIDTH / 2 - texLogo.width / 2, SCR_HEIGHT / 2 - texLogo.height / 2, WHITE);
}

void LogoScreen::Unload() {}