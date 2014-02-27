#include "GameObject.h"

GameObject::GameObject()
{
	x = 0;
	y = 0;

	velX = 0;
	velY = 0;

	dirX = 0;
	dirY = 0;

	boundX = 0;
	boundY = 0;

	maxFrame = 0;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	animationColumns = 0;
	animationDirection = 0;

	image = NULL;

	alive = true;
	collidable = true;
}

void GameObject::Destroy()
{
}

void GameObject::Init(float x, float y, float velX, float velY, int dirX, int dirY, int boundX, int boundY){
	GameObject::x = x;
	GameObject::y = y;

	GameObject::velX = velX;
	GameObject::velY = velY;

	GameObject::dirX = dirX;
	GameObject::dirY = dirY;

	GameObject::boundX = boundX;
	GameObject::boundY = boundY;

}
void GameObject::Update()
{
	x += velX*dirX;
	y += velY*dirY;
}
void GameObject::Render()
{}

bool GameObject::CheckCollisions(GameObject *pOtherObject)
{
	//using bounding boxes
	float oX = pOtherObject->getX();
	float oY = pOtherObject->getY();

	int oBX = pOtherObject->getBoundX();
	int oBY = pOtherObject->getBoundY();

	if (x + boundX > oX - oBX &&
		x - boundX < oX + oBX &&
		y + boundY > oY - oBY &&
		y - boundY < oY + oBY)
		return true;
	else
		return false;

}
void GameObject::Collided(int objectID)
{

}
bool GameObject::Collidable()
{
	return alive && collidable;
}