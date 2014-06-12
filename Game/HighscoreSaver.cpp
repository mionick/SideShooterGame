#include "HighscoreSaver.h"
#include <fstream>

HighscoreSaver::HighscoreSaver()
{
	fstream inputFile;
	inputFile.open("score", ios::in);
	
	string name;
	int score;
	int count = 0;

	while (inputFile >> name && inputFile >> score && count< maxNum)
	{
		HighscoreSaver::name[count].assign(name);
		HighscoreSaver::score[count] = score;
		count++;
	}

	inputFile.close();
	
	numOfEntries = count;
	lowest = HighscoreSaver::score[count-1];
}
HighscoreSaver::~HighscoreSaver(){}


void HighscoreSaver::AddToList(string name, int score)
{
	int count = 0;

	while (count < maxNum && score <= HighscoreSaver::score[count])
		count++;
	//our score should go in score[count]
	//shift all from count downward by one.
	if (count != maxNum)
	{
		for (int i = maxNum - 1; i>count; i--)
		{
			HighscoreSaver::name[i] = HighscoreSaver::name[i - 1];
			HighscoreSaver::score[i] = HighscoreSaver::score[i - 1];

		}
		HighscoreSaver::name[count] = name;
		HighscoreSaver::score[count] = score;
	}
	if (numOfEntries != maxNum)
		numOfEntries++;

	newEntry = count;
	lowest = HighscoreSaver::score[maxNum - 1];
	SaveList();
}
void HighscoreSaver::SaveList()
{
	fstream outputFile;
	outputFile.open("score", ios::out | ios::trunc);

	for (int i = 0; i < numOfEntries; i++)
	{
		outputFile << HighscoreSaver::name[i]<< " " << HighscoreSaver::score[i]<< '\n';
	}

	outputFile.close();
}

void HighscoreSaver::Render(int X, int Y, ALLEGRO_FONT *font)
{

	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
	al_draw_text(font, color, X, Y, 0, "HIGHSCORES:");
	string temp;
	for (int i = 0; i < numOfEntries; i++)
	{
		temp = HighscoreSaver::name[i];
		if (i == newEntry)
			color = al_map_rgb(0, 255, 0);
		else
			color = al_map_rgb(255, 255, 255);

		al_draw_text(font, color, X, Y + 35*i + 40, 0, temp.c_str());
		al_draw_textf(font, color, X + 100, Y + 35 * i + 40, 0,"             %i", HighscoreSaver::score[i]);

	}
}

void HighscoreSaver::Reset()
{
	newEntry = maxNum;
}