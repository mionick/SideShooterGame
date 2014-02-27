#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
private:
	void(*ScorePoint)(void);
public:
	Bullet(float x, float y, void(*ScorePoint)(void));
	void Destroy();

	void Update();
	void Render();
	void Collided(int ObjectID);
};