#pragma once

#include "GameObject.h"

class SpaceShip : public GameObject
{
private:
	int lives;
	int score;
	int animationRow;

	int weapon;
	int weaponLevel;

	int invincibleSince;
public:
	SpaceShip();
	void Destroy();
	
	void Init(ALLEGRO_BITMAP *image = NULL);
	void Update();
	void Render();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void ResetAnimation(int position);

	int GetLives() { return lives; }
	int GetScore() { return score; }

	void LoseLife();
	void AddLife() { lives++; }
	void addPoint() { score += 10; }

	int getWeapon() { return weapon; }
	void setWeapon(int newWeapon) { weapon = newWeapon; }

	int getWeaponLevel() { return weaponLevel; }
	int setWeaponLevel(int newWL) { weaponLevel = newWL; }

	int getInvincibleSince() { return invincibleSince; }
	void setInvincibleSince(int time) { invincibleSince = time; }

	void Collided(int objectID);

	void ChangeWeapon(int newWeapon);

};