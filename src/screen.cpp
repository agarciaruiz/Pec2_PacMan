#include "screen.hpp"

int Screen::FinishScreen() const { return finishScreen; }

void Screen::Init()
{
	framesCounter = 0;
	finishScreen = 0;
	font = LoadFont("resources/Font/mecha.png");
}

void Screen::Update() {}
void Screen::Draw() {}

void Screen::Unload()
{
	UnloadFont(font);
}