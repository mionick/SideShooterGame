#include "SpaceShip.h"
SpaceShip::SpaceShip()
{
}

void SpaceShip::Destroy()
{
	GameObject::Destroy();
}

void SpaceShip::Init(ALLEGRO_BITMAP *image)
{
	GameObject::Init(20, HEIGHT / 2, 6, 6, 0, 0, 10, 12);

	setID(PLAYER);
	setAlive(true);

	lives = 3;
	score = 0;

	maxFrame = 3;
	curFrame = 0;
	frameWidth = 43;
	frameHeight = 41;
	animationColumns = 3;
	animationDirection = 1;

	animationRow = 1;

	if (image != NULL)
		SpaceShip::image = image;

	weapon = NORMAL;
	weaponLevel = 1;

}
void SpaceShip::Update()
{
	GameObject::Update();
	if (x < 0)
		x = 0;
	else if (x > WIDTH)
		x = WIDTH;

	if (y < 0)
		y = 0;
	else if (y > HEIGHT)
		y = HEIGHT;
}
void SpaceShip::Render()
{
	GameObject::Render();

	int fx = (curFrame%animationColumns)*frameWidth;
	int fy = animationRow*frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);

	if (!getCollidable())
		al_draw_filled_circle(x, y, 20, al_map_rgba(0, 0, 255, 100));


}

void SpaceShip::MoveUp()
{
	animationRow = 0;
	dirY = -1;
}
void SpaceShip::MoveDown()
{
	animationRow = 2;
	dirY = 1;
}
void SpaceShip::MoveLeft()
{
	curFrame = 2;
	dirX = -1;
}
void SpaceShip::MoveRight()
{
	curFrame = 1;
	dirX = 1;
}

void SpaceShip::LoseLife()
{
	if (getCollidable())
		lives--;
}

void SpaceShip::ResetAnimation(int position)
{
	if (position == 1)
	{
		animationRow = 1;
		dirY = 0;
	}
	else
	{
		curFrame = 0;
		dirX = 0;
	}
}

void SpaceShip::Collided(int objectID)
{
	if (objectID == ENEMY)
		lives--;

	if (objectID == POWERUP)
	{
		score += 21;
	}
}

void SpaceShip::ChangeWeapon(int newWeapon)
{
	if (newWeapon != SHIELD && newWeapon != LIFE)
	{
		if (weapon != newWeapon)
		{
			weapon = newWeapon;
			weaponLevel = 1;
		}
		else
			weaponLevel++;
	}
	else if (newWeapon == SHIELD)
	{
		setCollidable(false);
		invincibleSince = al_current_time();
	}
	else if (newWeapon == LIFE)
		AddLife();
}
