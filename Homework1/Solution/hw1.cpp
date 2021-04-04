#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <chrono>
#include <cmath>
#include <set>

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
};

int main()
{
    string s1 = "TWO"; // argv ile okuma
    string s2 = "TWO";
    string s3 = "FOUR";

    Tree t1;

    stack<Node *> s;

    //string puzzle = "TWOFUR"; // set'e çevirilebilir.
    string puzzle = "TWOFUR";

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
                if (i != current->a)
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

                    if (password != puzzle[puzzle.length() - 1])
                        s.push(current->C[i]);
                }

                //s.push(current->C[i]);
                //cout << "Pushed" << endl;
            }
        }
    }
    int counter = 0;
    auto time1 = chrono::high_resolution_clock::now();
    stack<Node *> cop;
    cop.push(t1.getRoot());
    bool buldu = false;
    while (!cop.empty() && !buldu)
    {
        Node *current = cop.top();
        cop.pop();
        buldu = test(puzzle, s1, s2, s3, *current->key_value);
        counter++;
        for (int i = 0; i < DIGIT; i++)
        {
            if (current->C[-(i - (DIGIT - 1))])
            {
                cop.push((current)->C[-(i - (DIGIT - 1))]);
            }
        }
    }

    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = time2 - time1;
    cout << "Counter:" << counter << endl;
    cout << "Total running time is: " << duration.count() << " milliseconds." << endl;
    cout << "END" << endl;
}