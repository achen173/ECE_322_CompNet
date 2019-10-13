#!/bin/bash

# Filename: ex8.sh
#
# Problem: Use the grave symbol ` is used to execute the command 
# "date +%m_%d_%y" and place it into a variable. (Note no testcase 
# for this exercise)

var1=`date +%m_%d_%y`

datecode=$var1

filename="$datecode"_Assignment.txt

echo The assignment can be renamed as $filename.

