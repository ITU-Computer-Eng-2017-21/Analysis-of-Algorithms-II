/***********************************************************
2021 Spring - BLG 336E-Analysis of Algorithms II
Final Project
Question on Greedy Algorithms
Modified Dijkstra Algorithms for Maximum Capacity Path
Submitted: 15.06.2021 
**********************************************************/

/***********************************************************
STUDENT INFORMATION
Full Name :
Student ID:  
**********************************************************/

// Some of the libraries you may need have already been included.
// If you need additional libraries, feel free to add them
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

// Do not change this definition
//#define INT_MAX 1000

using namespace std;

class Graph
{
public:
	int node_count;
	int edge_count;
	int **adjacency_matrix;

	Graph(){};
	void read_file(char *filename);
	void print_adjacency_matrix(); // in case you need
	int weight(int i, int j) { return this->adjacency_matrix[i][j]; }
	~Graph();
};

Graph::~Graph()
{
	for (int i = 0; i < node_count; i++)
	{
		delete[] adjacency_matrix[i];
	}
}

void Graph::print_adjacency_matrix()
{
	// Prints the adjacency matrix
	for (int i = 0; i < this->node_count; i++)
	{
		for (int j = 0; j < this->node_count; j++)
		{
			cout << this->adjacency_matrix[i][j] << ", ";
		}
		cout << endl;
	}
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int maxFrigles(int status[], int wt[], int SIZE)
{
	int max = 0;
	int maxfringles = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (wt[i] > max && status[i] == 1)
		{
			max = wt[i];
			maxfringles = i;
		}
	}
	return maxfringles;
}

bool checkIsFullyDone(int status[], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (status[i] == 1)
		{
			return true;
		}
	}
	return false;
}
void Graph::read_file(char *filename)
{
	ifstream input(filename);

	string line;
	if (getline(input, line))
	{
		this->node_count = stoi(line);
	}

	int **arr;

	arr = new int *[this->node_count];

	for (int i = 0; i < this->node_count; i++)
		arr[i] = new int[this->node_count];

	for (int i = 0; i < this->node_count; i++)
	{
		for (int j = 0; j < this->node_count; j++)
		{
			arr[i][j] = 0;
		}
	}
	int i, j, w;
	while (!input.eof())
	{
		// displaying content
		input >> i;
		input >> j;
		input >> w;
		arr[i][j] = w;
		arr[j][i] = w;
	}

	/*
	arr[0][1] = 4;
	arr[0][2] = 2;
	arr[0][4] = 3;
	arr[1][3] = 1;
	arr[2][3] = 5;
	arr[2][5] = 4;
	arr[3][6] = 4;
	arr[3][7] = 1;
	arr[4][5] = 6;
	arr[5][7] = 3;
	arr[6][7] = 1;
	*/
	this->adjacency_matrix = arr;
	//graph->print_adjacency_matrix();
}

void Modified_Dijkstra(Graph *graph)
{
	int s = 0;
	int t = 7;

	int status[graph->node_count];
	int wt[graph->node_count];
	int dad[graph->node_count];

	for (int v = 0; v < graph->node_count; v++)
	{
		status[v] = 0;
		wt[v] = -1;
		dad[v] = -1;
	}
	bool devam = true;
	status[s] = 2;
	wt[s] = 1000;

	for (int w = 0; w < graph->node_count; w++)
	{
		if (graph->weight(s, w) != 0)
		{
			status[w] = 1;
			wt[w] = graph->weight(s, w);
			dad[w] = s;
		}
	}
	int temp1 = 0;
	//int temp2 = 0;
	while (devam)
	{
		int v = maxFrigles(status, wt, graph->node_count);
		status[v] = 2;
		temp1 = v;

		for (int w = 0; w < graph->node_count; w++)
		{
			if (graph->weight(v, w) != 0)
			{
				if (status[w] == 0)
				{
					status[w] = 1;
					wt[w] = min(wt[v], graph->weight(v, w));
					dad[w] = v;
				}
				else if (status[w] == 1 && (wt[w] < min(wt[v], graph->weight(v, w))))
				{
					wt[w] = min(wt[v], graph->weight(v, w));
					dad[w] = v;
				}
			}
		}
		devam = checkIsFullyDone(status, graph->node_count);
	}

	/*********************************************/
	/***** DO NOT CHANGE THE FOLLOWING LINES *****/
	/**** THEY PRINT OUT THE EXPECTED RESULTS ****/
	/*********************************************/

	// The following line prints wt array (or vector).
	// Do not change anything in the following lines.

	cout
		<< "###########RESULTS###########" << endl;
	cout << endl;

	cout << "1. WT ARRAY" << endl;
	cout << "------------------------" << endl;
	cout << "  ";
	for (int i = 0; i < graph->node_count - 1; i++)
	{
		cout << wt[i] << ", ";
	}
	cout << wt[graph->node_count - 1] << endl;

	// The following lines print the final path.
	// Do not change anything in the following lines.
	int iterator = graph->node_count - 1;
	vector<int> path_info;
	path_info.push_back(iterator);
	while (iterator != 0)
	{
		path_info.push_back(dad[iterator]);
		iterator = dad[iterator];
	}
	cout << endl;
	cout << "2. MAXIMUM CAPACITY PATH" << endl;
	cout << "------------------------" << endl;
	cout << "  ";
	vector<int>::iterator it;
	for (it = path_info.end() - 1; it > path_info.begin(); it--)
		cout << *it << " -> ";
	cout << *path_info.begin() << endl;

	cout << endl;
	cout << "3. MAXIMUM CAPACITY" << endl;
	cout << "------------------------" << endl;
	cout << "  ";
	cout << wt[graph->node_count - 1] << endl;
	cout << "#############################" << endl;

	return;
}

int main(int argc, char **argv)
{
	Graph *graph = new Graph();

	graph->read_file("D:/Code/VS Code-Projects/Analysis-of-Algorithms-II/Final Project/Q1/test2.txt");
	Modified_Dijkstra(graph);

	return 0;
}
