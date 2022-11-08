#include "options_screen.hpp"

void OptionsScreen::Init() 
{
	instructions1 = "To move PACMAN use the direction keys or A,D,W,S";
	instructions2 = "PACMAN has 3 lifes, every dot eaten increases 10 points";
	instructions3 = "the big dots adds 50 points to the score.";

	instructions4 = "To win PACMAN has to eat all the dots";
	instructions5 = "You loose if the ghost SHADOW kills you 3 times.";

	instructions6 = "Press [O] to return to Title Screen";

	framesCounter = 0;
	finishScreen = 0;
}

void OptionsScreen::Update() 
{
	framesCounter++;

	if (IsKeyPressed(KEY_O))
		finishScreen = 2;
}

void OptionsScreen::Draw()
{
	DrawText(instructions1, GetScreenWidth() / 2 - MeasureText(instructions1, 20) / 2, GetScreenHeight() / 2 - 60, 20, LIGHTGRAY);
	DrawText(instructions2, GetScreenWidth() / 2 - MeasureText(instructions2, 20) / 2, GetScreenHeight() / 2 -40, 20, LIGHTGRAY);
	DrawText(instructions3, GetScreenWidth() / 2 - MeasureText(instructions3, 20) / 2, GetScreenHeight() / 2 - 20, 20, LIGHTGRAY);

	DrawText(instructions4, GetScreenWidth() / 2 - MeasureText(instructions4, 20) / 2, GetScreenHeight() / 2 + 40, 20, LIGHTGRAY);
	DrawText(instructions5, GetScreenWidth() / 2 - MeasureText(instructions5, 20) / 2, GetScreenHeight() / 2 + 60, 20, LIGHTGRAY);

	if ((framesCounter / 30) % 2 == 0)
		DrawText(instructions6, GetScreenWidth() / 2 - MeasureText(instructions6, 20) / 2, GetScreenHeight() / 2 + 100, 20, GRAY);
}
