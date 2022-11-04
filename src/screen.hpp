#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"
#include "global.h"

class Screen {
protected:
	int framesCounter;
	int finishScreen;
	Font font {};

public:
	int Screen::FinishScreen() const;

	virtual void Screen::Init();
	virtual void Screen::Update();
	virtual void Screen::Draw();
	virtual void Screen::Unload();
};
#endif // SCREENS_H