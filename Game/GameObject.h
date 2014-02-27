#pragma once
#include <iostream>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include "Globals.h"


class GameObject
{
public:
	GameObject();

	void virtual Destroy();

	void Init(float x, float y, float velX, float velY, int dirX, int dirY, int boundX, int boundY);
	void virtual Update();
	void virtual Render();

	float getX() { return x; }
	float getY() { return y; }

	void setX(float x) { GameObject::x = x; }
	void setY(float y) { GameObject::y = y; }

	int getBoundX() { return boundX; }
	int getBoundY() { return boundY; }

	int getID() { return ID; }
	void setID(int ID) { GameObject::ID = ID; }

	bool getAlive(){ return alive; }
	void setAlive(bool alive) { GameObject::alive = alive; }

	bool getCollidable() { return collidable; }
	void setCollidable(bool collidable) { GameObject::collidable = collidable; }

	bool CheckCollisions(GameObject *pOtherObject);
	void virtual Collided(int objectID);
	bool Collidable();

private:
	int ID;
	bool alive;
	bool collidable;

protected:
	float x;
	float y;
	
	float velX;
	float velY;

	int dirX;
	int dirY;

	int boundX;
	int boundY;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	ALLEGRO_BITMAP *image;

};

