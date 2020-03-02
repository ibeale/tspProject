#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <climits>
#include <time.h>

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
        this->allCities = allCities;
        for(int i = 0; i < allCities.size(); i++){
            vector<int> node;
            this->children.push_back(node);
        }
        int dist;
        vector<int> line;
        for (int i = 0; i < allCities.size(); i++)
        {
            for (int j = 0; j < allCities.size(); j++)
            {
                dist = calcDist(allCities[i], allCities[j]);
                line.push_back(dist);
            }
            this->adjMatrix.push_back(line);
            line.clear();
        }
    }


    // Source: https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
    void createMST(){
        int dimension = this->adjMatrix.size();
        
        int parents[dimension];
        this->parents = parents;
        int mstSet[dimension];

        for(int i = 0; i < dimension; i++){
            this->keys.push_back(INT_MAX);
            mstSet[i] = 0;
        }

        //Start in a random place
        int index = rand() % dimension;
        printf("Starting at node %d\n", index);
        this->keys[index] = 0;
        parents[index] = -1;
        this->mstRootIndex = index;


        for(int count = 0; count < dimension - 1; count++){
            int u = minKey(this->keys, mstSet);
            mstSet[u] = 1;
            for(int i = 0; i < dimension; i++){
                if (this->adjMatrix[u][i] && mstSet[i] == 0 && this->adjMatrix[u][i] < this->keys[i]){
                    parents[i] = u;
                    this->keys[i] = this->adjMatrix[u][i];
                }
            }
        }


        for(int i = 0; i < dimension; i++){
            if(this->parents[i] != -1){
                int j = 0;
                if(this->children[this->parents[i]].size() > 0){
                    while(j < this->children[this->parents[i]].size()){
                        if(this->adjMatrix[i][parents[i]] > this->adjMatrix[this->children[this->parents[i]][j]][this->parents[i]]){
                            j++;
                        }
                        else{
                            break;
                        }
                    }
                    this->children[parents[i]].insert(this->children[parents[i]].begin() + j, i);
                }
                else{
                    this->children[parents[i]].push_back(i);
                }

            }
        }
        for(int i = 0; i < dimension; i++){
            printf("Node: %d, Parent: %d\n", i, this->parents[i]);
            for(int j = 0; j < this->children[i].size(); j++){
                printf("\tChild: %d\n", this->children[i][j]);
            }
        }


    }
    void FinalTSPSolution(){
        createTSPPath(this->mstRootIndex);
        int totalDist = 0;
        int i = 1;
        for(i; i < this->tspPath.size(); i++){
            totalDist += this->adjMatrix[this->tspPath[i-1]][this->tspPath[i]];
        }
        totalDist += this->adjMatrix[this->tspPath[i-1]][this->tspPath[0]];
        ofstream outfile;
        outfile.open("output.txt");
        outfile << totalDist << endl;
        for(int i = 0; i < this->tspPath.size(); i++){
            outfile << this->tspPath[i] << endl;
        }
    }



private:
    vector<vector<int> > adjMatrix;
    vector<City> allCities;
    int* parents;
    vector<int> keys;
    vector<vector<int> > children;
    vector<int> tsp_solution;
    int mstRootIndex;
    vector<int> tspPath;

    int calcDist(City city1, City city2){
        return round(sqrt(pow(city1.x - city2.x, 2) + pow(city1.y - city2.y, 2)));
    }

    int minKey(vector<int> key, int mstSet[]){
        int dimension = key.size();
        int min = INT_MAX, min_index;
        for(int i = 0; i < dimension; i++){
            if (mstSet[i] == 0 && key[i] < min){
                min = key[i], min_index = i;
            }
        }
        return min_index;

    }
    void createTSPPath(int node){
        this->tspPath.push_back(node);
        for(int i = 0; i < this->children[node].size(); i++){
            createTSPPath(this->children[node][i]);
        }
    }


};

vector<City> getCityFromFile(const char *filename)
{
    int x;
    int y;
    int index;
    vector<City> allCities;
    ifstream inputFile;
    inputFile.open(filename);
    while (inputFile >> index)
    {
        inputFile >> x;
        inputFile >> y;
        allCities.push_back(City(x, y, index));
    }
    inputFile.close();
    for (int i = 0; i < allCities.size(); i++)
    {
        printf("x: %d y: %d, index: %d\n", allCities[i].x, allCities[i].y, allCities[i].index);
    }
    return allCities;
}

int main(int argc, char** argv)
{
    if(argc != 1){
        printf("Too many arguments given. Please only specify input file location");
    }
    srand(time(NULL));
    vector<City> allCities = getCityFromFile(argv[1]);
    Graph graph_1(allCities);
    graph_1.createMST();
    graph_1.FinalTSPSolution();
}