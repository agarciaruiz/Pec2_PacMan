#include "main.hpp"

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    currentScreen = Screens::LOGO;
    transAlpha = 0.0f;
    onTransition = false;
    transFadeOut = false;
    transFromScreen = -1;
    transToScreen = Screens::NONE;

    InitWindow(SCR_WIDTH, SCR_HEIGHT, "PacMan - Alberto Garcia");

    InitAudioDevice();      // Initialize audio device

    // Setup and init first screen
    currentScreen = LOGO;

    //InitLogoScreen();
    logoScreen.Init();

    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload current screen data before closing
    switch (currentScreen)
    {
        case LOGO: logoScreen.Unload(); break;
        case TITLE: titleScreen.Unload(); break;
        case OPTIONS: optionsScreen.Unload(); break;
        case GAMEPLAY: gameScreen.Unload(); break;
        case ENDING: endingScreen.Unload(); break;
        default: break;
    }

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
static void ChangeToScreen(Screens screen)
{
    // Unload current screen
    switch (currentScreen)
    {
        case LOGO: logoScreen.Unload(); break;
        case TITLE: titleScreen.Unload(); break;
        case OPTIONS: optionsScreen.Unload(); break;
        case GAMEPLAY: gameScreen.Unload(); break;
        case ENDING: endingScreen.Unload(); break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO: logoScreen.Init(); break;
        case TITLE: titleScreen.Init(); break;
        case OPTIONS: optionsScreen.Init(); break;
        case GAMEPLAY: gameScreen.Init(); break;
        case ENDING: endingScreen.Init(); break;
        default: break;
    }

    currentScreen = screen;
}

// Request transition to next screen
static void TransitionToScreen(Screens screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO: logoScreen.Unload(); break;
                case TITLE: titleScreen.Unload(); break;
                case OPTIONS: optionsScreen.Unload(); break;
                case GAMEPLAY: gameScreen.Unload(); break;
                case ENDING: endingScreen.Unload(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                case LOGO: logoScreen.Init(); break;
                case TITLE: titleScreen.Init(); break;
                case OPTIONS: optionsScreen.Init(); break;
                case GAMEPLAY: gameScreen.Init(); break;
                case ENDING: endingScreen.Init(); break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = NONE;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Update and draw game frame
static void UpdateDrawFrame()
{
    // Update
    //----------------------------------------------------------------------------------

    if (!onTransition)
    {
        switch(currentScreen)
        {
            case LOGO:
            {
                logoScreen.Update();

                if (logoScreen.FinishScreen()) TransitionToScreen(TITLE);

            } break;
            case TITLE:
            {
                titleScreen.Update();

                if (titleScreen.FinishScreen() == 3) TransitionToScreen(OPTIONS);
                else if (titleScreen.FinishScreen() == 4) TransitionToScreen(GAMEPLAY);

            } break;
            case OPTIONS:
            {
                optionsScreen.Update();

                if (optionsScreen.FinishScreen() == 2) TransitionToScreen(TITLE);

            } break;
            case GAMEPLAY:
            {
                gameScreen.Update();

                if (gameScreen.FinishScreen() == 5) TransitionToScreen(ENDING);

            } break;
            case ENDING:
            {
                endingScreen.Update();

                if (endingScreen.FinishScreen() == 2) TransitionToScreen(TITLE);
                else if (endingScreen.FinishScreen() == 3) TransitionToScreen(OPTIONS);

            } break;
            default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(BLACK);

        switch(currentScreen)
        {
            case LOGO: logoScreen.Draw(); break;
            case TITLE: titleScreen.Draw(); break;
            case OPTIONS: optionsScreen.Draw(); break;
            case GAMEPLAY: gameScreen.Draw(); break;
            case ENDING: endingScreen.Draw(); break;
            default: break;
        }

        // Draw full screen rectangle in front of everything
        if (onTransition) DrawTransition();

        //DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
