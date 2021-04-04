#include <iostream>
#include <map>
#include <vector>
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
    //cout << number1 << endl;

    int number2 = 0;
    for (int i = 0; i < s2.length(); i++)
    {
        int digit = a[s2[i]];
        set1.insert(digit);
        int ust = (s2.length() - (i + 1));
        int temp = digit * pow(10, ust);
        number2 = number2 + temp;
    }
    //cout << number2 << endl;

    int number3 = 0;
    for (int i = 0; i < s3.length(); i++)
    {
        int digit = a[s3[i]];
        set1.insert(digit);
        int ust = (s3.length() - (i + 1));
        int temp = digit * pow(10, ust);
        number3 = number3 + temp;
    }
    //cout << number3 << endl;

    if (number1 + number2 == number3 && a[s1[0]] != 0 && a[s2[0]] && a[s3[0]] && set1.size() >= puzzle.length())
    {
        cout << "Solution: ";
        for (int i = 0; i < puzzle.length(); i++)
        {
            cout << puzzle[i] << ":" << a[puzzle[i]] << ", ";
        }
        cout << endl;

        /*map<char, int>::iterator itrx;
        for (itrx = a.begin(); itrx != a.end(); ++itrx)
        {
            //cout << current->C[i]->a << endl;

            cout << '\t' << itrx->first << '\t' << itrx->second << '\n';
        }
        cout << endl;*/
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
    //vector<Node *> next;
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

int main()
{
    //string s1 = "TWO"; // argv ile okuma
    //string s2 = "TWO";
    //string s3 = "FOUR";

    //string s1 = "DOWN"; // argv ile okuma
    //string s2 = "WWW";
    //string s3 = "ERROR";

    string s1 = "SEND"; // argv ile okuma
    string s2 = "MORE";
    string s3 = "MONEY";

    Tree t1;

    stack<Node *> s;

    //string puzzle = "TWOFUR"; // set'e çevirilebilir.
    //string puzzle = "DOWNER";
    string puzzle = "SENDMORY";

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
        //cout << "Popped" << endl;
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

                if (i != current->a && !matching)
                {

                    current->C[i] = new Node;
                    current->C[i]->key_value = new map<char, int>;

                    map<char, int>::iterator itr;
                    //cout << "\nThe map gquiz1 is : \n";
                    //cout << "\tKEY\tELEMENT\n";
                    for (itr = current->key_value->begin(); itr != current->key_value->end(); ++itr)
                    {
                        current->C[i]->key_value->insert(pair<char, int>(itr->first, itr->second));
                    }

                    //cout << endl;

                    current->C[i]->a = i;
                    current->C[i]->c = password;
                    current->C[i]->key_value->insert(pair<char, int>(password, i));

                    map<char, int>::iterator itrx;
                    //cout << "\nThe map " << current->C[i]->c << current->C[i]->a << " is : \n";
                    //cout << "\tKEY\tELEMENT\n";
                    /*for (itrx = current->C[i]->key_value->begin(); itrx != current->C[i]->key_value->end(); ++itrx)
                    {
                    //cout << current->C[i]->a << endl;

                    cout << '\t' << itrx->first << '\t' << itrx->second << '\n';
                    }
                    cout << endl;*/

                    if (password != puzzle[puzzle.length() - 1] && !matching)
                        s.push(current->C[i]);
                }

                //s.push(current->C[i]);
                //cout << "Pushed" << endl;
            }
        }
    }
    int counter = 0;
    auto time1 = chrono::high_resolution_clock::now();

    t1.DepthFirstSearch(t1.getRoot(), puzzle, s1, s2, s3);
    t1.BreathFirstSearch(t1.getRoot(), puzzle, s1, s2, s3);

    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = time2 - time1;
    cout << "Counter:" << counter << endl;
    cout << "Total running time is: " << duration.count() << " milliseconds." << endl;
    cout << "END" << endl;
}