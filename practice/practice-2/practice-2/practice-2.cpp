// practice-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
static const int MAX = 101;

int main()
{
	ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		cout << "failed reading\n";
		return 1;
	}
	ofstream outputFile("output.txt");
	if (!inputFile.is_open())
	{
		cout << "failed writing.\n";
		return 1;
	}
	
	int m = 0;
	int n = 0;
	inputFile >> m >> n;
	vector<vector<int>> map;
	for ( int i = 0; i < m; ++i)
	{
		map.push_back(vector<int>());
		for ( int j = 0; j < n; ++j)
		{
			int temp = 0;
			if (inputFile >> temp)
			{
				map[i].push_back(temp);
			}
		}
	}
	map.push_back(vector<int>());
	for (int j = 0; j < n; ++j)
	{
		map[m - 1].push_back(0);
	}
	for (int j = n - 1; j >= 0; --j)
	{
		for (int i = m - 1; i >= 0; --i)
		{
			if (i == m - 1)
			{
				map[i][j] += map[i][j + 1];
			}
			else if (j == n - 1)
			{
				map[i][j] += map[i + 1][j];
			}
			else if (map[i][j + 1] < map[i + 1][j])
			{
				map[i][j] += map[i][j + 1];
			}
			else
			{
				map[i][j] += map[i + 1][j];
			}
		}
	}

	outputFile << map[0][0] << "\n";

	int i = 0;
	int j = 0;
	while (i < m && j < n)
	{
		outputFile << i << " " << j << "\n";
		if (i == m - 1 || map[i][j + 1] < map[i + 1][j])
		{
			j++;
		}
		else 
		{
			i++;
		}
	}
    return 0;
}
