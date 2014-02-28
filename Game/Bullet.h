#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
private:
	void(*ScorePoint)(void);
	
	int type;
	int level;

public:
	Bullet(float x, float y, void(*ScorePoint)(void), int type = NORMAL, int level = 1);
	void Destroy();

	int getType() { return type; }
	void setType(int type) { Bullet::type = type; }

	int getLevel() { return level; }
	void setLevel(int level) { Bullet::level = level; }

	void Update();
	void Render();
	void Collided(int ObjectID);
};