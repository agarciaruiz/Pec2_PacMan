#include "title_screen.hpp"

void TitleScreen::Init()
{
	texTitle = LoadTexture("resources/Menu/PacMan_MainLogo.png");
	authorText = "by Alberto G.";
	startGameText = "PRESS [ENTER] to START";
	goToOptionsText = "PRESS [0] for INSTRUCTIONS";
	framesCounter = 0;
	finishScreen = 0;

	SoundManager::GetInstance()->PlayMusic("resources/Audio/Music/IntroTheme.mp3");

}

void TitleScreen::Update()
{
	framesCounter++;
	SoundManager::GetInstance()->UpdateMusic();

	// Press enter to change to GAMEPLAY screen
	if (IsKeyPressed(KEY_ENTER))
		finishScreen = 4;   // GAMEPLAY

	if (IsKeyPressed(KEY_O)) {
		finishScreen = 3; // OPTIONS
		SoundManager::GetInstance()->UnloadMusic();
	}
}

void TitleScreen::Draw()
{
	DrawTexture(texTitle, SCR_WIDTH / 2 - texTitle.width / 2, SCR_HEIGHT / 4 - 80, WHITE);
	DrawText(authorText, SCR_WIDTH / 2 - MeasureText(authorText, 20) / 2, GetScreenHeight() / 4 + 180, 20, DARKGRAY);

	if ((framesCounter / 30) % 2 == 0)
	{
		DrawText(startGameText, GetScreenWidth() / 2 - MeasureText(startGameText, 20) / 2, GetScreenHeight() / 2 + 120, 20, GRAY);
		DrawText(goToOptionsText, GetScreenWidth() / 2 - MeasureText(goToOptionsText, 20) / 2, GetScreenHeight() / 2 + 140, 20, DARKGRAY);
	}
}
