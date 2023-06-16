#include<stdio.h>
#include<iostream>
#include<fstream>

using namespace std;
class Node
{
private:
    int n;
    int cost_from_source;
    int total_cost;
    int **grid;
    Node *parent;

public:
    Node(int n);
    ~Node();
    void setNodeValues(int **grid);
    int **getNodeValues();
    int getCostFromSource();
    int getTotalCost();
    Node *getParent();
    void setCostFromSource(int cost);
    void setTotalCost(int cost);
    void setParent(Node *parent);
    void setN(int n);
    int getN();
    void printNode( fstream &output);

    Node(const Node &a)
    {
        this->n = a.n;
        this->cost_from_source = a.cost_from_source;
        this->total_cost = a.total_cost;
        this->grid = new int *[n];
        for (int i = 0; i < n; i++)
        {
            this->grid[i] = new int[n];
        }
        this->parent = a.parent;
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->n; j++)
            {
                this->grid[i][j] = a.grid[i][j];
            }
        }
    }
};

Node::Node(int n)
{
    this->n = n;
    this->cost_from_source = 0;
    this->total_cost = 0;
    this->grid = new int *[n];
    for (int i = 0; i < n; i++)
    {
        this->grid[i] = new int[n];
    }
    this->parent = nullptr;
}

Node::~Node()
{
    for (int i = 0; i < n; i++)
    {
        delete[] this->grid[i];
    }
    delete[] this->grid;
}

void Node::setNodeValues(int **grid)
{
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            this->grid[i][j] = grid[i][j];
        }
    }
    // this->printNode();
}
int **Node::getNodeValues()
{
    return this->grid;
}
int Node::getCostFromSource()
{
    return this->cost_from_source;
}
int Node::getTotalCost()
{
    return this->total_cost;
}
Node *Node::getParent()
{
    return this->parent;
}
void Node::setCostFromSource(int cost)
{
    this->cost_from_source = cost;
}
void Node::setTotalCost(int cost)
{
    this->total_cost = cost;
}
void Node::setParent(Node *parent)
{
    this->parent = parent;
}
void Node::setN(int n)
{
    this->n = n;
}
int Node::getN()
{
    return this->n;
}
void Node::printNode( fstream &output )
{
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        output<<grid[i][j]<<" ";
    }
    output<<endl;
}
}