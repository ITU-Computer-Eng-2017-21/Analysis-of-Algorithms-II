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
#include <fstream>  // file operation
//#include <sstream>    // string stream operaiton
#include <string> // string operation
//#include <algorithm>
#include <list>
#include <set>
#include <vector>
#include <map>
#include <queue>      // priority queue for Prim Algorithm
#include <functional> // map sort by value

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
    pq.push(make_pair(-1, src));
    key[src] = 0;
    parent[src] = src;

    pq.push(make_pair(-1, point_Hipp));
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
    // create the graph given in above fugure
    int V = s1.size();
    Graph g(V);

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
    //sort(istenilenson);

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
