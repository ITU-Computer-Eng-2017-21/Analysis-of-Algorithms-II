// STL implementation of Prim's algorithm for MST
#include <bits/stdc++.h>
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
    map<int, int> primMST(map<int, string> m1);
};

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
map<int, int> Graph::primMST(map<int, string> m1)
{
    // Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    int src = 5; // Taking vertex 0 as source
    map<int, int> mx;

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
    pq.push(make_pair(-4, 4));
    key[4] = 2000;
    parent[4] = src;
    pq.push(make_pair(-1, 6));
    key[6] = 1200;
    parent[6] = src;

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
                if (v != 4 && v != 6)
                {
                    key[v] = weight;
                }

                pq.push(make_pair(key[v], v));

                if (v != 4 && v != 6)
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

            mx.insert(pair<int, int>(i, parent[i]));
        }
    }
    return mx;
}

// Driver program to test methods of graph class
int main()
{
    // create the graph given in above fugure
    int V = 11;
    Graph g(V);

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

    map<int, string> m1;

    set<string> s1;

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

    set<string>::iterator itr;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        //cout << distance(s1.begin(), itr) << "-" << *itr << endl;
    }

    //set<string>::iterator itr;
    int i = 0;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        //cout << *itr << endl;
        m1.insert(pair<int, string>(i, *itr));
        i++;
    }

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

    map<int, int> istenilen = g.primMST(m1);

    map<int, int>::iterator it;
    for (it = istenilen.begin(); it != istenilen.end(); ++it)
    {
        cout << '\t' << it->first << '\t' << it->second << '\n';
    }
    cout << endl;

    return 0;
}
