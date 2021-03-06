// practice-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

typedef int Map[20][20];

struct Chessboard
{
	Map map;
	int y = 0;
	int x = 0;
};

static const string INPUT_FILE_NAME = "input.txt";
static const string OUTPUT_FILE_NAME = "output.txt";
static const unsigned int MAP_WIDTH = 20;
static const unsigned int MAP_HEIGHT = 20;
static const int BLANK = -1, WALL = -2, DOT = -3;

void InitLabirinth(Map &map)
{
	for (unsigned int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; ++j)
		{
			map[i][j] = BLANK;
		}
	}
}

void ReadLabirinth(std::ifstream &inputFile, Chessboard &chessboard)
{
	inputFile >> chessboard.y >> chessboard.x;

	std::string row;
	std::getline(inputFile, row);
	for (unsigned int i = 0; std::getline(inputFile, row) && i < MAP_HEIGHT; ++i)
	{
		for (unsigned int j = 0; j < row.length() && j < MAP_WIDTH; ++j)
		{
			switch (row[j])
			{
			case '.':
				chessboard.map[i][j] = DOT;
				break;
			case '#':
				chessboard.map[i][j] = WALL;
				break;
			default:
				break;
			}
		}
	}
}

bool CoordinateInRange(Chessboard &chessboard, int x, int y)
{
	return (y > 0 && y < chessboard.y)
		&& (x > 0 && x < chessboard.x);
}

void Mecta(Chessboard &chessboard, int i, int j)
{
	if (chessboard.map[i][j] == WALL)
	{
		chessboard.map[i][j] = DOT;
		Mecta(chessboard, i - 1, j - 1);
		Mecta(chessboard, i - 1, j + 1);
		Mecta(chessboard, i + 1, j - 1);
		Mecta(chessboard, i + 1, j + 1);

		Mecta(chessboard, i + 1, j);
		Mecta(chessboard, i - 1, j);
		Mecta(chessboard, i, j + 1);
		Mecta(chessboard, i, j - 1);
	}
}

int main()
{
	ifstream inputFile(INPUT_FILE_NAME);
	if (!inputFile.good() && inputFile.peek() != std::ifstream::traits_type::eof())
	{
		cout << "failed read\n";
		return 1;
	}
	ofstream outputFile(OUTPUT_FILE_NAME);

	Chessboard chessboard;
	InitLabirinth(chessboard.map);
	ReadLabirinth(inputFile, chessboard);
	int count = 0;
	for (int i = 0; i < chessboard.y; ++i)
	{
		for (int j = 0; j < chessboard.x; ++j)
		{
			if (chessboard.map[i][j] == WALL)
			{
				Mecta(chessboard, i, j);
				count++;
			}
		}
	}
	outputFile << count << "\n";
	inputFile.close();
	outputFile.close();

	return 0;
}