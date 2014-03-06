#include "CharEntry.h"
#include <allegro5\allegro.h>

CharEntry::CharEntry(){
	cursorPosition = 0;
	currentSize = 0;
	name = "";

	done = false;
}

//Image must be a square image with no padding at the border.
void CharEntry::Init(int charWidth, int charHeight, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *cursorImage)
{
	CharEntry::charWidth = charWidth;
	CharEntry::charHeight = charHeight;

	CharEntry::image = image; 
	CharEntry::cursorImage = cursorImage;
}

void CharEntry::Render(int centerX, int centerY)
{
	al_draw_bitmap(image, centerX - al_get_bitmap_width(image)/2, centerY, 0);
	al_draw_bitmap(cursorImage, centerX - al_get_bitmap_width(image)/2 + (cursorPosition % 13)*charWidth, centerY + (cursorPosition / 13)*charHeight, 0);

	int empty = maxSize - currentSize;
	for (int i = 0; i < currentSize; i++)
	{
		al_draw_bitmap_region(image, (chars[i] % 13)*charWidth, (chars[i] / 13)*charHeight, charWidth, charHeight, centerX - maxSize*charWidth / 2 + i*charWidth,
			centerY - charHeight * 2, 0);
	}
}
void CharEntry::Update(){}
void CharEntry::Destroy(){}

void CharEntry::MoveUp()
{
	cursorPosition -= 13;
	if (cursorPosition < 0)
		cursorPosition += 39;
}
void CharEntry::MoveDown()
{
	cursorPosition += 13;
	if (cursorPosition >= 39)
		cursorPosition -= 39;
}
void CharEntry::MoveLeft()
{
	if (cursorPosition % 13 == 0)
		cursorPosition += 12;
	else
		cursorPosition--;

}
void CharEntry::MoveRight()
{
	if (cursorPosition % 13 == 12)
		cursorPosition -= 12;
	else
		cursorPosition++;
}
void CharEntry::Enter()
{
	if (cursorPosition < 36)
	{
		if (currentSize < maxSize)
		{
			chars[currentSize] = cursorPosition;
			currentSize++;
		}
	}
	else if (cursorPosition == 37)
	{
		Backspace();
	}
	else if (cursorPosition == 38)
	{
		Done();
	}
}
void CharEntry::Backspace()
{
	currentSize--;
	chars[currentSize] = 0;
}
void CharEntry::Done()
{
	done = true;
}
string CharEntry::GetName()
{
	for (int i = 0; i < currentSize; i++)
	{
		if (chars[i] < 26)
			name.append(1, static_cast<char>(chars[i] + 65));
		else
			name.append(1, static_cast<char>(chars[i] + 22));
	}
	name.append(maxSize - currentSize, '-');

	return name;
}
void CharEntry::Reset()
{
	done = false;
	name = "";
	currentSize = 0;
}
