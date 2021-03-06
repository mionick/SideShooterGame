#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <list>
#include <string>
#include <iostream>

#include "Globals.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Comet.h"
#include "SpaceShip.h"
#include "Explosion.h"
#include "Background.h"
#include "PowerUp.h"
#include "CharEntry.h"
#include "HighscoreSaver.h"



bool keys[] = { false, false, false, false, false };
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};

//globals
SpaceShip *ship;
std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;

Background *titleScreen = NULL;
Background *loseScreen = NULL;

ALLEGRO_SAMPLE_INSTANCE *songInstance;

//prototypes
//function pointers
void __cdecl TakeLife();
void __cdecl ScorePoint();
void __cdecl ChangeWeapon(int type);


//for gnu compilers it looks like this:
// void TakeLife() __attribute__((cdecl));

void ChangeState(int &state, int newState);

int main(int argc, char **argv)
{
	//===========================================
	//SHELL VARIABLES
	//===========================================
	bool done = false;
	bool render = false;
	int state = -1;

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;

	int spawnRate = 100;
	int prevScore = 0;

	const int textDelay = 7;
	int currentTry = textDelay-1;


	//===========================================
	//PROJECT VARIABLES
	//===========================================
	ship = new SpaceShip;
	CharEntry *menu = new CharEntry;
	HighscoreSaver *scoreSaver = new HighscoreSaver;
	string playerName;

	ALLEGRO_BITMAP *pauseImage = NULL;

	ALLEGRO_BITMAP *shipImage = NULL;
	ALLEGRO_BITMAP *cometImage = NULL;
	ALLEGRO_BITMAP *explosionImage = NULL;

	ALLEGRO_BITMAP *bgImage = NULL;
	ALLEGRO_BITMAP *mgImage = NULL;
	ALLEGRO_BITMAP *fgImage = NULL;

	ALLEGRO_BITMAP *titleImage = NULL;
	ALLEGRO_BITMAP *loseImage = NULL;

	ALLEGRO_BITMAP *alphabetImage = NULL;
	ALLEGRO_BITMAP *cursorImage = NULL;

	ALLEGRO_SAMPLE *shot = NULL;
	ALLEGRO_SAMPLE *boom = NULL;
	ALLEGRO_SAMPLE *song = NULL;




	//===========================================
	//ALLEGRO VARIBABLES
	//===========================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *font2 = NULL;

	//===========================================
	//ALLEGRO INIT FUNCTIONS
	//===========================================
	if (!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if (!display)
		return -2;

	//===========================================
	//ADDON INSTALL
	//===========================================
	al_install_keyboard();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();


	//===========================================
	//PROJECT INIT
	//===========================================
	font = al_load_font("ARDELANEY.ttf", 18, 0);
	font2 = al_load_font("ARDELANEY.ttf", 36, 0);
	al_reserve_samples(15);

	shipImage = al_load_bitmap("ship.png");
	al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255));
	ship->Init(shipImage);

	bgImage = al_load_bitmap("starBG.png");
	mgImage = al_load_bitmap("starMG.png");
	fgImage = al_load_bitmap("starFG.png");

	Background *BG = new Background(bgImage, 1);
	Background *MG = new Background(mgImage, 2);
	Background *FG = new Background(fgImage, 4);


	//Backgrounds must be in objects list before ship is.
	objects.push_back(BG);
	objects.push_back(MG);
	objects.push_back(FG);

	objects.push_back(ship);

	cometImage = al_load_bitmap("asteroid.png");

	explosionImage = al_load_bitmap("explosion.png");

	titleImage = al_load_bitmap("Shooter_Title.png");
	loseImage = al_load_bitmap("Shooter_Lose.png");

	titleScreen = new Background(titleImage, 0);
	loseScreen = new Background(loseImage, 0);

	shot = al_load_sample("shot.wav");
	boom = al_load_sample("boom.wav");
	//song = al_load_sample("nappa.wav");

	song = al_load_sample("Another Winter -Anamanaguchi.wav");

	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(songInstance, 2.0);

	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	//Initializing textEntry stuff
	alphabetImage = al_load_bitmap("ALPHABET.bmp");
	//making the cursor
	cursorImage = al_create_bitmap(52, 40);
	al_set_target_bitmap(cursorImage);
	al_draw_line(0, 0, 0, 20, al_map_rgb(0, 255, 0), 3);
	al_draw_line(0, 0, 25, 0, al_map_rgb(0, 255, 0), 3);
	al_draw_line(52, 20, 52, 36, al_map_rgb(0, 255, 0), 3);
	al_draw_line(25, 36, 52, 36, al_map_rgb(0, 255, 0), 3);
	al_set_target_backbuffer(display);

	menu->Init(52, 35, alphabetImage, cursorImage);

	ChangeState(state, TITLE);

	srand(time(NULL));

	//===========================================
	//TIMER INIT AND STARTUP
	//===========================================
	queue = al_create_event_queue();
	timer = al_create_timer(1.0/60.0);

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	gameTime = al_current_time();
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);

		//===========================================
		//INPUT
		//===========================================
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_BACKSPACE:
				if (state == ENTERNAME)
					menu->Backspace();
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				if (state == TITLE)
					ChangeState(state, PLAYING);
				else if (state == PLAYING)
				{
					Bullet *bullet = new Bullet(ship->getX() + 17, ship->getY(), ScorePoint, ship->getWeapon(), ship->getWeaponLevel());
					objects.push_back(bullet);
					al_play_sample(shot, 0.7, 0, 2, ALLEGRO_PLAYMODE_ONCE, NULL);

				}
				else if (state == ENTERNAME)
				{
					menu->Enter();
				}
				else if (state == HIGHSCORE)
				{
					scoreSaver->Reset();
					ChangeState(state, LOST);
				}
				else if (state == LOST)
					ChangeState(state, PLAYING);
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (state == ENTERNAME)
				currentTry = textDelay - 1;
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		//===========================================
		//GAME UPDATE (MODEL)
		//===========================================
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//UPDATE FPS
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//===========
			//PLAYING
			if (state == PLAYING)
			{
			if (keys[UP])
				ship->MoveUp();
			else if (keys[DOWN])
				ship->MoveDown();
			else
				ship->ResetAnimation(1);

			if (keys[LEFT])
				ship->MoveLeft();
			else if (keys[RIGHT])
				ship->MoveRight();
			else
				ship->ResetAnimation(2);

			if (spawnRate > 15 && prevScore != ship->GetScore())
			{
				spawnRate--;
				prevScore = ship->GetScore();
			}

			if (!ship->getCollidable())
			{
				if (al_current_time() - ship->getInvincibleSince() >= 5)
					ship->setCollidable(true);
			}

			if (rand() % spawnRate == 0)
			{
				Comet *comet = new Comet(WIDTH, 30 + rand() % (HEIGHT - 60), cometImage, TakeLife);
				objects.push_back(comet);
			}


				//UPDATES
				for (iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->Update();

				//COLLISIONS

				for (iter = objects.begin(); iter != objects.end(); ++iter)
				{
					if (!(*iter)->Collidable())
						continue;
					for (iter2 = iter; iter2 != objects.end(); ++iter2)
					{
						if (!(*iter2)->Collidable()) continue;
						if ((*iter)->getID() == (*iter2)->getID()) continue;
						//collide if collidable and not same type
						if ((*iter)->getID() == POWERUP && (*iter2)->getID() != PLAYER ||
							(*iter2)->getID() == POWERUP && (*iter)->getID() != PLAYER)
							continue;
						//if a powerup collides with anything but the player, skip
						if ((*iter)->getID() == BULLET && (*iter2)->getID() == PLAYER ||
							(*iter2)->getID() == BULLET && (*iter)->getID() == PLAYER)
							continue;
						//if player and BULLET collide, skip

						if ((*iter)->CheckCollisions((*iter2)))
						{
							(*iter2)->Collided((*iter)->getID());
							(*iter)->Collided((*iter2)->getID());


							//Explode if neither object was a powerup
							if ((*iter)->getID() != POWERUP &&
								(*iter2)->getID() != POWERUP)
							{

								Explosion *explosion = new Explosion(((*iter)->getX() + (*iter2)->getX()) / 2,
									((*iter)->getY() + (*iter2)->getY()) / 2, explosionImage);

								objects.push_back(explosion);
								al_play_sample(boom, 1, 0, 2, ALLEGRO_PLAYMODE_ONCE, NULL);

								if (rand() % 6 == 0)
								{
									PowerUp *powerup = new PowerUp(((*iter)->getX() + (*iter2)->getX()) / 2, ((*iter)->getY() + (*iter2)->getY()) / 2, rand() % 4, shipImage, ChangeWeapon);
									objects.push_back(powerup);
								}
							}
							else if ((*iter)->getID() == POWERUP)
							{
							}
							else if ((*iter2)->getID() == POWERUP)
							{

							}
						}
					}
				}

				if (ship->GetLives() <= 0)
				{
					if (ship->GetScore() > scoreSaver->GetLowest())
						ChangeState(state, ENTERNAME);
					else
						ChangeState(state, HIGHSCORE);
					spawnRate = 100;
				}
			}
			else if (state == ENTERNAME)
			{
				if (menu->GetDone())
				{
					playerName = menu->GetName();
					scoreSaver->AddToList(playerName, ship->GetScore());
					menu->Reset();
					ChangeState(state, HIGHSCORE);
				}
				else if (keys[UP])
				{
					if (currentTry == textDelay)
					{
						menu->MoveUp();
						currentTry = 0;
					}
					else
						currentTry++;

				}
				else if (keys[DOWN])
				{
					if (currentTry == textDelay)
					{
					menu->MoveDown();
					currentTry = 0;
					}
					else
						currentTry++;

				}
				else if (keys[RIGHT])
				{
					if (currentTry == textDelay)
					{
					menu->MoveRight();
					currentTry = 0;
					}
					else
						currentTry++;

				}
				else if (keys[LEFT])
				{
					if (currentTry == textDelay)
					{
					menu->MoveLeft();
					currentTry = 0;
					}
					else
						currentTry++;

				}

			}
			//CULL THE DEAD
			
			for (iter = objects.begin(); iter != objects.end();)
			{
				if (!(*iter)->getAlive())
				{
					delete (*iter);
					iter = objects.erase(iter);
				}
				else
					iter++;
			}
			
		}
		//===========================================
		//RENDER (VIEW)
		//===========================================
		if (render && al_is_event_queue_empty(queue))
		{
			if (state == TITLE)
			{
				titleScreen->Render();
			}
			else if (state == PLAYING)
			{
				for (iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->Render();

				al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 5, 0, "Lives: %i Score: %i SpawnRate: %i", ship->GetLives(), ship->GetScore(), spawnRate);

			}
			else if (state == ENTERNAME)
			{
				menu->Render(WIDTH / 2, HEIGHT / 2);
			}
			else if (state == HIGHSCORE)
			{
				scoreSaver->Render(10, 10, font2);
			}
			else if (state == LOST)
			{
				loseScreen->Render();
			}
			else if (state == PAUSE)
			{
				//al_draw_bitmap(pauseImage, 0, 0, 0);
				al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "PAUSED");
			}
			render = false;

			//FLIP BUFFERS
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));

		}


	}


	//===========================================
	//DESTROY PROJECT OBJECTS
	//===========================================
	for (iter = objects.begin(); iter != objects.end();)
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}

	titleScreen->Destroy();
	loseScreen->Destroy();
	delete titleScreen;
	delete loseScreen;

	al_destroy_bitmap(cursorImage);
	al_destroy_bitmap(alphabetImage);

	al_destroy_bitmap(pauseImage);

	al_destroy_bitmap(titleImage);
	al_destroy_bitmap(loseImage);


	al_destroy_bitmap(cometImage);
	al_destroy_bitmap(shipImage);
	al_destroy_bitmap(explosionImage);

	//SHELL VARIABLES============================
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(mgImage);
	al_destroy_bitmap(fgImage);

	al_destroy_sample(shot);
	al_destroy_sample(boom);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);

	

	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_destroy_display(display);

	return 0;
}

void __cdecl TakeLife()
{
	ship->LoseLife();
}
void __cdecl ScorePoint()
{
	ship->addPoint();
}
void __cdecl ChangeWeapon(int type)
{
	ship->ChangeWeapon(type);
}


void ChangeState(int &state, int newState)
{
	if (state == TITLE)
	{

	}
	else if (state == PLAYING)
	{
		for (iter = objects.begin(); iter != objects.end(); iter++)
		{
			if ((*iter)->getID() != PLAYER && (*iter)->getID() != MISC)
				(*iter)->setAlive(false);
		}
		al_stop_sample_instance(songInstance);

	}
	else if (state == LOST)
	{

	}
	else if (state == PAUSE)
	{
	}

	state = newState;

	if (state == TITLE)
	{

	}
	else if (state == PLAYING)
	{
		ship->Init();
		al_play_sample_instance(songInstance);
	}
	else if (state == LOST)
	{

	}
	else if (state == PAUSE)
	{

	}

}