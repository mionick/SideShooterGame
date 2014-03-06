#pragma once

#include <allegro5\allegro.h>
#include "Globals.h"
# include <string>

using namespace std;

int const maxSize = 8;

class CharEntry
{
public:
	CharEntry();

	//Image must be a square image with no padding at the border.
	void Init(int charWidth, int charHeight, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *cursorImage);

	void Render(int centerX, int centerY);
	void Update();
	void Destroy();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Enter();
	void Backspace();
	void Done();
	void Reset();

	bool GetDone() { return done; }
	string GetName();

	int GetCurrentSize() { return currentSize; } 
	int GetCursorPosition() { return cursorPosition; }

private:

	int charWidth;
	int charHeight;

	int cursorPosition;
	int currentSize;

	int chars[maxSize];
	string name;

	bool done;

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *cursorImage;

};