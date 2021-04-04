/*  
    @author: Barış İncesu
    @ID: 150170092
    @date :4.02.2021
    ///////////////////////////
    Compile:
    g++ -std=c++11 150170092.cpp -o 150170092
    Run:
    ./150170092 DFS TWO TWO FOUR
*/

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <chrono>
#include <cmath>
#include <set>
#include <queue>

#define DIGIT 10

using namespace std;

bool test(string puzzle, string s1, string s2, string s3, map<char, int> a)
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
    void DepthFirstSearch(Node *, string, string, string, string);
    void BreathFirstSearch(Node *, string, string, string, string);
};

void Tree::DepthFirstSearch(Node *root, string puzzle, string s1, string s2, string s3)
{
    stack<Node *> cop;
    cop.push(root);
    bool buldu = false;
    while (!cop.empty() && !buldu)
    {
        Node *current = cop.top();
        cop.pop();
        buldu = test(puzzle, s1, s2, s3, *current->key_value);
        for (int i = 0; i < DIGIT; i++)
        {
            if (current->C[-(i - (DIGIT - 1))])
            {
                cop.push((current)->C[-(i - (DIGIT - 1))]);
            }
        }
    }
}

void Tree::BreathFirstSearch(Node *root, string puzzle, string s1, string s2, string s3)
{
    queue<Node *> cop;
    cop.push(root);
    bool buldu = false;
    while (!cop.empty() && !buldu)
    {
        Node *current = cop.front();
        cop.pop();
        buldu = test(puzzle, s1, s2, s3, *current->key_value);
        for (int i = 0; i < DIGIT; i++)
        {
            if (current->C[-(i - (DIGIT - 1))])
            {
                cop.push((current)->C[-(i - (DIGIT - 1))]);
            }
        }
    }
}

int main(int argc, char **argv)
{
    string type = argv[1];
    string xp = "";

    string s1 = argv[2];
    set<char> pset;
    for (int i = 0; i < s1.length(); i++)
    {
        pset.insert(s1[i]);
    }
    string s2 = argv[3];
    for (int i = 0; i < s2.length(); i++)
    {
        pset.insert(s2[i]);
    }
    string s3 = argv[4];
    for (int i = 0; i < s3.length(); i++)

    {
        pset.insert(s3[i]);
    }
    set<char, greater<int>>::iterator itr;
    //cout << "\nThe set s1 is : \n";
    for (itr = pset.begin(); itr != pset.end(); itr++)
    {
        xp += *itr;
    }
    string puzzle = xp;
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
    int counter = 0;
    if (type == "DFS")
    {
        auto dfstime1 = chrono::high_resolution_clock::now();
        t1.DepthFirstSearch(t1.getRoot(), puzzle, s1, s2, s3);
        auto dfstime2 = chrono::high_resolution_clock::now();

        chrono::duration<double> dfsduration = dfstime2 - dfstime1;
        cout << "Running time: " << dfsduration.count() << " seconds" << endl;
        cout << "Number of the visited nodes: " << endl;
        cout << "Maximum number of nodes kept in the memory: " << endl;
    }
    if (type == "BFS")
    {
        auto bfstime1 = chrono::high_resolution_clock::now();
        t1.BreathFirstSearch(t1.getRoot(), puzzle, s1, s2, s3);
        auto bfstime2 = chrono::high_resolution_clock::now();

        chrono::duration<double> bfsduration = bfstime2 - bfstime1;
        cout << "Running time: " << bfsduration.count() << " seconds" << endl;
        cout << "Number of the visited nodes: " << endl;
        cout << "Maximum number of nodes kept in the memory: " << endl;
    }
    return 0;
}