// STL implementation of Prim's algorithm for MST
#include <bits/stdc++.h>
#include <string>   // string operation
#include <fstream>  // file operation
#include <sstream>  // string stream operaiton
#include <iostream> // basic library for cout
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
using namespace std;
#define INF 0x3f3f3f3f

// iPair ==> Integer Pair
typedef pair<int, int> iPair;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V; // No. of vertices

    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list<pair<int, int>> *adj;

public:
    Graph(int V); // Constructor

    // function to add an edge to graph
    void addEdge(string us, string vs, int wt, set<string> s1);

    // Print MST using Prim's algorithm
    map<string, int> primMST(map<int, string> m1, int point_GP, int point_Hipp, int point_Chx, int weight_GPtoHipp, int weight_GPtoChx);
};

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
};

bool cmp(pair<string, int> &a, pair<string, int> &b)
{
    return a.second < b.second;
}

// Function to sort the map according
// to value in a (key-value) pairs
void sort(map<string, int> &M)
{
    int totalCost = 0;
    // Declare vector of pairs
    vector<pair<string, int>> A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto &it : M)
    {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    // Print the sorted value
    for (auto &it : A)
    {

        cout << it.first << ' ' << it.second << '\n';
        totalCost = totalCost + it.second;
    }
    cout << totalCost << '\n';
}

// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair>[V];
}

void Graph::addEdge(string us, string vs, int wt, set<string> s1)
{
    int u, v;
    set<string>::iterator itr;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        //cout << *itr << endl;
        if (*itr == us)
        {
            u = std::distance(s1.begin(), itr);
        }
        if (*itr == vs)
        {
            v = std::distance(s1.begin(), itr);
        }
        //m1.insert(pair<int, string>(0, *itr));
    }

    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

// Prints shortest paths from src to all other vertices
map<string, int> Graph::primMST(map<int, string> m1, int point_GP, int point_Hipp, int point_Chx, int weight_GPtoHipp, int weight_GPtoChx)
{
    // Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    int src = point_GP; // Taking vertex 0 as source
    map<string, int> mx;

    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(V, INF);

    // To store parent array which in turn store MST
    vector<int> parent(V, -1);

    // To keep track of vertices included in MST
    vector<bool> inMST(V, false);

    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push(make_pair(-3, src));
    key[src] = 0;
    parent[src] = src;
    pq.push(make_pair(-4, point_Hipp));
    key[point_Hipp] = weight_GPtoHipp;
    parent[point_Hipp] = src;
    pq.push(make_pair(-1, point_Chx));
    key[point_Chx] = weight_GPtoChx;
    parent[point_Chx] = src;

    /* Looping till priority queue becomes empty */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum key
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted key (key must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true; // Include vertex in MST

        // 'i' is used to get all adjacent vertices of a vertex
        list<pair<int, int>>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;

            // If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if (inMST[v] == false && key[v] > weight)
            {
                // Updating key of v
                if (v != point_Hipp && v != point_Chx)
                {
                    key[v] = weight;
                }

                pq.push(make_pair(key[v], v));

                if (v != point_Hipp && v != point_Chx)
                {
                    parent[v] = u;
                }
            }
        }
    }

    // Print edges of MST using parent array

    for (int i = 0; i < V; ++i)
    {
        if (i != src)
        {
            //cout << m1[parent[i]] << "," << m1[i] << "," << key[i] << "\n";
            //printf("%d - %d\n", parent[i], i);

            mx.insert(pair<string, int>(m1[parent[i]] + " " + m1[i], key[i]));
        }
    }
    return mx;
}

