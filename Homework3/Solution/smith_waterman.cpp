#include <iostream>
#include <string>
#include <fstream>

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
    if (s1.at(i - 1) == s2.at(j - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    string s1 = "ABCTABS";
    string s2 = "ABCDABS";

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
            int left_down = scoreMatrix[row][column - 1] - 2;
            int right_up = scoreMatrix[row - 1][column] - 2;
            int diag = scoreMatrix[row - 1][column - 1];

            if (compare(row, column, s1, s2))
            {
                diag = diag + 1;
            }
            else
            {
                diag = diag - 10;
            }

            if (left_down < 0)
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
            scoreMatrix[row][column] = indel;
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

    //scoreMatrix[2][3] = 111;

    for (int i = 0; i < lengthOfs1 + 1; i++)
    {
        for (int j = 0; j < lengthOfs2 + 1; j++)
        {
            cout << scoreMatrix[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Target Length = " << target_length << " Target Number = " << target_number << endl;

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

    cout << "s1 = " << s1 << " s2 = " << s2 << endl;

    for (int i = 0; i < target_number; i++)
    {
        string output = s2.substr(positions[i] - target_length, positions[i]);
        cout << "target: " << output << endl;
    }
    // information_tunction_yesişim1_esişim2_kesişim3
    cout << "Hello World!" << endl;

}