#pragma once

#include "GameObject.h"

class PowerUp : public GameObject
{
private:
	int type;

	void setType(int type);
	int getType() { return type; }

	void (*ChangeWeapon)(int);

public:
	PowerUp(float x, float y, int type, ALLEGRO_BITMAP *image, void (*ChangeWeapon)(int));

	void Destroy();
	void Update();
	void Render();

	void Collided(int ObjectID);


};