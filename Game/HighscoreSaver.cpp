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
}
HighscoreSaver::~HighscoreSaver(){}

void HighscoreSaver::CreateNewFile()
{

}
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

	al_draw_text(font, al_map_rgb(255, 255, 255), X, Y, 0, "HIGHSCORES:");
	string temp;
	for (int i = 0; i < numOfEntries; i++)
	{
		temp = HighscoreSaver::name[i];
		al_draw_text(font, al_map_rgb(255, 255, 255), X, Y + 35*i + 40, 0, temp.c_str());
		al_draw_textf(font, al_map_rgb(255, 255, 255), X + 100, Y + 35 * i + 40, 0,"             %i", HighscoreSaver::score[i]);

	}
}