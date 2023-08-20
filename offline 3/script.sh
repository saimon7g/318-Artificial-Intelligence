#!/bin/bash

g++ -o main main.cpp

csvFilePath="output_File.csv"
touch "$csvFilePath"
echo "Test Graph, Number of Vertices, Number of Edges, Alpha Value, Randomized Best Value, Greedy Best Value, Semi-Greedy Best Value, Num of iteration for Local, best value for Local, Num of iteration for GRASP,best value for GRASP" > "$csvFilePath"

chmod u+x script1.sh
chmod u+x script2.sh
chmod u+x script3.sh
chmod u+x script4.sh
chmod u+x script5.sh
chmod u+x script6.sh
chmod u+x script7.sh
chmod u+x script8.sh
chmod u+x script9.sh

./script1.sh & ./script2.sh & ./script3.sh & ./script4.sh & ./script5.sh & ./script6.sh & ./script7.sh & ./script8.sh & ./script9.sh