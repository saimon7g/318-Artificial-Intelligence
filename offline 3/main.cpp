#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;

void GreedyConstruction(int **graph, int vertex, vector<int> *set1, vector<int> *set2, float alpha);
int CalculateMaxCut(int **graph, int vertex, vector<int> *set1, vector<int> *set2);
int LocalSearch(int **graph, int vertex, vector<int> *set1, vector<int> *set2, int *numOfIterationsForLocalSearch);
int GRASP(int **graph, int vertex,vector<int> *set1, vector<int> *set2, int numOfIterationsForGRASP);
void PrintSet(vector<int> *set1);

struct edge
{
    int u;
    int v;
    int weight;
};

int main(int argc, char *argv[])
{

    // take input file name from command line
    char *input_file_name = argv[1];
    char *output_file_name = argv[2];

    // open input file from a different directory
    FILE *fp = fopen(input_file_name, "r");

    if (fp == NULL)
    {
        cout << "File not found" << endl;
        exit(0);
    }

    // read the input file
    int vertex, edge;
    float alpha = 0.2;
    int numOfIterationsForGRASP = 40;

    fscanf(fp, "%d %d", &vertex, &edge);
    alpha = atof(argv[3]);
    numOfIterationsForGRASP = atoi(argv[4]);

    cout<<input_file_name<<"            "<<alpha<<"                  "<<numOfIterationsForGRASP<<endl;


    cout <<" Vertex  : " <<vertex << "                           edgwe:   " << edge << endl;

    // create a 2D array to store the graph
    int **graph = new int *[vertex];
    for (int i = 0; i < vertex; i++)
    {
        graph[i] = new int[vertex];
    }
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            graph[i][j] = 0;
        }
    }

    // read the graph from the input file
    int u, v, weight;
    for (int i = 0; i < edge; i++)
    {
        fscanf(fp, "%d %d %d", &u, &v, &weight);
        graph[u - 1][v - 1] = weight;
        graph[v - 1][u - 1] = weight;
    }

    // greedy construction

    vector<int> *greedySetA = new vector<int>;
    vector<int> *greedySetB = new vector<int>;
    GreedyConstruction(graph, vertex, greedySetA, greedySetB, 1);
    int maxcutForGreedy = CalculateMaxCut(graph, vertex, greedySetA, greedySetB);

    // randomized construction

    vector<int> *randomizedSetA = new vector<int>;
    vector<int> *randomizedSetB = new vector<int>;
    int sumOfMaxcut = 0;
    for(int i=0;i<10;i++){
        GreedyConstruction(graph, vertex, randomizedSetA, randomizedSetB, 0);
        sumOfMaxcut += CalculateMaxCut(graph, vertex, randomizedSetA, randomizedSetB);
        randomizedSetA->clear();
        randomizedSetB->clear();
    }
    int maxcutForRandomized = sumOfMaxcut/10;

    // semi-greedy construction

    vector<int> *semiGreedySetA = new vector<int>;
    vector<int> *semiGreedySetB = new vector<int>;
    sumOfMaxcut = 0;
    for(int i=0;i<10;i++){
        GreedyConstruction(graph, vertex, semiGreedySetA, semiGreedySetB, alpha);
        sumOfMaxcut += CalculateMaxCut(graph, vertex, semiGreedySetA, semiGreedySetB);
        semiGreedySetA->clear();
        semiGreedySetB->clear();
    }
    int maxcutForSemiGreedy = sumOfMaxcut/10;

    GreedyConstruction(graph, vertex, randomizedSetA, randomizedSetB, 0);


    // PrintSet(greedySetA);
    // PrintSet(greedySetB);
    // PrintSet(randomizedSetA);
    // PrintSet(randomizedSetB);
    // PrintSet(semiGreedySetA);
    // PrintSet(semiGreedySetB);

    int* numOfIterationsForLocalSearch= new int;
    *numOfIterationsForLocalSearch = 0;
    int maxcutForLocalSearch = LocalSearch(graph, vertex,randomizedSetA, randomizedSetB, numOfIterationsForLocalSearch);

    vector<int> *set1ForGRASP = new vector<int>;
    vector<int> *set2ForGRASP = new vector<int>;
    int maxcutForGRASP = GRASP(graph, vertex,set1ForGRASP, set2ForGRASP, numOfIterationsForGRASP);

    ofstream myfile(output_file_name, std::ios_base::app);
    if (myfile.is_open())
    {
        myfile<<input_file_name<<","<<vertex<<","<<edge<<","<<alpha<<","<<maxcutForRandomized<<","<<maxcutForGreedy<<","<<maxcutForSemiGreedy<<","<<*numOfIterationsForLocalSearch<<","<<maxcutForLocalSearch<<","<<numOfIterationsForGRASP<<","<<maxcutForGRASP<<endl;
        
    }
    else
    {
        cout << "Unable to open file";
    }

    // close the file
    fclose(fp);
    myfile.close();
    //clear pointers
    greedySetA->clear();
    greedySetB->clear();
    randomizedSetA->clear();
    randomizedSetB->clear();
    semiGreedySetA->clear();
    semiGreedySetB->clear();
    set1ForGRASP->clear();
    set2ForGRASP->clear();
    delete greedySetA;
    delete greedySetB;
    delete randomizedSetA;
    delete randomizedSetB;
    delete semiGreedySetA;
    delete semiGreedySetB;
    delete set1ForGRASP;
    delete set2ForGRASP;

    // clear graph
    for (int i = 0; i < vertex; i++)
    {
        delete[] graph[i];
    }
    delete[] graph;
    return 0;
}

