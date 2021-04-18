// STL implementation of Prim's algorithm for MST
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

// iPair ==> Integer Pair
typedef pair<int, int> iPair;

// To add an edge
void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

// Prints shortest paths from src to all other vertices
void primMST(vector<pair<int, int>> adj[], int V, map<int, string> m1)
{
    // Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    int src = 0; // Taking vertex 0 as source

    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(V, INF);

    // To store parent array which in turn store MST
    vector<int> parent(V, -1);

    // To keep track of vertices included in MST
    vector<bool> inMST(V, false);

    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push(make_pair(0, 1));
    //key[src] = 2000;
    key[1] = 2000;
    parent[1] = 0;

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

        //key[1] = 2000;
        //parent[1] = 0;
        //inMST[1] = true;
        inMST[u] = true; // Include vertex in MST

        // Traverse all adjacent of u
        for (auto x : adj[u])
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = x.first;
            int weight = x.second;

            // If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if (inMST[v] == false && key[v] > weight)
            {
                // Updating key of v
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Print edges of MST using parent array
    for (int i = 1; i < V; ++i)
    {
        cout << m1[parent[i]] << "," << m1[i] << "," << key[i] << "\n";
        //cout << m1[i] << "," << m1[parent[i]] << "," << key[i] << "\n";
        //cout << "------------\n";
        printf("%d - %d\n", parent[i], i);
    }
}

// Driver program to test methods of graph class
int main()
{
    int V = 11;
    vector<iPair> adj[V];

    map<int, string> m1;

    m1.insert(pair<int, string>(0, "GP"));
    m1.insert(pair<int, string>(1, "Hipp"));
    m1.insert(pair<int, string>(2, "Bas1"));
    m1.insert(pair<int, string>(3, "Bas2"));
    m1.insert(pair<int, string>(4, "Bas3"));
    m1.insert(pair<int, string>(5, "Ch1"));
    m1.insert(pair<int, string>(6, "Ch2"));
    m1.insert(pair<int, string>(7, "Hp1"));
    m1.insert(pair<int, string>(8, "Hp2"));
    m1.insert(pair<int, string>(9, "Hp3"));
    m1.insert(pair<int, string>(10, "Hp4"));

    addEdge(adj, 0, 1, 12);
    addEdge(adj, 0, 6, 2);
    addEdge(adj, 0, 4, 9);
    addEdge(adj, 0, 10, 8);
    addEdge(adj, 0, 3, 6);
    addEdge(adj, 1, 5, 1);
    addEdge(adj, 1, 7, 7);
    //addEdge(adj, 1, 2, 14); //
    addEdge(adj, 1, 6, 13);
    addEdge(adj, 1, 8, 10);
    addEdge(adj, 2, 6, 15);
    addEdge(adj, 6, 4, 4);
    addEdge(adj, 4, 10, 16);
    addEdge(adj, 4, 9, 11);
    //addEdge(adj, 9, 10, 17);
    addEdge(adj, 9, 3, 3);
    addEdge(adj, 3, 8, 18);
    //addEdge(adj, 10, 8, 5); //

    // making above shown graph
    /*
    addEdge(adj, 0, 1, 4);
    addEdge(adj, 1, 2, 17);
    addEdge(adj, 3, 4, 13);
    addEdge(adj, 4, 5, 5);
    addEdge(adj, 6, 7, 12);
    addEdge(adj, 7, 8, 2);

    addEdge(adj, 0, 3, 8);
    addEdge(adj, 1, 4, 14);
    addEdge(adj, 2, 5, 3);
    addEdge(adj, 3, 6, 7);
    addEdge(adj, 4, 7, 10);
    addEdge(adj, 5, 8, 12);
    addEdge(adj, 7, 9, 9);

    addEdge(adj, 0, 4, 11);
    addEdge(adj, 2, 4, 13);
    addEdge(adj, 3, 7, 9);
    addEdge(adj, 5, 7, 6);
    addEdge(adj, 6, 9, 11);
    addEdge(adj, 8, 9, 10);
    */

    primMST(adj, V, m1);

    return 0;
}
