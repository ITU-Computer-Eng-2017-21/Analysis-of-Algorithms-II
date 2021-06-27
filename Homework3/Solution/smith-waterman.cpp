/*  
    @author: Barış İncesu
    @ID: 150170092
    @date :14.05.2021

    Compile: g++ -std=c++11 -Wall -Werror 150170092.cpp -o 150170092
    Run: ./150170092
    Calico: python -m calico.cli <testFileName>.t inputFileName outputFileName match mismatch gap
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <bits/stdc++.h>

using namespace std;
// Function for max value
int max(int a, int b, int c, int d)
{
    int maxValue = a;

    if (b > maxValue)
    {
        maxValue = b;
    }
    if (c > maxValue)
    {
        maxValue = c;
    }
    if (d > maxValue)
    {
        maxValue = d;
    }

    return maxValue;
}
// compare letters for match or mismatch
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

int main(int argc, char **argv)
{
    string inputFileName = argv[1];
    string outpuFileName = argv[2];
    //cin >> filename;

    int match = stoi(argv[3]);
    int mismatch = stoi(argv[4]);
    int gap = stoi(argv[5]);

    //filename = "strings.txt";

    ifstream file1;
    file1.open(inputFileName);

    if (!file1)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string word;
    vector<string> v1;

    while (!file1.eof())
    {
        file1 >> word;
        v1.push_back(word);
    }

    sort(v1.begin(), v1.end()); // sort for alphabetical order
    string s1 = "ABCTABS";
    string s2 = "ABCDABS";

    //string fileName = "150170092_result.txt";

    for (unsigned int i = 0; i < v1.size(); i++)
    {
        for (unsigned int j = i + 1; j < v1.size(); j++)
        {
            ofstream myfile;
            // std::ios::app is the open mode "append" meaning
            // new data will be written to the end of the file.
            myfile.open(outpuFileName, ios::out | ios::app);
            s1 = v1.at(i);
            s2 = v1.at(j);
            //sw(s1, s2, fileName);

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

            for (int row = 1; row < lengthOfs1 + 1; row++)
            {
                for (int column = 1; column < lengthOfs2 + 1; column++)
                {
                    int left_down = scoreMatrix[row][column - 1] + gap;
                    int right_up = scoreMatrix[row - 1][column] + gap;
                    int diag = scoreMatrix[row - 1][column - 1];

                    if (compare(row, column, s1, s2))
                    {
                        diag += match;
                        //scoreMatrix[row][column] = diag;
                    }
                    else
                    {
                        diag += mismatch;
                        //scoreMatrix[row][column] = diag;
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
                    }*/
                    int indel = max(left_down, right_up, diag, 0);
                    scoreMatrix[row][column] = indel;
                }
            }

            int maximumNumberInMatrix = 0;

            for (int i = 0; i < lengthOfs1 + 1; i++)
            {
                for (int j = 0; j < lengthOfs2 + 1; j++)
                {
                    if (scoreMatrix[i][j] > maximumNumberInMatrix)
                    {
                        maximumNumberInMatrix = scoreMatrix[i][j];
                    }
                }
            }
            int target_number = 0;
            for (int i = 0; i < lengthOfs1 + 1; i++)
            {
                for (int j = 0; j < lengthOfs2 + 1; j++)
                {
                    if (scoreMatrix[i][j] == maximumNumberInMatrix)
                    {
                        target_number++;
                    }
                }
            }

            int target_length = 0;
            int password[target_number];
            for (int i = 0; i < target_number; i++)
            {
                password[i] = 0;
            }

            int positions[target_number];
            int offset = 0;

            for (int i = 0; i < lengthOfs1 + 1; i++)
            {
                for (int j = 0; j < lengthOfs2 + 1; j++)
                {
                    if (scoreMatrix[i][j] == maximumNumberInMatrix)
                    {
                        int targeti = i;
                        int targetj = j;
                        while (targeti >= 1 && targetj >= 1 && scoreMatrix[targeti][targetj] != 0)
                        {
                            targeti = targeti - 1;
                            targetj = targetj - 1;
                            target_length++;
                            password[offset] = password[offset] + 1;
                        }
                        positions[offset] = i;
                        offset++;
                    }
                }
            }

            if (myfile.is_open())
            {
                myfile << s1 << " - " << s2 << "\n";
                cout << s1 << " - " << s2 << endl;

                myfile << "Score: " << maximumNumberInMatrix << " Sequence(s):";
                cout << "Score: " << maximumNumberInMatrix << " Sequence(s): ";

                if (target_length > 0)
                {
                    set<string> outputvector;

                    for (int i = 0; i < target_number; i++)
                    {

                        int end = positions[i] - 1;
                        int start = end - password[i] + 1;
                        if (start < 0)
                        {
                            start = 0;
                        }

                        string outputx = s1.substr(start, password[i]);
                        //cout << positions[i] << endl;
                        //cout << "target: " << outputx << endl;
                        outputvector.insert(outputx);
                    }
                    //sort(outputvector.begin(), outputvector.end());
                    for (auto i = outputvector.begin(); i != outputvector.end(); ++i)
                    {
                        myfile << " "
                               << "\"" << *i << "\"";
                        cout << "\"" << *i << "\""
                             << " ";
                    }
                }
                cout << endl;
                myfile << "\n";
                myfile.close();
            }
        }
    }
}