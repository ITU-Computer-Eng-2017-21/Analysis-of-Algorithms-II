#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <chrono>
#include <cmath>

using namespace std;

void test(string s1, string s2, string s3)
{
    map<char, int> a;
    a.insert(pair<char, int>('T', 7));
    a.insert(pair<char, int>('W', 3));
    a.insert(pair<char, int>('O', 9));
    a.insert(pair<char, int>('F', 1));
    a.insert(pair<char, int>('U', 6));
    a.insert(pair<char, int>('R', 8));

    cout << a['T'] << endl;
    cout << a['W'] << endl;
    cout << a['O'] << endl;
    cout << a['F'] << endl;
    cout << a['U'] << endl;
    cout << a['R'] << endl;

    int number1 = 0;

    for (int i = 0; i < s1.length(); i++)
    {
        int digit = a[s1[i]];
        int ust = (s1.length() - (i + 1));
        int temp = digit * pow(10, ust);
        number1 = number1 + temp;
    }
    //cout << number1 << endl;

    int number2 = 0;
    for (int i = 0; i < s2.length(); i++)
    {
        int digit = a[s2[i]];
        int ust = (s2.length() - (i + 1));
        int temp = digit * pow(10, ust);
        number2 = number2 + temp;
    }
    //cout << number2 << endl;

    int number3 = 0;
    for (int i = 0; i < s3.length(); i++)
    {
        int digit = a[s3[i]];
        int ust = (s3.length() - (i + 1));
        int temp = digit * pow(10, ust);
        number3 = number3 + temp;
    }
    //cout << number3 << endl;

    if (number1 + number2 == number3)
        cout << "SUCCESFUL" << endl;
    else
        cout << "FAIL" << endl;
}
class Node
{
private:
public:
    map<char, int> *key_value;
    int a;
    char c;
    Node *C[10];
    //vector<Node *> next;
    Node(){};
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
    void insert(Node &a)
    {
    }
};

int main()
{
    string s1 = "TWO"; // argv ile okuma
    string s2 = "TWO";
    string s3 = "FOUR";

    Tree t1;

    stack<Node *> s;

    string puzzle = "TWOFUR"; // set'e çevirilebilir.
    //string puzzle = "SENDMORY";

    Node *emptynode = new Node;
    emptynode->key_value = new map<char, int>;
    emptynode->c = '-';

    if (!t1.getRoot())
    {
        t1.root = emptynode;
    }

    s.push(emptynode);

    auto time1 = chrono::high_resolution_clock::now();
    while (!s.empty())
    {

        Node *current = s.top();
        s.pop();
        //cout << "Popped" << endl;
        for (int i = 0; i < 10; i++)
        {
            int index = puzzle.find(current->c) + 1;
            if (index < puzzle.length())
            {
                char password = puzzle[index];
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
                /*if (counter < 13)
                    s.push(current->C[i]);*/
                s.push(current->C[i]);
                //cout << "Pushed" << endl;
            }
        }
    }

    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = time2 - time1;

    cout << "Total running time is: " << duration.count() << " milliseconds." << endl;
    cout << "END" << endl;
}