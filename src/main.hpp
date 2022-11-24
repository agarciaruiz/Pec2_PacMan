#ifndef MAIN_H
#define MAIN_H

#include "logo_screen.hpp"
#include "title_screen.hpp"
#include "game_screen.hpp"
#include "ending_screen.hpp"
#include "options_screen.hpp"
#include "raylib.h"

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
Screens currentScreen;

LogoScreen logoScreen;
TitleScreen titleScreen;
GameScreen gameScreen;
EndingScreen endingScreen;
OptionsScreen optionsScreen;

// Required variables to manage screen transitions (fade-in, fade-out)
float transAlpha;
bool onTransition;
bool transFadeOut;
int transFromScreen;
Screens transToScreen;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
void ChangeToScreen(Screens screen);     // Change to screen, no transition effect
void TransitionToScreen(Screens screen); // Request transition to next screen
void UpdateTransition(void);         // Update transition effect
void DrawTransition(void);           // Draw transition effect (full-screen rectangle)
void UpdateDrawFrame();          // Update and draw one frame

#endif