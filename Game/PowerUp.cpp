#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, int type, ALLEGRO_BITMAP *image, void(*ChangeWeapon)(int))
{
	GameObject::Init(x, y, 3, 3, -1, (rand() % 3) - 1, 7, 7);
	PowerUp::type = type;

	setID(POWERUP);


	maxFrame = 6;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 100;
	frameHeight = 100;
	animationColumns = 3;
	animationDirection = 1;

	PowerUp::image = image;

	PowerUp::ChangeWeapon = ChangeWeapon;

}

void PowerUp::Destroy()
{
	GameObject::Destroy();
}
void PowerUp::Update()
{
	GameObject::Update();

	if ((y <= 0) || (y >= HEIGHT))
		velY *= -1;

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
void PowerUp::Render()
{
	if (type == NORMAL)
	{
		al_draw_filled_circle(x, y, 7, al_map_rgb(100, 100, 255));
		al_draw_filled_circle(x, y, 4, al_map_rgb(255, 100, 100));
	}
	else if (type == WIDE)
	{
		al_draw_filled_circle(x, y, 7, al_map_rgb(255, 100, 100));
		al_draw_filled_circle(x, y, 4, al_map_rgb(100, 100, 255));
	}
	else if (type == SHIELD)
	{
		al_draw_filled_circle(x, y, 7, al_map_rgb(0, 0, 255));
	}
	else if (type == LIFE)
	{
		al_draw_filled_circle(x, y, 7, al_map_rgb(255, 0, 0));
		al_draw_line(x, y - 7, x, y + 7, al_map_rgb(255, 255, 255), 3);
		al_draw_line(x-7, y, x+7, y, al_map_rgb(255, 255, 255), 3);

	}
}

void PowerUp::Collided(int objectID)
{
	if (objectID == PLAYER)
	{
		setAlive(false);
		ChangeWeapon(type);
	}
	else if (objectID == BORDER)
	{
		setAlive(false);
	}
}
