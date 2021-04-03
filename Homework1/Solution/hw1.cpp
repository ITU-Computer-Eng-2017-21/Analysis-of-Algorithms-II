#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <string>

using namespace std;

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
    stack<Node *> s;
    Tree t1;
    string puzzle = "TW";
    //Node n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13;

    Node *emptynode = new Node;
    emptynode->key_value = new map<char, int>;
    /*emptynode->key_value->insert(pair<char, int>('T', 0));
    emptynode->key_value->insert(pair<char, int>('W', 0));
    emptynode->key_value->insert(pair<char, int>('O', 0));
    emptynode->key_value->insert(pair<char, int>('F', 0));
    emptynode->key_value->insert(pair<char, int>('U', 0));
    emptynode->key_value->insert(pair<char, int>('R', 0));*/
    emptynode->c = '-';

    if (!t1.getRoot())
    {
        t1.root = emptynode;
    }

    s.push(emptynode);
    /*for (int i = 0; i < 3; i++)
    {
        int x = s.size();
        if (t1.getRoot()->C[i] == NULL)
        {
            cout << "NULL" << endl;
        }

        //cout << t1.getRoot()->C[i] << endl;
        s.push(t1.getRoot()->C[i]);
    }*/
    int counter = 0;
    while (!s.empty())
    {

        Node *current = s.top();
        s.pop();
        cout << "Popped" << endl;
        for (int i = 0; i < 10; i++)
        {
            int index = puzzle.find(current->c) + 1;
            //char password = '!';s
            if (index < puzzle.length())
            {
                char password = puzzle[index];
                //Node *a = new Node;
                current->C[i] = new Node;
                //Node *n1 = new Node;
                current->C[i]->key_value = new map<char, int>;

                map<char, int>::iterator itr;
                //cout << "\nThe map gquiz1 is : \n";
                //cout << "\tKEY\tELEMENT\n";
                for (itr = current->key_value->begin(); itr != current->key_value->end(); ++itr)
                {
                    current->C[i]->key_value->insert(pair<char, int>(itr->first, itr->second));
                }
                cout << endl;

                current->C[i]->a = i;
                current->C[i]->c = password;

                current->C[i]->key_value->insert(pair<char, int>(password, i));

                map<char, int>::iterator itrx;
                cout << "\nThe map " << current->C[i]->c << current->C[i]->a << " is : \n";
                cout << "\tKEY\tELEMENT\n";
                for (itrx = current->C[i]->key_value->begin(); itrx != current->C[i]->key_value->end(); ++itrx)
                {
                    //cout << current->C[i]->a << endl;

                    cout << '\t' << itrx->first << '\t' << itrx->second << '\n';
                }
                cout << endl;
                /*if (counter < 13)
                    s.push(current->C[i]);*/
                s.push(current->C[i]);
                cout << "Pushed" << endl;
                counter++;
            }
        }
    }

    /*for (int i = 0; i < 10; i++)
    {
        s.push(t1.getRoot()->C[i]);
    }

    while (s.empty())
    {
        Node *a = s.top();
        s.pop();
        for (int i = 0; i < 10; i++)
        {
            Node *x = new Node;
            map<char, int> *m1 = new map<char, int>;
            a->C[i] = x;
            a->key_value = *m1;
            s.push(x->C[i]);
        }

    }*/
    cout << "END" << endl;
}