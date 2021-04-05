/*  
    @author: Barış İncesu
    @ID: 150170092
    @date :4.02.2021
    ///////////////////////////
    Compile:
    g++ -std=c++11 150170092.cpp -o 150170092
    Run:
    ./150170092 DFS TWO TWO FOUR outputFileName
*/

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <chrono>
#include <cmath>
#include <set>
#include <queue>

#include <fstream>

#define DIGIT 10

using namespace std;

bool test(string puzzle, string s1, string s2, string s3, map<char, int> a, string outputFileName)
{
    int number1 = 0;
    set<int, greater<int>> set1;

    for (int i = 0; i < s1.length(); i++)
    {
        int digit = a[s1[i]];
        set1.insert(digit);
        int ust = (s1.length() - (i + 1));
        int temp = digit * pow(10, ust);
        number1 = number1 + temp;
    }

    int number2 = 0;
    for (int i = 0; i < s2.length(); i++)
    {
        int digit = a[s2[i]];
        set1.insert(digit);
        int ust = (s2.length() - (i + 1));
        int temp = digit * pow(10, ust);
        number2 = number2 + temp;
    }

    int number3 = 0;
    for (int i = 0; i < s3.length(); i++)
    {
        int digit = a[s3[i]];
        set1.insert(digit);
        int ust = (s3.length() - (i + 1));
        int temp = digit * pow(10, ust);
        number3 = number3 + temp;
    }

    if (number1 + number2 == number3 && a[s1[0]] != 0 && a[s2[0]] && a[s3[0]] && set1.size() == puzzle.length())
    {
        cout << "Solution: ";
        for (int i = 0; i < puzzle.length(); i++)
        {
            cout << puzzle[i] << ":" << a[puzzle[i]] << ", ";
        }
        cout << endl;

        ofstream myfile;
        myfile.open(outputFileName + ".txt");

        myfile << "	0	1	2	3	4	5	6	7	8	9\n";
        for (int i = 0; i < a.size(); i++)
        {
            myfile << puzzle[i];
            for (int j = 0; j < 9; j++)
            {
                if (a[puzzle[i]] == j)
                {
                    myfile << "	" << 1;
                }
                myfile << "	.";
            }
            if (a[puzzle[i]] == 9)
            {
                myfile << "	" << 1;
            }
            myfile << "\n";
        }
        myfile.close();
        return true;
    }

    else
        return false;
}
class Node
{
private:
public:
    map<char, int> *key_value;
    int a;
    char c;
    Node *C[DIGIT];
    Node()
    {
        for (int i = 0; i < DIGIT; i++)
        {
            C[i] = NULL;
        }
    };
    ~Node(){};
};

class Tree
{
private:
public:
    Node *root;
    Tree() { root = NULL; };
    ~Tree(){};

    Node *getRoot() { return root; };
    void DepthFirstSearch(Node *, string, string, string, string, string);
    void BreathFirstSearch(Node *, string, string, string, string, string);
};

void Tree::DepthFirstSearch(Node *root, string puzzle, string s1, string s2, string s3, string outputFileName)
{
    int counterMaxMemory = 0;
    int counterVisited = 0;
    int temp = 0;

    stack<Node *> memoryStack;
    memoryStack.push(root);
    bool buldu = false;

    while (!memoryStack.empty() && !buldu)
    {
        int temp = memoryStack.size();
        if (temp > counterMaxMemory)
        {
            counterMaxMemory = temp;
        }

        Node *current = memoryStack.top();
        memoryStack.pop();

        buldu = test(puzzle, s1, s2, s3, *current->key_value, outputFileName);
        counterVisited++;
        for (int i = 0; i < DIGIT; i++)
        {

            if (current->C[-(i - (DIGIT - 1))])
            {
                memoryStack.push((current)->C[-(i - (DIGIT - 1))]);
            }
        }
    }
    cout << "Number of the visited nodes: " << counterVisited << endl;
    cout << "Maximum number of nodes kept in the memory: " << counterMaxMemory << endl;
}

