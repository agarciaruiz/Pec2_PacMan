#include "ending_screen.hpp"

void EndingScreen::Update()
{
	framesCounter++;

	// Press enter or tap to return to TITLE screen
	if (IsKeyPressed(KEY_ENTER))
		finishScreen = 2;

	if (IsKeyPressed(KEY_O))
		finishScreen = 3;
}

void EndingScreen::Draw()
{
	DrawText("YOU LOOSE :(", SCR_WIDTH / 2 - MeasureText("YOU LOOSE :(", 50) / 2, GetScreenHeight() / 2 - 50, 50, YELLOW);

	if ((framesCounter / 30) % 2 == 0)
	{
		DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);
		DrawText("PRESS [0] for INSTRUCTIONS", GetScreenWidth() / 2 - MeasureText("PRESS [0] for INSTRUCTIONS", 20) / 2, GetScreenHeight() / 2 + 40, 20, DARKGRAY);
	}
}