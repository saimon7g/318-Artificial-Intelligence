#!/bin/bash
csvFilePath="output_File.csv"

counter=19
while [ $counter -le 36 ]; do
    ./main "set1/g$counter.rud" $csvFilePath 0.5 100
    ((counter++))
done