void Tree::BreathFirstSearch(Node *root, string puzzle, string s1, string s2, string s3, string outputFileName)
{
    int counterMaxMemory = 0;
    int counterVisited = 0;
    int temp = 0;

    queue<Node *> memoryQueue;
    memoryQueue.push(root);
    bool buldu = false;
    while (!memoryQueue.empty() && !buldu)
    {
        int temp = memoryQueue.size();
        if (temp > counterMaxMemory)
        {
            counterMaxMemory = temp;
        }

        Node *current = memoryQueue.front();
        memoryQueue.pop();

        buldu = test(puzzle, s1, s2, s3, *current->key_value, outputFileName);
        counterVisited++;
        for (int i = 0; i < DIGIT; i++)
        {
            if (current->C[-(i - (DIGIT - 1))])
            {
                memoryQueue.push((current)->C[-(i - (DIGIT - 1))]);
            }
        }
    }
    cout << "Number of the visited nodes: " << counterVisited << endl;
    cout << "Maximum number of nodes kept in the memory: " << counterMaxMemory << endl;
}

int main(int argc, char **argv)
{

    //string puzzle = "TWOFUR"; // set'e çevirilebilir.
    string puzzle = "DOWNER";
    //string puzzle = "SENDMORY";
    string outputFileName = "outputFileName";
    string type = "DFS";
    //string type = "BFS";

    //string s1 = "TWO"; // argv ile okuma
    //string s2 = "TWO";
    //string s3 = "FOUR";

    string s1 = "DOWN"; // argv ile okuma
    string s2 = "WWW";
    string s3 = "ERROR";

    //string s1 = "SEND"; // argv ile okuma
    //string s2 = "MORE";
    //string s3 = "MONEY";
    //string type = argv[1];
    string xp = "";

    //string s1 = argv[2];
    set<char> pset;
    for (int i = 0; i < s1.length(); i++)
    {
        pset.insert(s1[i]);
    }
    //string s2 = argv[3];
    for (int i = 0; i < s2.length(); i++)
    {
        pset.insert(s2[i]);
    }
    //string s3 = argv[4];
    for (int i = 0; i < s3.length(); i++)

    {
        pset.insert(s3[i]);
    }

    //string outputFileName = argv[5];

    set<char, greater<int>>::iterator itr;
    //cout << "\nThe set s1 is : \n";
    for (itr = pset.begin(); itr != pset.end(); itr++)
    {
        xp += *itr;
    }
    puzzle = xp;
    cout << "Algorithm: " << type << endl;

    Tree t1;
    stack<Node *> s;

    Node *emptynode = new Node;
    emptynode->key_value = new map<char, int>;
    emptynode->a = DIGIT + 1;
    emptynode->c = '-';

    if (!t1.getRoot())
    {
        t1.root = emptynode;
    }

    s.push(emptynode);

    while (!s.empty())
    {

        Node *current = s.top();
        s.pop();

        int index = puzzle.find(current->c) + 1;
        if (index < puzzle.length())
        {
            char password = puzzle[index];

            for (int i = 0; i < DIGIT; i++)
            {
                bool matching = false;
                for (auto it = current->key_value->begin(); it != current->key_value->end(); ++it)
                    if (it->second == i)
                    {
                        matching = true;
                    }

                if (!matching)
                {

                    current->C[i] = new Node;
                    current->C[i]->key_value = new map<char, int>;

                    map<char, int>::iterator itr; // copy map root to chield
                    for (itr = current->key_value->begin(); itr != current->key_value->end(); ++itr)
                    {
                        current->C[i]->key_value->insert(pair<char, int>(itr->first, itr->second));
                    }

                    current->C[i]->a = i;
                    current->C[i]->c = password;
                    current->C[i]->key_value->insert(pair<char, int>(password, i));

                    if (password != puzzle[puzzle.length() - 1])
                        s.push(current->C[i]);
                }
            }
        }
    }

    if (type == "DFS")
    {
        auto dfstime1 = chrono::high_resolution_clock::now();
        t1.DepthFirstSearch(t1.getRoot(), puzzle, s1, s2, s3, outputFileName);
        auto dfstime2 = chrono::high_resolution_clock::now();

        chrono::duration<double> dfsduration = dfstime2 - dfstime1;
        cout << "Running time: " << dfsduration.count() << " seconds" << endl;
    }
    if (type == "BFS")
    {
        auto bfstime1 = chrono::high_resolution_clock::now();
        t1.BreathFirstSearch(t1.getRoot(), puzzle, s1, s2, s3, outputFileName);
        auto bfstime2 = chrono::high_resolution_clock::now();

        chrono::duration<double> bfsduration = bfstime2 - bfstime1;
        cout << "Running time: " << bfsduration.count() << " seconds" << endl;
    }
    return 0;
}