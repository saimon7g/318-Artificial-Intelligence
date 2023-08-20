#!/bin/bash
csvFilePath="output_File.csv"

counter=43
while [ $counter -le 48 ]; do
    ./main "set1/g$counter.rud" $csvFilePath 0.5 50
    ((counter++))
done