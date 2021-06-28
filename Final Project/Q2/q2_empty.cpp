#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point
{
    int xCoordinate;
    int yCoordinate;
};

class PointSpace
{
    int numberOfPoints;
    vector<Point> points;

public:
    void setNumberOfPoints(int n)
    {
        numberOfPoints = n;
    }

    int getNumberOfPoints()
    {
        return numberOfPoints;
    }

    void addPoint(int x, int y)
    {
        Point p = Point();
        p.xCoordinate = x;
        p.yCoordinate = y;

        points.push_back(p);
    }

    void printNumberOfPoints()
    {
        cout << "Total number of points: " << getNumberOfPoints() << endl;
    }

    void printAllPoints()
    {
        cout << "Points coordinates (x y): " << endl;

        for (std::vector<Point>::const_iterator i = points.begin(); i != points.end(); ++i)
        {
            cout << i->xCoordinate << "\t" << i->yCoordinate << endl;
        }
    }

    void selectionSortX(vector<Point> &arr, int n)
    {
        int i, j, min_idx;

        // One by one move boundary of unsorted subarray
        for (i = 0; i < n - 1; i++)
        {
            // Find the minimum element in unsorted array
            min_idx = i;
            for (j = i + 1; j < n; j++)
                if (arr[j].xCoordinate < arr[min_idx].xCoordinate)
                    min_idx = j;

            // Swap the found minimum element with the first element
            swap(arr[min_idx], arr[i]);
        }
    }

    void selectionSortY(vector<Point> &arr, int n)
    {
        int i, j, min_idx;

        // One by one move boundary of unsorted subarray
        for (i = 0; i < n - 1; i++)
        {
            // Find the minimum element in unsorted array
            min_idx = i;
            for (j = i + 1; j < n; j++)
                if (arr[j].yCoordinate < arr[min_idx].yCoordinate)
                    min_idx = j;

            // Swap the found minimum element with the first element
            swap(arr[min_idx], arr[i]);
        }
    }

    double FindClosestPairDistance()
    {
        selectionSortX(points, points.size());
        //X e göre sırala//

        // Use recursive function closestUtil()
        // to find the smallest distance
        return closestUtil(points, points.size());
    }

    float closestUtil(vector<Point> P, int n)
    {
        // If there are 2 or 3 points, then use brute force
        if (n <= 3)
            return bruteForce(P, n);

        // Find the middle point
        int mid = n / 2;
        Point midPoint = P[mid];

        // Consider the vertical line passing
        // through the middle point calculate
        // the smallest distance dl on left
        // of middle point and dr on right side
        float dl = closestUtil(P, mid);

        vector<Point> pr;
        for (int i = mid; i < P.size(); i++)
        {
            pr.push_back(P[i]);
        }

        float dr = closestUtil(pr, n - mid);

        // Find the smaller of two distances
        float d = min(dl, dr);

        // Build an array strip[] that contains
        // points close (closer than d)
        // to the line passing through the middle point
        vector<Point> strip;
        int j = 0;
        for (int i = 0; i < n; i++)
            if (abs(P[i].xCoordinate - midPoint.xCoordinate) < d)
                strip.push_back(P[i]), j++;

        // Find the closest points in strip.
        // Return the minimum of d and closest
        // distance is strip[]
        return min(d, stripClosest(strip, j, d));
    }

    float stripClosest(vector<Point> strip, int size, float d)
    {
        float min = d; // Initialize the minimum distance as d

        selectionSortY(strip, strip.size());

        // Pick all points one by one and try the next points till the difference
        // between y coordinates is smaller than d.
        // This is a proven fact that this loop runs at most 6 times
        for (int i = 0; i < size; ++i)
            for (int j = i + 1; j < size && (strip[j].yCoordinate - strip[i].yCoordinate) < min; ++j)
                if (dist(strip[i], strip[j]) < min)
                    min = dist(strip[i], strip[j]);

        return min;
    }
    // A utility function to find the
    // distance between two points
    float dist(Point p1, Point p2)
    {
        return sqrt((p1.xCoordinate - p2.xCoordinate) * (p1.xCoordinate - p2.xCoordinate) + (p1.yCoordinate - p2.yCoordinate) * (p1.yCoordinate - p2.yCoordinate));
    }

    // A Brute Force method to return the
    // smallest distance between two points
    // in P[] of size n
    float bruteForce(vector<Point> P, int n)
    {
        float min = 9999999;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (dist(P[i], P[j]) < min)
                    min = dist(P[i], P[j]);
        return min;
    }

    // A utility function to find
    // minimum of two float values
    float min(float x, float y)
    {
        return (x < y) ? x : y;
    }

    //int compareX
};

int main(int argc, char *argv[])
{
    //define a point space
    PointSpace pointSpace;

    //get file name
    string inputFileName = "D:/Code/VS Code-Projects/Analysis-of-Algorithms-II/Final Project/Q2/points20.txt";

    string line;
    ifstream infile(inputFileName);

    //read the number of total points (first line)
    getline(infile, line);
    pointSpace.setNumberOfPoints(stoi(line));

    //read points' coordinates and assign each point to the space (second to last line)
    int x, y;
    while (infile >> x >> y)
    {
        pointSpace.addPoint(x, y);
    }

    //print details of point space (not necessary for assignment evaluation: calico will not check this part)
    pointSpace.printAllPoints();
    pointSpace.printNumberOfPoints();

    //find and print the distance between closest pair of points (calico will check this part)
    double closestDistance = pointSpace.FindClosestPairDistance();
    cout << "Distance between the closest points: " << closestDistance << endl;

    return 0;
}
