#ifndef OPTIONSCREEN_H
#define OPTIONSCREEN_H
#include "screen.hpp"
#include <string>

class OptionsScreen : public Screen {
private:
	char* instructions1;
	char* instructions2;
	char* instructions3;

	char* instructions4;
	char* instructions5;
	char* instructions6;
public:
	void OptionsScreen::Init() override;
	void OptionsScreen::Update() override;
	void OptionsScreen::Draw() override;
};

#endif
