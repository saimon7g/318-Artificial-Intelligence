#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Node.cpp"
#include <queue>

using namespace std;

class ComapareClass
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->getTotalCost() > b->getTotalCost();
    }
};

int getInversionNumber(int **grid, int n);
int hammingDistance(int **grid, int n);
int manhattanDistance(int **grid, int n);
bool compareNodes(Node *a, Node *b);
Node *moveRight(Node *node);
Node *moveLeft(Node *node);
Node *moveUp(Node *node);
Node *moveDown(Node *node);
bool compareFunction(Node *a, Node *b);
void printPath(Node *node, fstream &output);

int main()
{

    fstream input;
    fstream output;
    input.open("input.txt", ios::in);
    output.open("output.txt", ios::out);
    int n, blank_row, blank_column;

    input >> n;
    int **grid = new int *[n];
    for (int i = 0; i < n; i++)
    {
        grid[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            input >> grid[i][j];
            if (grid[i][j] == 0)
            {
                blank_row = i;
                blank_column = j;
            }
        }
    }

    int inversion_number = getInversionNumber(grid, n);

    // cout << "inversion_number: " << inversion_number << endl;
    // int hamming_distance = hammingDistance(grid, n);
    // int manhattan_distance = manhattanDistance(grid, n);

    if (n % 2 == 1 && inversion_number % 2 == 1)
    {
        output << "Unsolvable puzzle" << endl;
        output << inversion_number << endl;
        input.close();
        output.close();
        return 0;
    }
    else if (n % 2 == 0 && (inversion_number + (n - 1 - blank_row)) % 2 == 1)
    {
        output << "Unsolvable puzzle" << endl;
        output << inversion_number << endl;
        input.close();
        output.close();
        return 0;
    }

    Node *start_node = new Node(n);
    start_node->setNodeValues(grid);
    start_node->setCostFromSource(0);
    start_node->setParent(nullptr);

    priority_queue<Node *, vector<Node *>, ComapareClass> pq;

    Node *target_node = new Node(n);
    target_node->setCostFromSource(0);
    target_node->setParent(nullptr);
    target_node->setTotalCost(0);
    int **target_grid = new int *[n];
    for (int i = 0; i < n; i++)
    {
        target_grid[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            target_grid[i][j] = (i * n) + j + 1;
        }
    }
    target_grid[n - 1][n - 1] = 0;
    target_node->setNodeValues(target_grid);

    int type = 1;
    // can take input if needed
    int number_of_nodes = 0;
    int number_of_explored_nodes = 0;

    if (type == 1)
    {
        start_node->setTotalCost(hammingDistance(grid, n));
        pq.push(start_node);
        Node *end_node = nullptr;
        Node *current_node = nullptr;
        while (true)
        {
            current_node = pq.top();
            pq.pop();
            if (compareNodes(current_node, target_node))
            {
                end_node = current_node;
                break;
            }
            else
            {
                Node *right_node = moveRight(current_node);
                Node *left_node = moveLeft(current_node);
                Node *up_node = moveUp(current_node);
                Node *down_node = moveDown(current_node);
                if (right_node != nullptr && !compareNodes(right_node, current_node->getParent()))
                {
                    right_node->setTotalCost(hammingDistance(right_node->getNodeValues(), n) + right_node->getCostFromSource());
                    pq.push(right_node);
                    number_of_explored_nodes++;
                }
                if (left_node != nullptr && !compareNodes(left_node, current_node->getParent()))
                {
                    left_node->setTotalCost(hammingDistance(left_node->getNodeValues(), n) + left_node->getCostFromSource());
                    pq.push(left_node);
                    number_of_explored_nodes++;
                }
                if (up_node != nullptr && !compareNodes(up_node, current_node->getParent()))
                {
                    up_node->setTotalCost(hammingDistance(up_node->getNodeValues(), n) + up_node->getCostFromSource());
                    pq.push(up_node);
                    number_of_explored_nodes++;
                }
                if (down_node != nullptr && !compareNodes(down_node, current_node->getParent()))
                {
                    down_node->setTotalCost(hammingDistance(down_node->getNodeValues(), n) + down_node->getCostFromSource());
                    pq.push(down_node);
                    number_of_explored_nodes++;
                }
            }
        }
        Node *temp = end_node;
        while (temp != nullptr)
        {
            number_of_nodes++;
            temp = temp->getParent();
        }
        number_of_nodes--;

        output << "Minimum number of moves =" << number_of_nodes << endl;
        output << "Number of Explored Nodes:  " << number_of_explored_nodes << endl;

        printPath(end_node, output);
    }
    else if (type == 2)
    {
        start_node->setTotalCost(manhattanDistance(grid, n));
        pq.push(start_node);
        Node *end_node = nullptr;
        Node *current_node = nullptr;
        while (true)
        {
            current_node = pq.top();
            pq.pop();
            if (compareNodes(current_node, target_node))
            {
                end_node = current_node;
                break;
            }
            else
            {
                Node *right_node = moveRight(current_node);
                Node *left_node = moveLeft(current_node);
                Node *up_node = moveUp(current_node);
                Node *down_node = moveDown(current_node);
                if (right_node != nullptr && !compareNodes(right_node, current_node->getParent()))
                {
                    right_node->setTotalCost(manhattanDistance(right_node->getNodeValues(), n) + right_node->getCostFromSource());
                    pq.push(right_node);
                    number_of_explored_nodes++;
                }
                if (left_node != nullptr && !compareNodes(left_node, current_node->getParent()))
                {
                    left_node->setTotalCost(manhattanDistance(left_node->getNodeValues(), n) + left_node->getCostFromSource());
                    pq.push(left_node);
                    number_of_explored_nodes++;
                }
                if (up_node != nullptr && !compareNodes(up_node, current_node->getParent()))
                {
                    up_node->setTotalCost(manhattanDistance(up_node->getNodeValues(), n) + up_node->getCostFromSource());
                    pq.push(up_node);
                    number_of_explored_nodes++;
                }
                if (down_node != nullptr && !compareNodes(down_node, current_node->getParent()))
                {
                    down_node->setTotalCost(manhattanDistance(down_node->getNodeValues(), n) + down_node->getCostFromSource());
                    pq.push(down_node);
                    number_of_explored_nodes++;
                }
            }
        }

        Node *temp = end_node;
        while (temp != nullptr)
        {
            number_of_nodes++;
            temp = temp->getParent();
        }
        number_of_nodes--;

        output << "Minimum number of moves =" << number_of_nodes << endl;
        output << "Number of Explored Nodes:  " << number_of_explored_nodes << endl;

        printPath(end_node, output);
    }

    input.close();
    output.close();
    return 0;
}

