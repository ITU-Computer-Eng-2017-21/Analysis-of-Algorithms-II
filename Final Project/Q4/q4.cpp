/* * * * * * * * * * * * * * * * * * * * * * * * * *
 * BLG 336E Analysis of Algorithms II
 * Spring 2021
 * Student Name: NESE GUNES
 * Student ID: 504192555
 * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <queue>

using namespace std;

class Solution
{
public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        // Create a color array to store colors
        // assigned to all veritces. Vertex
        // number is used as index in this array.
        // The value '-1' of colorArr[i]
        // is used to indicate that no color
        // is assigned to vertex 'i'. The value 1
        // is used to indicate first color
        // is assigned and value 0 indicates
        // second color is assigned.

        int V = 4;
        int src = 0;

        int colorArr[V];
        for (int i = 0; i < V; ++i)
            colorArr[i] = -1;

        // Assign first color to source
        colorArr[src] = 1;

        // Create a queue (FIFO) of vertex
        // numbers and enqueue source vertex
        // for BFS traversal
        queue<int> q;
        q.push(src);

        // Run while there are vertices
        // in queue (Similar to BFS)
        while (!q.empty())
        {
            // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
            int u = q.front();
            q.pop();

            // Return false if there is a self-loop
            //if (graph[u][u] == 1)
            //return false;

            // Find all non-colored adjacent vertices
            for (int i = 0; i < graph[u].size(); i++)
            {
                // An edge from u to v exists and
                // destination v is not colored
                if (colorArr[graph[u][i]] == -1)
                {
                    // Assign alternate color to this adjacent v of u
                    colorArr[graph[u][i]] = 1 - colorArr[u];
                    q.push(graph[u][i]);
                }

                // An edge from u to v exists and destination
                // v is colored with same color as u
                else if (colorArr[graph[u][i]] == colorArr[u])
                    return false;
            }
        }

        // If we reach here, then all adjacent
        // vertices can be colored with alternate color
        return true;
    }
};

// This function is provided to check if your graph data is stored well or not
void printv(vector<vector<int>> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
            cout << v[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    // Solution class for bipartite-ness problem
    Solution s;

    // Read data filename from std input stream and open it with file handler/pointer
    string fname;
    cin >> fname;
    ifstream graphFileHandler(fname);

    // An array of integers to store neighbours of a vertex
    vector<int> adj;
    // A 2D array of integers to store neighbours of each vertex in a graph
    vector<vector<int>> graph;

    string line;

    // Read from the file until there is no new line left
    while (graphFileHandler >> line)
    {
        // Save line as string stream object
        stringstream ss(line);
        // Get a string variable
        string substr;

        // Until the end of the line, read the line as substings separated by commas
        while (ss.good())
        {
            getline(ss, substr, ',');
            // Push the substring in adjacency list, we got a neighbour here
            adj.push_back(stoi(substr));
        }

        // When line ends, push all the neighbours of the vertex into the graph
        graph.push_back(adj);

        // Clear the array, before the next iteration begins
        // Next iteration, we will read the subsequent line from the file and it will contain neighbours of some other guy
        adj.clear();
    }

    // Check if data file is read in the way it is supposed to be
    // D O   N O T   P R I N T   T H E   G R A P H   I N   Y O U R   S O L U T I O N
    // The expected output only includes a True or a False not the graph data itself
    // Do not uncomment this line
    // printv(graph);

    // Save the return value of the function
    bool answer = s.isBipartite(graph);

    // If answer is True, print True otherwise False
    if (answer == 1)
        cout << "True" << endl;
    else
        cout << "False" << endl;

    return 0;
}
