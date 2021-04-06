/*  
    @author: Barış İncesu
    @ID: 150170092
    @date :4.02.2021
    ///////////////////////////
    Compile:
    g++ -std=c++11 150170092.cpp -o hw1
    Run:
    ./hw1 DFS TWO TWO FOUR outputFileName
*/

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <set>
#include <queue>
#include <cmath>
#include <chrono>
#include <fstream>

#define DIGIT 10

using namespace std;
/*map values checking possible solutions in isSolution function*/
bool Solution(string puzzle, string s1, string s2, string s3, map<char, int> a, string outputFileName)
{
    set<int, greater<int>> solutionSet; //counting different digits

    int number1 = 0; //calculate first number SEND = 9567
    for (int i = 0; i < s1.length(); i++)
    {
        int base = a[s1[i]];
        solutionSet.insert(base); // 9, 5, 6, 7
        int exponent = (s1.length() - (i + 1));
        int temp = base * pow(10, exponent);
        number1 = number1 + temp;
    }

    int number2 = 0; //calculate first number MORE = 1085
    for (int i = 0; i < s2.length(); i++)
    {
        int base = a[s2[i]];
        solutionSet.insert(base); // 1, 0, 8, 5
        int exponent = (s2.length() - (i + 1));
        int temp = base * pow(10, exponent);
        number2 = number2 + temp;
    }

    int number3 = 0; //calculate first number MONEY = 10652
    for (int i = 0; i < s3.length(); i++)
    {
        int base = a[s3[i]];
        solutionSet.insert(base); // 1, 0, 6, 5, 2
        int exponent = (s3.length() - (i + 1));
        int temp = base * pow(10, exponent);
        number3 = number3 + temp;
    }

    //9567 + 1085 =? 10652 //[S]END [M]ORE [M]ONEY SMM cannot be equal 0 //solutionSet = {9,5,6,7,1,0,8,2} has 8 number == SENDMORY length
    if (number1 + number2 == number3 && a[s1[0]] != 0 && a[s2[0]] && a[s3[0]] && solutionSet.size() == puzzle.length())
    {
        cout << "Solution: "; // solution output
        for (int i = 0; i < puzzle.length(); i++)
        {
            cout << puzzle[i] << ":" << a[puzzle[i]];
            if (i < puzzle.length() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;

        ofstream file; //writing solution to txt file
        file.open(outputFileName + ".txt");

        file << "	0	1	2	3	4	5	6	7	8	9\n";
        for (int i = 0; i < a.size(); i++)
        {
            file << puzzle[i];
            for (int j = 0; j < 9; j++)
            {
                if (a[puzzle[i]] == j)
                {
                    file << "	" << 1;
                }
                file << "	.";
            }
            if (a[puzzle[i]] == 9)
            {
                file << "	" << 1;
            }
            file << "\n";
        }
        file.close();
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
/*root, SENDMORY, SEND, MORE, MONEY, outputFileName*/
void Tree::DepthFirstSearch(Node *root, string puzzle, string s1, string s2, string s3, string outputFileName)
{
    int counterVisited = 0;

    stack<Node *> memoryStack;
    memoryStack.push(root);
    bool solved = false;

    while (!memoryStack.empty() && !solved)
    {
        Node *current = memoryStack.top();
        memoryStack.pop();

        solved = Solution(puzzle, s1, s2, s3, *current->key_value, outputFileName);
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
}
/*root, SENDMORY, SEND, MORE, MONEY, outputFileName*/
void Tree::BreathFirstSearch(Node *root, string puzzle, string s1, string s2, string s3, string outputFileName)
{
    int counterVisited = 0;

    queue<Node *> memoryQueue;
    memoryQueue.push(root);
    bool solved = false;
    while (!memoryQueue.empty() && !solved)
    {
        Node *current = memoryQueue.front();
        memoryQueue.pop();

        solved = Solution(puzzle, s1, s2, s3, *current->key_value, outputFileName);
        counterVisited++;
        for (int i = 0; i < DIGIT; i++)
        {
            if (current->C[i])
            {
                memoryQueue.push((current)->C[i]);
            }
        }
    }
    cout << "Number of the visited nodes: " << counterVisited << endl;
}

int main(int argc, char **argv)
{
    string type = argv[1];

    string s1 = argv[2];

    set<char> puzzleSet;
    for (int i = 0; i < s1.length(); i++)
    {
        puzzleSet.insert(s1[i]);
    }

    string s2 = argv[3];
    for (int i = 0; i < s2.length(); i++)
    {
        puzzleSet.insert(s2[i]);
    }

    string s3 = argv[4];
    for (int i = 0; i < s3.length(); i++)
    {
        puzzleSet.insert(s3[i]);
    }

    string outputFileName = argv[5];

    string puzzle = "";
    set<char, greater<int>>::iterator itr;
    for (itr = puzzleSet.begin(); itr != puzzleSet.end(); itr++)
    {
        puzzle += *itr;
    }

    Tree t1;
    stack<Node *> s;

    Node *emptyNode = new Node;
    emptyNode->key_value = new map<char, int>;
    emptyNode->a = DIGIT + 1;
    emptyNode->c = '-';

    if (!t1.getRoot())
    {
        t1.root = emptyNode;
    }
    int counterMaxMemory = 1;
    s.push(emptyNode);

    // Creating tree structure
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
                    counterMaxMemory++;

                    if (password != puzzle[puzzle.length() - 1])
                        s.push(current->C[i]);
                }
            }
        }
    }

    cout << "Algorithm: " << type << endl;
    if (type == "DFS")
    {
        auto dfstime1 = chrono::high_resolution_clock::now();
        t1.DepthFirstSearch(t1.getRoot(), puzzle, s1, s2, s3, outputFileName);
        auto dfstime2 = chrono::high_resolution_clock::now();

        chrono::duration<double> dfsduration = dfstime2 - dfstime1;
        cout << "Maximum number of nodes kept in the memory: " << counterMaxMemory << endl;
        cout << "Running time: " << dfsduration.count() << " seconds" << endl;
    }
    if (type == "BFS")
    {
        auto bfstime1 = chrono::high_resolution_clock::now();
        t1.BreathFirstSearch(t1.getRoot(), puzzle, s1, s2, s3, outputFileName);
        auto bfstime2 = chrono::high_resolution_clock::now();

        chrono::duration<double> bfsduration = bfstime2 - bfstime1;
        cout << "Maximum number of nodes kept in the memory: " << counterMaxMemory << endl;
        cout << "Running time: " << bfsduration.count() << " seconds" << endl;
    }
    return 0;
}