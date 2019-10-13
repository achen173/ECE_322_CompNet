#!/bin/bash

# Filename: ex2.sh
#
# Problem: Make a script to print out the first and third arguments to 
# the script. Then combine the two arguments in var and print var out.
a=Argument1
b=Argument3
echo The first argument is "${a}"
echo The third argument is "${b}"
var="$a$b"
echo The combined first and third argument in var is "${var}" 
