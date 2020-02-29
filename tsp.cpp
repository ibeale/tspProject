#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

struct City
{
    int x;
    int y;
    int index;

    City(int x, int y, int index)
    {
        this->x = x;
        this->y = y;
        this->index = index;
    }
};

class Graph
{
public:
    Graph(vector<City> allCities)
    {
        int dist;
        for (int i = 0; i < allCities.size(); i++)
        {
            for (int j = 0; j < allCities.size(); j++)
            {
                dist = round(sqrt(pow(allCities[i].x - allCities[j].x, 2) + pow(allCities[i].y - allCities[j].y, 2)));
                this->adjMatrix[i][j] = dist;
            }
        }
        for (int i = 0; i < this->adjMatrix.size(); i++)
        {
            for (int j = 0; j < this->adjMatrix.size(); i++)
            {
                printf("%d", this->adjMatrix[i][j]);
            }
        }
    }

private:
    vector<vector<int>> adjMatrix;
};

vector<City>
getCityFromFile(const char *filename)
{
    int x;
    int y;
    int index;
    vector<City> allCities;
    ifstream inputFile;
    inputFile.open(filename);
    while (!inputFile.eof())
    {
        inputFile >> x;
        inputFile >> y;
        inputFile >> index;
        allCities.push_back(City(x, y, index));
    }
    for (int i = 0; i < allCities.size(); i++)
    {
        printf("x: %d y: %d, index: %d\n", allCities[i].x, allCities[i].y, allCities[i].index);
    }
    return allCities;
}

int main()
{
    vector<City> allCities = getCityFromFile("tsp_test_casesW20/tsp_test_cases/test-input-1.txt");
    Graph graph(allCities);
}