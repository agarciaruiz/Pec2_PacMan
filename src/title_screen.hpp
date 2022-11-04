#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H
#include "screen.hpp"

class TitleScreen : public Screen {
private:
	Texture2D texTitle;

public:
	void TitleScreen::Init() override;
	void TitleScreen::Update() override;
	void TitleScreen::Draw() override;
};

#endif