void GreedyConstruction(int **graph, int vertex, vector<int> *set1, vector<int> *set2, float alpha)
{

    // cout << "Greedy Construction" << endl;

    int max_weight = -100000;
    int min_weight = 1000000;

    for (int i = 0; i < vertex; i++)
    {
        for (int j = i; j < vertex; j++)
        {
            if (graph[i][j] > max_weight)
            {
                max_weight = graph[i][j];
            }
            if (graph[i][j] < min_weight)
            {
                min_weight = graph[i][j];
            }
        }
    }

    int mew = min_weight + alpha * (max_weight - min_weight);

    vector<edge> *edges = new vector<edge>;

   
    for (int i = 0; i < vertex; i++)
    {
        for (int j = i ; j < vertex; j++)
        {
            if (graph[i][j] >= mew)
            {
                edge e;
                e.u = i;
                e.v = j;
                e.weight = graph[i][j];
                edges->push_back(e);
            }
        }
    }


    // random number with range 0 to edges->size()-1
    int random = rand() % edges->size();
    int max_u = edges->at(random).u;
    int max_v = edges->at(random).v;

    set1->push_back(max_u);
    set2->push_back(max_v);

    set<int> *already_taken = new set<int>;
    edges->clear();

    // need correction
    already_taken->insert(max_u);
    already_taken->insert(max_v);


    for (int i = 0; i < vertex; i++)
    {
        edges->clear();
        // cout << i << " "<<endl;
        if (already_taken->find(i) != already_taken->end())
        {
            continue;
        }

        int max_inside1 = 0;
        int max_inside2 = 0;


        for (int j = 0; j < set1->size(); j++)
        {
            max_inside2 += graph[i][set1->at(j)];
        }
        for (int j = 0; j < set2->size(); j++)
        {
            max_inside1 += graph[i][set2->at(j)];
        }
        if (max_inside1 > max_inside2)
        {
            edge e;
            e.u = i;
            e.v = 1;
            e.weight = max_inside1;
            edges->push_back(e);
        }
        else
        {
            edge e;
            e.u = i;
            e.v = 2;
            e.weight = max_inside2;
            edges->push_back(e);
        }
        max_weight = -100000;
        min_weight = 1000000;

        for (int i = 0; i < edges->size(); i++)
        {
            if (edges->at(i).weight > max_weight)
            {
                max_weight = edges->at(i).weight;
            }
            if (edges->at(i).weight < min_weight)
            {
                min_weight = edges->at(i).weight;
            }
        }
        mew = min_weight + alpha * (max_weight - min_weight);
        vector<edge> *RCL = new vector<edge>;

        for (int i = 0; i < edges->size(); i++)
        {
            if (edges->at(i).weight >= mew)
            {
                RCL->push_back(edges->at(i));
            }
        }

        random = rand() % RCL->size();
        max_u = RCL->at(random).u;
        max_v = RCL->at(random).v;

        if (max_v == 1)
        {
            set1->push_back(max_u);
        }
        else
        {
            set2->push_back(max_u);
        }

        already_taken->insert(max_u);

        RCL->clear();
        delete RCL;

    }

    int maxcut = CalculateMaxCut(graph, vertex, set1, set2);
    // cout << "Maxcut: " << maxcut << endl;
    edges->clear();
    already_taken->clear();
    delete edges;
    delete already_taken;

    return void();
}

