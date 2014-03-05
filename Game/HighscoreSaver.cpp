#include "HighscoreSaver.h"
#include <fstream>

HighscoreSaver::HighscoreSaver()
{
	fstream inputFile;
	inputFile.open("scores", ios::in);
	
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
	if (count < maxNum)
	{
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

	for (int i = 0; i < numOfEntries; i++)
		al_draw_textf(font, al_map_rgb(255, 255, 255), X, Y + 35*i, 0, HighscoreSaver::name[i].c_str() + ' %i', HighscoreSaver::score[i]);
}