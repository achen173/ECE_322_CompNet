#!/bin/bash

# Filename: ex5.sh
#
# Problem: Use a case statement to give a different answer depending on whether
# a "y" or a "n" is entered.

read -p "Do you wish to open the pod bay doors?" inputVar

if [ $inputVar == "y" ]; then 
	echo "I'm sorry, Dave. I'm afraid I can't do that."
elif [ $inputVar == "n" ]; then
	echo "That is good. I wouldn't open them anyway."
fi