// Driver program to test methods of graph class
int main()
{
    // create the graph given in above fugure
    string filename = "city_plan_2.txt";
    // making above shown graph
    /*
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    */

    ifstream file1;
    file1.open(filename);
    set<string> s1;

    if (!file1)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    //string line;
    string source, destination, cop;
    //int weight = 0;

    //Okumaya başla!
    while (!file1.eof())
    {
        // "," e kadar oku. String olarak al.
        getline(file1, source, ',');
        getline(file1, destination, ',');
        getline(file1, cop, '\n');

        s1.insert(source);
        s1.insert(destination);
    }

    int V = s1.size();
    Graph g(V);

    map<int, string> m1;
    /*
    s1.insert("GP");
    s1.insert("Hipp");
    s1.insert("Bas1");
    s1.insert("Bas2");
    s1.insert("Bas3");
    s1.insert("Ch1");
    s1.insert("Ch2");
    s1.insert("Hp1");
    s1.insert("Hp2");
    s1.insert("Hp3");
    s1.insert("Hp4");
    */
    set<string>::iterator itr;
    int i = 0;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        //cout << *itr << endl;
        //cout << distance(s1.begin(), itr) << "-" << *itr << endl;
        m1.insert(pair<int, string>(i, *itr));
        i++;
    }

    ifstream file2;
    file2.open(filename);

    if (!file2)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }
    //int weight = 0;

    //Okumaya başla!
    int weight_GPtoChx = 0;

    int point_GP = positionSet(s1, "GP"), point_Hipp = positionSet(s1, "Hipp"), point_Chx, weight_GPtoHipp;

    while (!file2.eof())
    {
        // "," e kadar oku. String olarak al.
        getline(file2, source, ',');
        getline(file2, destination, ',');
        getline(file2, cop, '\n');

        int c1 = source.find("Ch");
        int c2 = destination.find("GP");

        int c3 = source.find("GP");
        int c4 = destination.find("Ch");
        //cout << "inhere1" << endl;
        if ((c1 != -1 && c2 != -1) || (c3 != -1 && c4 != -1))
        {
            //cout << "inhere2" << endl;
            if (weight_GPtoChx == 0 || stoi(cop) < weight_GPtoChx)
            {
                //cout << "inhere3" << endl;
                weight_GPtoChx = stoi(cop);
                if (c1 != -1 && c2 != -1)
                {
                    point_Chx = positionSet(s1, source);
                    //cout << "Clotest:" << weight_GPtoChx << " Point:" << source << endl;
                }
                else if (c3 != -1 && c4 != -1)
                {
                    point_Chx = positionSet(s1, destination);
                    //cout << "Clotest:" << weight_GPtoChx << " Point:" << destination << endl;
                }
            }
            /*else if (stoi(cop) < clotest)
            {
                clotest = stoi(cop);
                if (c1 != -1 && c2 != -1)
                {
                    point_Chx = positionSet(s1, source);
                    cout << "CLotest:" << clotest << " Point:" << source << endl;
                }
                else if (c3 != -1 && c4 != -1)
                {
                    point_Chx = positionSet(s1, destination);
                    cout << "CLotest:" << clotest << " Point:" << destination << endl;
                }
            }*/
        }

        int gphipp1 = source.find("GP");
        int gphipp2 = destination.find("Hipp");

        int gphipp3 = source.find("Hipp");
        int gphipp4 = destination.find("GP");

        if ((gphipp1 != -1 && gphipp2 != -1) || (gphipp3 != -1 && gphipp4 != -1))
        {
            weight_GPtoHipp = stoi(cop);
            //cout << "Hippodrom Weight:" << weight_GPtoHipp << " Hippodrom:" << positionSet(s1, "Hipp") << endl;
        }

        int index1 = source.find("Hp");
        int index2 = destination.find("Hp");

        int index3 = source.find("Hipp");
        int index4 = destination.find("Bas");

        int index5 = source.find("Bas");
        int index6 = destination.find("Hipp");

        //cout << index1 << " | " << index2 << " | " << index3 << " | " << index4 << " | " << index5 << " | " << index6 << endl;

        //cout << "g.addEdge(" << source << "," << destination << "," << stoi(cop) << endl;

        if (!((index1 != -1 && index2 != -1) || (index3 != -1 && index4 != -1) || (index5 != -1 && index6 != -1)))
        {

            /*cout << "g.addEdge(" << source << "," << destination << "," << stoi(cop) << endl;
            g.addEdge(source, destination, stoi(cop), s1);*/
            g.addEdge(source, destination, stoi(cop), s1);
            //cout << "ENRTY!" << endl;
        }
        //cout << "---------------" << endl;
    }
    /*
    g.addEdge("GP", "Hipp", 1200, s1);
    g.addEdge("GP", "Ch2", 2000, s1);
    g.addEdge("GP", "Bas3", 9, s1);
    g.addEdge("GP", "Hp4", 8, s1);
    g.addEdge("GP", "Bas2", 6, s1);
    g.addEdge("Hipp", "Ch1", 1, s1);
    g.addEdge("Hipp", "Hp1", 7000, s1);
    //g.addEdge("Hipp", "Bas1", 14, s1);
    g.addEdge("Hipp", "Ch2", 13, s1);
    g.addEdge("Hipp", "Hp2", 10, s1);
    g.addEdge("Bas1", "Ch2", 15, s1);
    g.addEdge("Ch2", "Bas3", 4, s1);
    g.addEdge("Bas3", "Hp4", 16, s1);
    g.addEdge("Bas3", "Hp3", 11, s1);
    //g.addEdge(adj, "Hp3", "Hp4", 17, s1);
    g.addEdge("Hp3", "Bas2", 3, s1);
    g.addEdge("Bas2", "Hp2", 18, s1);
    //addEdge(adj, "Hp4", "Hp2", 5, s1);
    */

    map<string, int> istenilen = g.primMST(m1, point_GP, point_Hipp, point_Chx, weight_GPtoHipp, weight_GPtoChx);

    ifstream file3;
    file3.open(filename);

    if (!file3)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    //int weight = 0;
    map<string, int> istenilenson;
    //Okumaya başla!
    while (!file3.eof())
    {
        // "," e kadar oku. String olarak al.
        getline(file3, source, ',');
        getline(file3, destination, ',');
        getline(file3, cop, '\n');

        //cout << "GIRDI1" << endl;
        //cout << source << "," << destination << "," << stoi(cop) << endl;
        //cout << "DOSYA *** VS *** BIZIM " << endl;
        map<string, int>::iterator it;
        for (it = istenilen.begin(); it != istenilen.end(); ++it)
        {
            //cout << "GIRDI2" << endl;
            //cout << it->first.substr(0, it->first.find(',')) << "--" << it->first.substr(it->first.find(',') + 1, it->first.length()) << endl;
            //cout << it->first.substr(0, it->first.find(',')) << "," << it->first.substr(it->first.find(','), it->first.length()) << "," << it->second << endl;

            if (source == it->first.substr(0, it->first.find(' ')) && destination == it->first.substr(it->first.find(' ') + 1, it->first.length()) && stoi(cop) == it->second)
            {
                //cout << "MATCH" << endl;
                istenilenson.insert(pair<string, int>(source + " " + destination, it->second));
            }
            else if (destination == it->first.substr(0, it->first.find(' ')) && source == it->first.substr(it->first.find(' ') + 1, it->first.length()) && stoi(cop) == it->second)
            {
                //cout << "TERSMATCH" << endl;
                istenilenson.insert(pair<string, int>(source + " " + destination, it->second));
            }
        }
        //cout << endl;

        s1.insert(source);
        s1.insert(destination);
    }

    //sort(istenilen);
    //cout << "--------------------";
    sort(istenilenson);
    /*map<string, int>::iterator it;
    for (it = istenilen.begin(); it != istenilen.end(); ++it)
    {
        cout << '\t' << it->first << '\t' << it->second << '\n';
    }
    cout << endl;*/
    //multimap<int, int> verilen;

    //verilen.insert(pair<int, int>(3, 5));

    return 0;
}
