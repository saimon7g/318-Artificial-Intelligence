#!/bin/bash
csvFilePath="output_File.csv"

counter=7
while [ $counter -le 12 ]; do
    ./main "set1/g$counter.rud" $csvFilePath 0.5 50
    ((counter++))
done