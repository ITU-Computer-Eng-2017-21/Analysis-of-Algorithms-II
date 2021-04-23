/*  
    @author: Barış İncesu
    @ID: 150170092
    @date :23.04.2021

    Compile: g++ -std=c++11 -Wall -Werror q1.cpp -o q1
    Run: ./q2
    Calico: python -m calico.cli q2_tc_v3.t
*/

#include <iostream> // basic library for cout
#include <fstream>  // file operation
#include <string>   // string operation
#include <queue>    // priority queue for Prim Algorithm
#include <set>
#include <vector>
#include <map>
#include <functional> // map sort by value
using namespace std;
#define INF 0x3f3f3f3f

// iPair ==> Integer Pair
typedef pair<int, int> iPair;

// function to return position in map
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

// To add an edge
void addEdge(vector<pair<int, int>> adj[], string us, string vs, int wt, set<string> s1)
{
    int u, v;
    u = positionSet(s1, us);
    v = positionSet(s1, vs);

    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

// Prints shortest paths from src to all other vertices
map<string, int> primMST(vector<pair<int, int>> adj[], int V, map<int, string> m1, int point_GP, int point_Hipp, int point_Chx, int weight_GPtoHipp, int weight_GPtoChx)
{
    // Create a priority queue to store vertices that
    // are being preinMST.
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    int src = point_GP;  // Taking vertex point of GP as source
    map<string, int> mx; // mx is record of MST Edges

    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(V, INF);

    // To store parent array which in turn store MST
    vector<int> parent(V, -1);

    // To keep track of vertices included in MST
    vector<bool> inMST(V, false);

    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push(make_pair(-1, src));
    key[src] = 0;
    parent[src] = src;

    // Insert GP - Hipp Edge
    // its key as weight_GPtoHipp.
    // Hipp's parent => GP
    pq.push(make_pair(-1, point_Hipp));
    key[point_Hipp] = weight_GPtoHipp;
    parent[point_Hipp] = src;

    // Chx is nearest Church to GP.
    // Insert GP - Chx Edge
    // its key as weight_GPtoChx.
    // Chx's parent => GP
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
                // Dont Change Hipp's and Chx's key.
                if (v != point_Hipp && v != point_Chx)
                {
                    key[v] = weight;
                }
                pq.push(make_pair(key[v], v));
                // Dont Change Hipp's and Chx's parent.
                if (v != point_Hipp && v != point_Chx)
                {
                    // Updating key of v
                    parent[v] = u;
                }
            }
        }
    }

    // Record edges of MST using parent array and key
    for (int i = 0; i < V; ++i)
    {
        if (i != src)
        {
            mx.insert(pair<string, int>(m1[parent[i]] + ' ' + m1[i], key[i]));
        }
    }
    return mx;
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

    string source, destination, weight;

    // First Reading for detect points and insert points to set s1.
    while (!file1.eof())
    {
        // "," e kadar oku. String olarak al.
        getline(file1, source, ',');
        getline(file1, destination, ',');
        getline(file1, weight, '\n');

        s1.insert(source);
        s1.insert(destination);
    }

    int V = s1.size(); // graph size = point number
    vector<iPair> adj[V];

    // set s1 values copy to map m1
    map<int, string> m1;
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

    // Second reading for creating edges and detect some critical edges with points in s1.
    int weight_GPtoChx = 0;

    int point_GP = positionSet(s1, "GP"), point_Hipp = positionSet(s1, "Hipp"), point_Chx, weight_GPtoHipp;

    while (!file2.eof())
    {
        getline(file2, source, ',');
        getline(file2, destination, ',');
        getline(file2, weight, '\n');

        int c1 = source.find("Ch");
        int c2 = destination.find("GP");

        int c3 = source.find("GP");
        int c4 = destination.find("Ch");
        // Nearest Church Detect
        if ((c1 != -1 && c2 != -1) || (c3 != -1 && c4 != -1))
        {
            if (weight_GPtoChx == 0 || stoi(weight) < weight_GPtoChx)
            {
                weight_GPtoChx = stoi(weight);
                if (c1 != -1 && c2 != -1)
                {
                    point_Chx = positionSet(s1, source);
                }
                else if (c3 != -1 && c4 != -1)
                {
                    point_Chx = positionSet(s1, destination);
                }
            }
        }

        int gphipp1 = source.find("GP");
        int gphipp2 = destination.find("Hipp");

        int gphipp3 = source.find("Hipp");
        int gphipp4 = destination.find("GP");

        // GP - Hipp Edge detect
        if ((gphipp1 != -1 && gphipp2 != -1) || (gphipp3 != -1 && gphipp4 != -1))
        {
            weight_GPtoHipp = stoi(weight);
        }

        int index1 = source.find("Hp");
        int index2 = destination.find("Hp");

        int index3 = source.find("Hipp");
        int index4 = destination.find("Bas");

        int index5 = source.find("Bas");
        int index6 = destination.find("Hipp");

        // Hpx -> Hpx and Hipp <-> Basicila Edge Detect and create graph
        if (!((index1 != -1 && index2 != -1) || (index3 != -1 && index4 != -1) || (index5 != -1 && index6 != -1)))
        {
            addEdge(adj, source, destination, stoi(weight), s1);
        }
    }
    // start algorithm and find MST Edges
    map<string, int> istenilen = primMST(adj, V, m1, point_GP, point_Hipp, point_Chx, weight_GPtoHipp, weight_GPtoChx);

    // Read3 for MST Edge adjhust for expected output form, sorted by weight and Source -> Destination
    ifstream file3;
    file3.open(filename);

    if (!file3)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    // Last output form of MST Edges
    map<string, int> istenilenson;
    while (!file3.eof())
    {
        // "," e kadar oku. String olarak al.
        getline(file3, source, ',');
        getline(file3, destination, ',');
        getline(file3, weight, '\n');

        map<string, int>::iterator it;
        for (it = istenilen.begin(); it != istenilen.end(); ++it)
        {
            // Destination -> Source convert to Source -> Destination
            if (source == it->first.substr(0, it->first.find(' ')) && destination == it->first.substr(it->first.find(' ') + 1, it->first.length()) && stoi(weight) == it->second)
            {
                istenilenson.insert(pair<string, int>(source + ' ' + destination, it->second));
            }
            else if (destination == it->first.substr(0, it->first.find(' ')) && source == it->first.substr(it->first.find(' ') + 1, it->first.length()) && stoi(weight) == it->second)
            {
                istenilenson.insert(pair<string, int>(source + ' ' + destination, it->second));
            }
        }

        s1.insert(source);
        s1.insert(destination);
    }

    typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;
    // Defining a lambda function to compare two pairs. It will compare two pairs using second field
    Comparator compFunctor =
        [](std::pair<std::string, int> elem1, std::pair<std::string, int> elem2) {
            return elem1.second < elem2.second;
        };
    // Declaring a set that will store the pairs using above comparision logic
    std::set<std::pair<std::string, int>, Comparator> setOfWords(istenilenson.begin(), istenilenson.end(), compFunctor);
    // Iterate over a set using range base for loop
    // It will display the items in sorted order of values
    int totalCost = 0;
    for (std::pair<std::string, int> element : setOfWords)
    {
        cout << element.first.substr(0, element.first.find(' ')) << ' ' << element.first.substr(element.first.find(' ') + 1, element.first.length()) << ' ' << element.second << '\n';
        totalCost = totalCost + element.second;
    }
    cout << totalCost << '\n';

    return 0;
}
