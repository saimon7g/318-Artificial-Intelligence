#!/bin/bash
csvFilePath="output_File.csv"

counter=13
while [ $counter -le 18 ]; do
    ./main "set1/g$counter.rud" $csvFilePath 0.5 50
    ((counter++))
done