#pragma once
#include <iostream>
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>

/*
Text file must contain text pairs, in this format:
NAME--- SCORE----------\n
*/
using namespace std;

const int maxNum = 8;

class HighscoreSaver
{
public:
	HighscoreSaver();
	~HighscoreSaver();

	void CreateNewFile();
	void AddToList(string name, int score);
	void SaveList();

	void Render(int X, int Y, ALLEGRO_FONT *font);

	int GetLowest() { return lowest; }

	void Reset();

private:
	string name[maxNum];
	int score[maxNum];
	int numOfEntries;

	int lowest;

	int newEntry;



};