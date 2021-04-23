/*  
    @author: Barış İncesu
    @ID: 150170092
    @date :23.04.2021
    ///////////////////////////
    Compile: g++ -std=c++11 -Wall -Werror q2.cpp -o q2
    Run: ./q2
    Calico: python -m calico.cli q2_tc_updated.t
*/

#include <iostream> // basic library for cout
#include <fstream>  // file operation
#include <limits.h>
#include <string> // string operation
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// Number of vertices
// in the graph
#define V 1000

//function to return position in map
int positionSet(set<string> s1, string Ch)
{
    set<string>::iterator itr;
    int position = 0;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        if (*itr == Ch)
        {
            position = distance(s1.begin(), itr);
        }
    }
    return position;
}

// A utility function to find the
// vertex with minimum distance
// value, from the set of vertices
// not yet included in shortest
// path tree
int minDistance(int dist[], bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false &&
            dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print shortest
// path from source to j
// using parent array
void printPath(int parent[], int j, int a, set<string> s1)
{

    std::set<string>::iterator it = s1.begin();
    // Base Case : If j is source
    if (parent[j] == -1)
    {
        return;
    }

    printPath(parent, parent[j], a, s1);

    std::advance(it, j);
    cout << *it << ' ';
}

// A utility function to print
// the constructed distance
// array
void printSolution(int dist[], int n, int parent[], set<string> s1)
{
    int src = 0;
    std::set<string>::iterator it = s1.begin();
    std::advance(it, src);
    cout << *it << ' ';

    for (int i = 1; i < 2; i++) // Ma = 0, Mo = 1 So write only 1 times and start at 1
    {
        printPath(parent, i, dist[i], s1);
        cout << dist[i] << '\n';
    }
}

// Funtion that implements Dijkstra's
// single source shortest path
// algorithm for a graph represented
// using adjacency matrix representation
void dijkstra(int graph[V][V], int src, set<string> s1)
{

    // The output array. dist[i]
    // will hold the shortest
    // distance from src to i
    int dist[V];

    // sptSet[i] will true if vertex
    // i is included / in shortest
    // path tree or shortest distance
    // from src to i is finalized
    bool sptSet[V];

    // Parent array to store
    // shortest path tree
    int parent[V];

    // Initialize all distances as
    // INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex
    // from itself is always 0
    dist[src] = 0;

    // Find shortest path
    // for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance
        // vertex from the set of
        // vertices not yet processed.
        // u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex
        // as processed
        sptSet[u] = true;

        // Update dist value of the
        // adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    // print the constructed
    // distance array
    printSolution(dist, V, parent, s1);
}

// return if point is a near enemy less than 5.
bool isBadPoint(vector<string> v, string location)
{
    vector<string>::iterator itr;
    for (itr = v.begin(); itr != v.end(); itr++)
    {
        if (*itr == location)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    string filename;
    cin >> filename;

    ifstream file1;
    file1.open(filename);
    set<string> s1;

    if (!file1)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string line;
    string source, destination, weight;

    vector<string> badPoints;
    vector<string> goodPoints;
    // First read for detect point good/bad
    while (!file1.eof())
    {
        getline(file1, source, ',');
        getline(file1, destination, ',');
        getline(file1, weight, '\n');

        int index1 = source.find("E");
        int index2 = destination.find("E");

        if ((index1 != -1 || index2 != -1) && stoi(weight) < 5)
        {
            if (index1 == -1)
            {
                badPoints.push_back(source);
            }
            if (index2 == -1)
            {
                badPoints.push_back(destination);
            }
        }
        else
        {
            if (!isBadPoint(badPoints, source) && index1 == -1)
            {
                goodPoints.push_back(source);
            }
            if (!isBadPoint(badPoints, destination) && index2 == -1)
            {
                goodPoints.push_back(destination);
            }
        }
    }

    set<string>::iterator itr;
    vector<string>::iterator badIterator;
    vector<string>::iterator goodIterator;
    // Determination of the final points
    for (goodIterator = goodPoints.begin(); goodIterator != goodPoints.end(); goodIterator++)
    {
        bool sabit = true;
        for (badIterator = badPoints.begin(); badIterator != badPoints.end(); badIterator++)
        {
            if (*badIterator == *goodIterator)
            {
                sabit = false;
            }
        }
        if (sabit)
        {
            s1.insert(*goodIterator);
        }
    }

    // Creating Adjaceny Matrix for Dijsktra Algorithm with full 0
    int graph[V][V];

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = 0;
        }
    }

    ifstream file2;
    file2.open(filename);

    if (!file2)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }
    // Secomd Read: Place edges to adjaceny matrix
    while (!file2.eof())
    {
        int m = 0;
        int n = 0;

        getline(file2, source, ',');
        getline(file2, destination, ',');
        getline(file2, weight, '\n');

        int index1 = source.find("E");
        int index2 = destination.find("E");

        // if edge has not link with Enemy Points and Source and Destination are Good Points add edge to matrix
        if ((index1 == -1) && (index2 == -1) && !isBadPoint(badPoints, source) && !isBadPoint(badPoints, destination))
        {

            m = positionSet(s1, source);
            n = positionSet(s1, destination);
            graph[m][n] = stoi(weight);
            graph[n][m] = stoi(weight);
        }
    }
    int begin = positionSet(s1, "Ma");

    dijkstra(graph, begin, s1);
    return 0;
}
