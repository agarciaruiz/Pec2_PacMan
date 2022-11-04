#include "title_screen.hpp"

void TitleScreen::Init()
{
	texTitle = LoadTexture("resources/Menu/PacMan_MainLogo.png");
	framesCounter = 0;
	finishScreen = 0;
}

void TitleScreen::Update()
{
	framesCounter++;
	// Press enter to change to GAMEPLAY screen
	if (IsKeyPressed(KEY_ENTER))
		finishScreen = 4;   // GAMEPLAY

	if (IsKeyPressed(KEY_O))
		finishScreen = 3; // OPTIONS
}

void TitleScreen::Draw()
{
	// TODO: Draw TITLE screen here!
	DrawTexture(texTitle, SCR_WIDTH / 2 - texTitle.width / 2, SCR_HEIGHT / 4 - texTitle.height / 2, WHITE);

	DrawText("by", SCR_WIDTH / 2 - MeasureText("by", 20) / 2, GetScreenHeight() / 4 + 120, 20, DARKGRAY);
	DrawText("Alberto G.", SCR_WIDTH / 2 - MeasureText("Alberto G.", 20) / 2, GetScreenHeight() / 4 + 140, 20, DARKGRAY);

	if ((framesCounter / 30) % 2 == 0)
	{
		DrawText("PRESS [ENTER] to START", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] to START", 20) / 2, GetScreenHeight() / 2 + 80, 20, GRAY);
		DrawText("PRESS [0] for INSTRUCTIONS", GetScreenWidth() / 2 - MeasureText("PRESS [0] for INSTRUCTIONS", 20) / 2, GetScreenHeight() / 2 + 100, 20, DARKGRAY);
	}
}
