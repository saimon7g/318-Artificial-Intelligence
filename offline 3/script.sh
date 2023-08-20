#!/bin/bash

g++ -o main main.cpp

csvFilePath="output_File.csv"
touch "$csvFilePath"
echo "Test Graph, Number of Vertices, Number of Edges, Alpha Value, Randomized Best Value, Greedy Best Value, Semi-Greedy Best Value, Num of iteration for Local, best value for Local, Num of iteration for GRASP,best value for GRASP" > "$csvFilePath"


counter=1
while [ $counter -le 18 ]; do
    ./main "set1/g$counter.rud" $csvFilePath 0.5 100
    ((counter++))
done

