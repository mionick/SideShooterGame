#pragma once

#include "GameObject.h"

class Comet : public GameObject
{
private:
	// returnTypeOfFunc (*nameOfPointer)(FunctionPArameteers)
	void(*TakeLife)(void);
public:
	Comet(float x, float y, ALLEGRO_BITMAP *image, void (*TakeLife)(void));
	void Destroy();
	void Render();
	void Update();

	void Collided(int ObjectID);
};