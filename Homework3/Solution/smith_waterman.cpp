#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <bits/stdc++.h>

//#include <algorithm>
//#include <initializer_list>

using namespace std;

int max(int a, int b, int c)
{
    int val = a;
    if (b > val)
    {
        val = b;
    }
    if (c > val)
    {
        val = c;
    }
    return val;
}

bool compare(int i, int j, string s1, string s2)
{
    if (s1[i - 1] == s2[j - 1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void sw(string s1, string s2, string fileName)
{
    // std::ios::app is the open mode "append" meaning
    // new data will be written to the end of the file.
    ofstream outFile;
    outFile.open(fileName, std::ios::app);

    const int lengthOfs1 = s1.length();
    const int lengthOfs2 = s2.length();

    int scoreMatrix[lengthOfs1 + 1][lengthOfs2 + 1];

    for (int i = 0; i < lengthOfs1 + 1; i++)
    {
        for (int j = 0; j < lengthOfs2 + 1; j++)
        {
            scoreMatrix[i][j] = 0;
        }
    }

    /*for (int j = 0; j < lengthOfs2 + 1; j++)
    {
        scoreMatrix[0][j] = 0 + j;
    }

    for (int i = 0; i < lengthOfs1 + 1; i++)
    {
        scoreMatrix[i][0] = 0 + i;
    }*/

    for (int row = 1; row < lengthOfs1 + 1; row++)
    {
        for (int column = 1; column < lengthOfs2 + 1; column++)
        {
            //int left_down = scoreMatrix[row][column - 1] - 2;
            //int right_up = scoreMatrix[row - 1][column] - 2;
            int diag = scoreMatrix[row - 1][column - 1];

            if (compare(row, column, s1, s2))
            {
                diag = diag + 1;
                scoreMatrix[row][column] = diag;
            }
            else
            {
                diag = 0;
                scoreMatrix[row][column] = diag;
            }

            /*if (left_down < 0)
            {
                left_down = 0;
            }
            if (right_up < 0)
            {
                right_up = 0;
            }
            if (diag < 0)
            {
                diag = 0;
            }
            int indel = max(left_down, right_up, diag);
            scoreMatrix[row][column] = indel;*/
        }
    }

    int target_length = 0;
    int target_number = 0;
    for (int i = 0; i < lengthOfs1 + 1; i++)
    {
        for (int j = 0; j < lengthOfs2 + 1; j++)
        {
            if (scoreMatrix[i][j] > target_length)
            {
                target_length = scoreMatrix[i][j];
            }
        }
    }

    for (int i = 0; i < lengthOfs1 + 1; i++)
    {
        for (int j = 0; j < lengthOfs2 + 1; j++)
        {
            if (scoreMatrix[i][j] == target_length)
            {
                target_number++;
            }
        }
    }

    int positions[target_number];
    int offset = 0;

    for (int i = 0; i < lengthOfs1 + 1; i++)
    {
        for (int j = 0; j < lengthOfs2 + 1; j++)
        {
            if (scoreMatrix[i][j] == target_length)
            {
                positions[offset] = j;
                offset++;
            }
        }
    }

    //scoreMatrix[2][3] = 111;
    outFile << s1 << " - " << s2 << "\n";
    //cout << s1 << " - " << s2 << endl;
    /*for (int i = 0; i < lengthOfs1 + 1; i++)
        {
            for (int j = 0; j < lengthOfs2 + 1; j++)
            {
                cout << scoreMatrix[i][j] << "\t";
            }
            cout << endl;
        }*/

    outFile << "Score: " << target_length << " Sequence(s): ";
    //cout << "Score: " << target_length << " Sequence(s): ";

    set<string> outputvector;

    for (int i = 0; i < target_number; i++)
    {

        int end = positions[i] - 1;
        int start = end - target_length + 1;
        string outputx = s2.substr(start, target_length);
        //cout << positions[i] << endl;
        //cout << "target: " << outputx << endl;
        outputvector.insert(outputx);
    }
    //sort(outputvector.begin(), outputvector.end());
    for (auto i = outputvector.begin(); i != outputvector.end(); ++i)
    {
        outFile << "\"" << *i << "\""
                << " ";
        //cout << "\"" << *i << "\"" << " ";
    }
    outFile << "\n";
    //cout << endl;
    // information_tunction_yesişim1_esişim2_kesişim3
    //cout << "Hello World!" << endl;

    //cout << "------------------------------------------------" << endl;
}

int main()
{
    string filename;
    cin >> filename;
    //filename = "strings.txt";

    ifstream file1;
    file1.open(filename);

    if (!file1)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string word;
    vector<string> v1;

    while (!file1.eof())
    {
        getline(file1, word, '\n');
        v1.push_back(word);
    }

    /*v1.push_back("information");
    v1.push_back("fanimatio");

    v1.push_back("malfunction");
    v1.push_back("automative");
    v1.push_back("medication");
    v1.push_back("paramedic");
    v1.push_back("automata");
    v1.push_back("flammable");
    v1.push_back("compatibility");
    v1.push_back("ability");
    v1.push_back("certificate");
    v1.push_back("directive");
    v1.push_back("conformity");
    v1.push_back("component");
    v1.push_back("examination");
    v1.push_back("predict");
    v1.push_back("disctrict");
    v1.push_back("fountain");
    v1.push_back("personality");
    v1.push_back("qualify");*/

    sort(v1.begin(), v1.end());
    string s1 = "ABCTABS";
    string s2 = "ABCDABS";

    string fileName = "150170092_result.txt";

    for (unsigned int i = 0; i < v1.size(); i++)
    {
        for (unsigned int j = i + 1; j < v1.size(); j++)
        {
            s1 = v1.at(i);
            s2 = v1.at(j);
            sw(s1, s2, fileName);
        }
    }
}