/*  
    @author: Barış İncesu
    @ID: 150170092
    @date :11.01.2021
    ///////////////////////////
    Compile:
    g++ -std=c++11 150170092.cpp -o 150170092
    Run:
    ./150170092 euroleague.csv
*/

#include <iostream> // basic library for cout

#include <fstream> // file operation
//#include <stdio.h>
//#include <limits.h>
#include <string> // string operation
#include <set>
#include <vector>
#include <algorithm>

//#include <sstream> // string stream operaiton

using namespace std;

// Number of vertices
// in the graph
#define V 200

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
        //cout << a << "\n";
        return;
    }

    printPath(parent, parent[j], a, s1);

    //printf("%d ", j);
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
    //printf("Vertex\t Distance\tPath");

    for (int i = 1; i < 2; i++)
    {

        //printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
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

//function to return position in map
int positionSet(set<string> s1, string Ch)
{
    set<string>::iterator itr;
    int position = 0;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        //cout << *itr << endl;
        if (*itr == Ch)
        {
            position = distance(s1.begin(), itr);
        }
        //m1.insert(pair<int, string>(0, *itr));
    }
    return position;
}

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
// Driver Code
int main()
{
    string filename;
    cin >> filename;
    // Let us create the example
    // graph discussed above

    ifstream file1;
    file1.open(filename);
    set<string> s1;

    if (!file1)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string line;
    string source, destination, cop;
    //int weight = 0;

    vector<string> badPoints;
    //Okumaya başla!
    while (!file1.eof())
    {
        // "," e kadar oku. String olarak al.
        getline(file1, source, ',');
        getline(file1, destination, ',');
        getline(file1, cop, '\n');

        int index1 = source.find("E");
        int index2 = destination.find("E");

        // E lileri alma. -> kümeye kaydet.
        cout << "Okunan satir: " << source << ',' << destination << ',' << cop << endl;
        cout << index1 << " " << index2 << endl;
        if ((index1 != -1 || index2 != -1) && stoi(cop) < 5)
        {
            cout << "----------------------------------Sikinti Durum" << endl;
            if (index1 == -1)
            {
                cout << "------------------ Bad Point Eklendi:" << source << endl;
                badPoints.push_back(source);
            }
            if (index2 == -1)
            {
                cout << "------------------ Bad Point Eklendi:" << destination << endl;
                badPoints.push_back(destination);
            }
        }
        else
        {
            if (!isBadPoint(badPoints, source) && index1 == -1)
            {
                s1.insert(source);
                cout << "Eklenen Nokta: " << source << endl;
            }
            if (!isBadPoint(badPoints, destination) && index2 == -1)
            {
                s1.insert(destination);
                cout << "Eklenen Nokta: " << destination << endl;
            }
        }
    }
    cout << "BURDAYIM1" << endl;

    set<string>::iterator itr;

    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        cout << *itr << endl;
        if (isBadPoint(badPoints, *itr))
        {
            s1.erase(*itr);
            s1.insert("deneme");
            cout << "BURDAYIM4" << endl;
        }
    }
    //set<string>::iterator itr;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        cout << distance(s1.begin(), itr) << "-" << *itr << endl;
    }

    cout << "BURDAYIM3" << endl;
    //const int counterSpot = s1.size();
    //cout << counterSpot << endl;

    int graph[V][V];

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = 0;
        }
    }

    //set<string>::iterator itr;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        cout << distance(s1.begin(), itr) << "-" << *itr << endl;
    }

    ifstream file2;
    file2.open(filename);

    if (!file2)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    while (!file2.eof())
    {
        int m = 0;
        int n = 0;
        // 2li 2li oku.
        getline(file2, source, ',');
        getline(file2, destination, ',');
        getline(file2, cop, '\n');
        // E li eşleşme var mı?
        int index1 = source.find("E");
        int index2 = destination.find("E");
        //int index3 = source.find("S");
        //int index4 = destination.find("S");

        cout << "Matrislenen satir: " << source << ',' << destination << ',' << cop << endl;
        if ((index1 == -1) && (index2 == -1) && !isBadPoint(badPoints, source) && !isBadPoint(badPoints, destination))
        {
            cout << "Matrislenebilir" << endl;
            //cout << source << "-" << destination << endl;
            for (itr = s1.begin(); itr != s1.end(); itr++)
            {

                if (*itr == source)
                {
                    m = distance(s1.begin(), itr);
                }
                if (*itr == destination)
                {
                    n = std::distance(s1.begin(), itr);
                }
            }
            graph[m][n] = stoi(cop);
            graph[n][m] = stoi(cop);
            //cout << "Eklenen Nokta: " << source << endl;
        }
        /*if (((source.find("S") != -1) && (destination.find("S") != -1)))
        {
            for (itr = s1.begin(); itr != s1.end(); itr++)
            {
                //cout << *itr << endl;
                if (*itr == source)
                {
                    m = distance(s1.begin(), itr);
                }
                if (*itr == destination)
                {
                    n = std::distance(s1.begin(), itr);
                }
            }
            graph[m][n] = stoi(cop);
        }*/

        // Sx to Sx var mı?
    }
    int begin;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        //cout << *itr << endl;
        if (*itr == "Ma")
        {
            begin = distance(s1.begin(), itr);
        }
    }

    // Yoksa mapdeki adreslerini al ve matrix'e kaydet.

    // Matrix Ex | Sx->Sx

    /*int graph[V][V] = {{0, 0, 0, 0, 0, 4, 8, 9, 0, 0},
                       {0, 0, 4, 6, 0, 2, 7, 0, 0, 0},
                       {0, 4, 0, 0, 0, 7, 0, 0, 0, 9},
                       {0, 6, 0, 0, 0, 0, 1, 0, 4, 0},
                       {0, 0, 0, 0, 0, 0, 0, 0, 7, 16},
                       {4, 2, 7, 0, 0, 0, 0, 0, 0, 0},
                       {8, 7, 0, 1, 0, 0, 0, 0, 0, 0},
                       {9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 4, 7, 0, 0, 0, 0, 0},
                       {0, 0, 9, 0, 16, 0, 0, 0, 0, 0}};*/

    // Ma 0
    // R1 1
    // R2 2
    // R3 3
    // R4 4
    // S1 5
    // S2 6
    // S3 7
    // S4 8
    // Mo 9
    //graph[3][5] = 1;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << graph[i][j] << "\t";
        }
        cout << endl;
    }

    dijkstra(graph, begin, s1);
    return 0;
}
