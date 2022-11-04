#ifndef LOGOSCREEN_H
#define LOGOSCREEN_H
#include "screen.hpp"

class LogoScreen : public Screen {
private:
	int logoPositionX;
	int logoPositionY;

	int lettersCount;

	int topSideRecWidth;
	int leftSideRecHeight;

	int bottomSideRecWidth;
	int rightSideRecHeight;

	float alpha;         // Useful for fading

	Texture2D texLogo;

public:

	void LogoScreen::Init() override;
	void LogoScreen::Update() override;
	void LogoScreen::Draw() override;
	void LogoScreen::Unload() override;

};
#endif // !LOGO_SCREEN_H

