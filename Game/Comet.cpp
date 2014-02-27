#include "Comet.h"


Comet::Comet(float x, float y, ALLEGRO_BITMAP *image, void(*TakeLife)(void))
{
	GameObject::Init(x, y, 5, 0, -1, 0, 35, 35);

	setID(ENEMY);

	maxFrame = 143;
	curFrame = rand() % 143;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 96;
	frameHeight = 96;
	animationColumns = 21;

	if (rand() % 2)
		animationDirection = 1;
	else
		animationDirection = -1;

	Comet::image = image;

	Comet::TakeLife = TakeLife;
	//might have to use this instead:
	//Comet::TakeLife = &TakeLife;

}
void Comet::Destroy()
{
	GameObject::Destroy();
}

void Comet::Update()
{
	GameObject::Update();

	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame)
			curFrame = 0;
		else if (curFrame <= 0)
			curFrame = maxFrame;
	
		frameCount = 0;
	}

	if (x + frameWidth < 0)

		Collided(BORDER);

}

void Comet::Render()
{
	GameObject::Render();

	int fx = (curFrame % animationColumns) *frameWidth;
	int fy = (curFrame / animationColumns) *frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);

}

void Comet::Collided(int ObjectID)
{
	if (ObjectID == BORDER)
	{
		TakeLife();
	}

	if (ObjectID != ENEMY)
		setAlive(false);
}
