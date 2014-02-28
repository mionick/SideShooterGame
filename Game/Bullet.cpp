#include "Bullet.h"

Bullet::Bullet(float x, float y, void(*ScorePoint)(void), int type, int level)
{
	if (type == NORMAL)
		GameObject::Init(x, y, 10, 0, 1, 0, 0, 0);
	else 	if (type == WIDE)
	{
		GameObject::Init(x, y, 10, 0, 1, 0, 0, 10*level);
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

}
void Bullet::Render()
{
	if (type == NORMAL)
		al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255));
	else if (type == WIDE)
		al_draw_line(x, y - getBoundY(), x, y + getBoundY(), al_map_rgb(0, 255, 0), 1);
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

	}

	if (ObjectID == ENEMY)
		ScorePoint();
}