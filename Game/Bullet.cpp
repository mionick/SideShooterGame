#include "Bullet.h"

Bullet::Bullet(float x, float y, void(*ScorePoint)(void), int type, int level)
{
	 
	if (type == NORMAL)
		GameObject::Init(x, y, 10, 0, 1, 0, 0, 1+level);
	else if (type == WIDE)
	{
		GameObject::Init(x, y, 10, 0, 1, 0, 0, 10*level);
	}
	else if (type == BARRIER)
	{
		GameObject::Init(x, y, 14, 0, 1, 0, 0, 25);
		cyclesLeft = 10+ 15 * level;

	}
	setID(BULLET);

	Bullet::ScorePoint = ScorePoint;

	Bullet::type = type;
	Bullet::level = level;


}

void Bullet::Destroy()
{
	GameObject::Destroy();
}

void Bullet::Update()
{
	GameObject::Update();

	if (x > WIDTH)
		Collided(BORDER);

	if (type == BARRIER)
	{
		cyclesLeft--;
		if (velX > 0)
		{
			velX--;
		}
		if (cyclesLeft <= 0)
		{
			setAlive(false);
		}
	}

}
void Bullet::Render()
{
	if (type == NORMAL)
		al_draw_filled_circle(x, y, 1 + level, al_map_rgb(255, 255, 255));
	else if (type == WIDE)
		al_draw_line(x, y - getBoundY(), x, y + getBoundY(), al_map_rgb(0, 255, 0), 1);
	else if (type == BARRIER)
	{
		al_draw_line(x, y - getBoundY(), x, y + getBoundY(), al_map_rgb(0, 255, 255), 5);

		al_draw_line(x, y - getBoundY()+1, x, y + getBoundY()-1, al_map_rgb(0, 0, 100), 1);

	}
}
void Bullet::Collided(int ObjectID)
{
	if (ObjectID == ENEMY || ObjectID == BORDER)
		//if (ObjectID == BORDER)
	{
		if (type == NORMAL)
			level--;
		if (type == WIDE || level == 0)
			setAlive(false);
		if (type == BARRIER)
		{

		}

	}

	if (ObjectID == ENEMY)
		ScorePoint();
}