int CalculateMaxCut(int **graph, int vertex, vector<int> *set1, vector<int> *set2)
{
    int maxcut = 0;
    for (int i = 0; i < set1->size(); i++)
    {
        for (int j = 0; j < set2->size(); j++)
        {
            maxcut += graph[set1->at(i)][set2->at(j)];
        }
    }
    return maxcut;
}

void PrintSet(vector<int> *set1)
{
    cout << endl; 
    for (int i = 0; i < set1->size(); i++)
    {
        cout << set1->at(i) << " ";
    }
    cout << endl;
}

int LocalSearch(int **graph, int vertex, vector<int> *set1, vector<int> *set2, int *numOfIterationsForLocalSearch)
{
    bool improved = true;
    int count = 0;
    int maxcut = CalculateMaxCut(graph, vertex, set1, set2);
    while (improved)
    {
        improved = false;
        count++;

        for (int i = 0; i < vertex; i++)
        {
            int weight_when_i_in_set1 = 0;
            int weight_when_i_in_set2 = 0;
            for (int j = 0; j < set2->size(); j++)
            {
                weight_when_i_in_set1 += graph[i][set2->at(j)];
            }
            for (int j = 0; j < set1->size(); j++)
            {
                weight_when_i_in_set2 += graph[i][set1->at(j)];
            }
            auto it = find(set1->begin(), set1->end(), i);
            // cout<< i<< "            "<<*it<<endl;
            if (it != set1->end() && weight_when_i_in_set1 < weight_when_i_in_set2)
            {
                set2->push_back(i);
                set1->erase(it);
                improved = true;
                break;
            }
            it = find(set2->begin(), set2->end(), i);
            if (it != set2->end() && weight_when_i_in_set2 < weight_when_i_in_set1)
            {
                set1->push_back(i);
                set2->erase(it);
                improved = true;
                break;
            }
        }
        // cout << "Iteration: " << count << endl;
    }
    *numOfIterationsForLocalSearch = count;
    return CalculateMaxCut(graph, vertex, set1, set2);
}

int GRASP(int **graph, int vertex, vector<int> *set1, vector<int> *set2, int numOfIterationsForGRASP)
{
    int maxcut = 0;
    set1->clear();
    set2->clear();

    for (int i = 0; i < numOfIterationsForGRASP; i++)
    {
        vector<int> *set1_temp = new vector<int>;
        vector<int> *set2_temp = new vector<int>;
        int *numOfIterationsForLocalSearch = new int;
        *numOfIterationsForLocalSearch = 0;
        GreedyConstruction(graph, vertex, set1_temp, set2_temp, 0);
        LocalSearch(graph, vertex, set1_temp, set2_temp, numOfIterationsForLocalSearch);
        if(i==0){
            maxcut = CalculateMaxCut(graph, vertex, set1_temp, set2_temp);
            for(int j=0;j<set1_temp->size();j++){
                set1->push_back(set1_temp->at(j));
            }
            for(int j=0;j<set2_temp->size();j++){
                set2->push_back(set2_temp->at(j));
            }
        }
        else if(CalculateMaxCut(graph, vertex, set1_temp, set2_temp)>maxcut){
            maxcut = CalculateMaxCut(graph, vertex, set1_temp, set2_temp);
            set1->clear();
            set2->clear();
            for(int j=0;j<set1_temp->size();j++){
                set1->push_back(set1_temp->at(j));
            }
            for(int j=0;j<set2_temp->size();j++){
                set2->push_back(set2_temp->at(j));
            }
        }
        set1_temp->clear();
        set2_temp->clear();
        delete set1_temp;
        delete set2_temp;
    }

    return maxcut;
}