int getInversionNumber(int **grid, int n)
{
    int inversion_number = 0;
    int grid_array[n * n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            grid_array[(i * n) + j] = grid[i][j];
        }
    }
    for (int i = 0; i < n * n; i++)
    {
        for (int j = i + 1; j < n * n; j++)
        {
            if (grid_array[i] > grid_array[j] && grid_array[i] != 0 && grid_array[j] != 0)
            {
                inversion_number++;
            }
        }
    }
    return inversion_number;
}
int hammingDistance(int **grid, int n)
{
    int hamming_distance = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] != (i * n) + (j + 1))
            {
                hamming_distance++;
            }
        }
    }
    hamming_distance--;
    // cout << "hamming_distance: " << hamming_distance << endl;
    return hamming_distance;
}
int manhattanDistance(int **grid, int n)
{
    int manhattan_distance = 0;
    int num, rowdis, coldis;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            num = grid[i][j];
            if (num != 0)
            {
                rowdis = abs((num - 1) / n - i);
                coldis = abs((num - 1) % n - j);
                manhattan_distance += rowdis + coldis;
            }
        }
    }
    // cout << "manhattondistance: " << manhattan_distance << endl;
    return manhattan_distance;
}

bool compareNodes(Node *a, Node *b)
{
    if (a == nullptr || b == nullptr)
    {
        return false;
    }
    int **grid_a = a->getNodeValues();
    int **grid_b = b->getNodeValues();

    int n = a->getN();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid_a[i][j] != grid_b[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

Node *moveRight(Node *node)
{
    int n = node->getN();
    int **grid = node->getNodeValues();
    int blank_row, blank_column;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 0)
            {
                blank_row = i;
                blank_column = j;
            }
        }
    }
    if (blank_column == n - 1)
    {
        return nullptr;
    }
    else
    {
        int **new_grid = new int *[n];
        for (int i = 0; i < n; i++)
        {
            new_grid[i] = new int[n];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                new_grid[i][j] = grid[i][j];
            }
        }
        new_grid[blank_row][blank_column] = new_grid[blank_row][blank_column + 1];
        new_grid[blank_row][blank_column + 1] = 0;
        Node *new_node = new Node(n);
        new_node->setNodeValues(new_grid);
        new_node->setParent(node);
        new_node->setCostFromSource(node->getCostFromSource() + 1);
        return new_node;
    }
}

