/*
* q3_maxProfit_skeleton.cpp
*
* Created on: June 14th, 2021
*     Author: Barış İncesu
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b)
{
	return (a > b) ? a : b;
}

pair<int, set<int>> MaxProfit(int numOfCrystals, vector<int> profits, vector<int> entryCosts)
{
	int W = numOfCrystals;

	int numOfCities = profits.size();
	int n = numOfCities;

	int K[n + 1][W + 1];
	int i, w;
	set<int> citiesToVisit;
	// Build table K[][] in bottom up manner
	for (i = 0; i <= n; i++)
	{
		for (w = 0; w <= W; w++)
		{
			if (i == 0 || w == 0)
				K[i][w] = 0;

			else if (entryCosts[i - 1] <= w)
			{
				K[i][w] = max(profits[i - 1] +
								  K[i - 1][w - entryCosts[i - 1]],
							  K[i - 1][w]);
				//citiesToVisit.insert(i);
			}
			else
			{
				K[i][w] = K[i - 1][w];
			}
		}
	}

	i = profits.size();
	w = W;
	while (i > 0 && w > 0)
	{
		if (K[i][w] != K[i - 1][w])
		{
			citiesToVisit.insert(i);
			w = w - entryCosts[i - 1];
		}
		i = i - 1;
	}

	int maxProfit = K[n][W];

	/****************************************************************/
	/********* YOU NEED TO USE HERE AS BASE OF YOUR METHOD! *********/
	/* YOU CAN USE HELPER METHODS BUT main() WILL CALL THIS METHOD! */
	/****************************************************************/

	cout << "Dynaming Programming Table" << endl;
	for (int i = 0; i <= numOfCities; i++)
	{
		for (int j = 0; j <= numOfCrystals; j++)
		{
			cout << std::right << std::setw(3) << K[i][j];
		}
		cout << endl;
	}

	return pair<int, set<int>>(maxProfit, citiesToVisit);
}

int main()
{
	int numOfCrystals;
	vector<int> profits;
	vector<int> entryCosts;

	string inputFilename;
	cout << "Enter the name of the input file: ";
	//cin >> inputFilename;
	inputFilename = "D:/Code/VS Code-Projects/Analysis-of-Algorithms-II/Final Project/Q3/q3_maxProfit_test2.txt";

	ifstream input(inputFilename);

	if (!input.is_open())
	{
		cerr << "File named \"" << inputFilename << "\" could not open!" << endl;
		return EXIT_FAILURE;
	}

	string line;
	if (getline(input, line))
	{
		numOfCrystals = stoi(line);
	}
	while (getline(input, line, ' '))
	{
		profits.push_back(stoi(line));
		getline(input, line);
		entryCosts.push_back(stoi(line));
	}

	pair<int, set<int>> result = MaxProfit(numOfCrystals, profits, entryCosts);

	cout << "Max profit is " << result.first << "." << endl;
	cout << "Cities visited:";
	for (int cityNumber : result.second)
	{
		cout << " " << cityNumber;
	}
	cout << endl;
}
