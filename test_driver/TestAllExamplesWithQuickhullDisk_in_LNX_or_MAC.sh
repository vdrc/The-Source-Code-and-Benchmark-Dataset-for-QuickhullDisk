#!/bin/bash

#*********************************************************************
#**          Shell script to test 40 examples for QuickhullDisk     **
#*********************************************************************

echo "------------------------------------------------------------------------------------------"
echo "--Test 40 examples(RANDOM(10), MIXED(10), ON-BNDRY(10), ON-A-LINE(10)) for QuickhullDisk--"
echo "------------------------------------------------------------------------------------------"
echo ""

mkdir -p output
mkdir -p output/RANDOM
for i in {1..10} 
do
    echo "-----------------------------"
    ./RunQuickhullDisk -i ../test_data/RANDOM/N"$i"0000.txt -o output/RANDOM/output_"N$i"0000.txt
    echo "-----------------------------"	
done

mkdir -p output/MIXED
for i in {1..10} 
do
    echo "-----------------------------"
    ./RunQuickhullDisk -i ../test_data/MIXED/N100000_"$i"0.txt -o output/MIXED/output_100000_"$i"0.txt
    echo "-----------------------------"	
done

mkdir -p output/ON-BNDRY
for i in {1..10} 
do
    echo "-----------------------------"
    ./RunQuickhullDisk -i ../test_data/ON-BNDRY/N"$i"0000.txt -o output/ON-BNDRY/output_"N$i"0000.txt
    echo "-----------------------------"	
done

mkdir -p output/ON-A-LINE
for i in {1..10} 
do
    echo "-----------------------------"
    ./RunQuickhullDisk -i ../test_data/ON-A-LINE/N"$i"000.txt -o output/ON-A-LINE/output_"N$i"000.txt
    echo "-----------------------------"	
done