Node *moveLeft(Node *node)
{
    int n = node->getN();
    int **grid = node->getNodeValues();
    int blank_row, blank_column;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 0)
            {
                blank_row = i;
                blank_column = j;
            }
        }
    }
    if (blank_column == 0)
    {
        return nullptr;
    }
    else
    {
        int **new_grid = new int *[n];
        for (int i = 0; i < n; i++)
        {
            new_grid[i] = new int[n];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                new_grid[i][j] = grid[i][j];
            }
        }
        new_grid[blank_row][blank_column] = new_grid[blank_row][blank_column - 1];
        new_grid[blank_row][blank_column - 1] = 0;
        Node *new_node = new Node(n);
        new_node->setNodeValues(new_grid);
        new_node->setParent(node);
        new_node->setCostFromSource(node->getCostFromSource() + 1);
        return new_node;
    }
}

Node *moveUp(Node *node)
{
    int n = node->getN();
    int **grid = node->getNodeValues();
    int blank_row, blank_column;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 0)
            {
                blank_row = i;
                blank_column = j;
            }
        }
    }
    if (blank_row == 0)
    {
        return nullptr;
    }
    else
    {
        int **new_grid = new int *[n];
        for (int i = 0; i < n; i++)
        {
            new_grid[i] = new int[n];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                new_grid[i][j] = grid[i][j];
            }
        }
        new_grid[blank_row][blank_column] = new_grid[blank_row - 1][blank_column];
        new_grid[blank_row - 1][blank_column] = 0;
        Node *new_node = new Node(n);
        new_node->setNodeValues(new_grid);
        new_node->setParent(node);
        new_node->setCostFromSource(node->getCostFromSource() + 1);
        return new_node;
    }
}

Node *moveDown(Node *node)
{
    int n = node->getN();
    int **grid = node->getNodeValues();
    int blank_row, blank_column;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 0)
            {
                blank_row = i;
                blank_column = j;
            }
        }
    }
    if (blank_row == n - 1)
    {
        return nullptr;
    }
    else
    {
        int **new_grid = new int *[n];
        for (int i = 0; i < n; i++)
        {
            new_grid[i] = new int[n];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                new_grid[i][j] = grid[i][j];
            }
        }
        new_grid[blank_row][blank_column] = new_grid[blank_row + 1][blank_column];
        new_grid[blank_row + 1][blank_column] = 0;
        Node *new_node = new Node(n);
        new_node->setNodeValues(new_grid);
        new_node->setParent(node);
        new_node->setCostFromSource(node->getCostFromSource() + 1);
        return new_node;
    }
}

void printPath(Node *node, fstream &output)
{

    if (node->getParent() == nullptr)
    {
        node->printNode(output);
        output << endl;
        return;
    }
    else
    {
        printPath(node->getParent(), output);
        node->printNode(output);
        output << endl;
    }
}
